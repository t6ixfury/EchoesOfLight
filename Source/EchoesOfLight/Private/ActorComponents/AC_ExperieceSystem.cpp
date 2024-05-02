// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_ExperieceSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Save/Save_Experience.h"
#include "Character/MainCharacter.h"
#include "Save/EchoesGameInstance.h"

// Sets default values for this component's properties
UAC_ExperieceSystem::UAC_ExperieceSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ExperienceSlot = FString("ExperienceSlot1");

	// ...
}


// Called when the game starts
void UAC_ExperieceSystem::BeginPlay()
{
	Super::BeginPlay();
	CharacterRef = Cast<AMainCharacter>(GetOwner());
}


// Called every frame
void UAC_ExperieceSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ExperieceSystem::AddExperience(float ExpToAdd)
{
	if (CurrentLevel < 50)
	{
		CurrentExp += ExpToAdd;
		ExpGainedForNewLevel += ExpToAdd;

		UE_LOG(LogTemp, Warning, TEXT("Current Experience : %f"), CurrentExp);

		if (ExpGainedForNewLevel >= NeededExp)
		{
			LevelUp();
		}
		ExperienceAddedDelegate.Broadcast(ExpToAdd);
	}  

}

void UAC_ExperieceSystem::LevelUp()
{
	if (CurrentLevel < 50)
	{
		LastLevelExp = Levels.LevelToExperience[CurrentLevel];
		CurrentLevel = FMath::Clamp(CurrentLevel + 1, 1, 50);
		ExpToNextLevel = Levels.LevelToExperience[CurrentLevel + 1];
		NeededExp = ExpToNextLevel - LastLevelExp;
		ExpGainedForNewLevel = 0;

		UE_LOG(LogTemp, Warning, TEXT("Experience  to next level : %f"), ExpToNextLevel);
		if (CharacterRef)
		{
			FItemCharacerStatistics stats;
			stats.Defense = FMath::RandRange(1, 3);
			stats.Health = FMath::RandRange(1, 3);
			stats.Stamina = FMath::RandRange(1, 3);
			stats.Strength = FMath::RandRange(1, 3);
			CharacterRef->IncreaseStats(stats);
			SaveExperience();
		}
	}
	LevelUpDelegate.Broadcast(CurrentLevel);
}

void UAC_ExperieceSystem::UpdateWidget()
{
	
}

void UAC_ExperieceSystem::SaveExperience()
{
	if (UWorld* World = GetOwner()->GetWorld())
	{
		UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(World->GetGameInstance());
		USave_Experience* ExpSave = NewObject<USave_Experience>(this, USave_Experience::StaticClass());

		if (IsValid(GameInstance) && IsValid(ExpSave))
		{
			ExpSave->sCurrentLevel = CurrentLevel;
			ExpSave->sExperienceToNextLevel = ExpToNextLevel;
			ExpSave->sExperience = CurrentExp;
			UGameplayStatics::SaveGameToSlot(ExpSave, GameInstance->ExperienceSlot, 0);
			UE_LOG(LogTemp, Warning, TEXT("Experience Saved"));
		}

	}
}

void UAC_ExperieceSystem::LoadExperience()
{

	if (UWorld* World = GetOwner()->GetWorld())
	{
		UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(World->GetGameInstance());
		if (IsValid(GameInstance))
		{
			if (UGameplayStatics::DoesSaveGameExist(GameInstance->ExperienceSlot, 0))
			{
				if (USave_Experience* ExpSave = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(GameInstance->ExperienceSlot, 0)))
				{
					CurrentExp = ExpSave->sExperience;
					ExpToNextLevel = ExpSave->sExperienceToNextLevel;
					CurrentLevel = ExpSave->sCurrentLevel;
					UE_LOG(LogTemp, Warning, TEXT("Experience Loaded"));
				}

			}
		}
	}

}

