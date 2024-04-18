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
		if (CurrentExp >= ExpToNextLevel)
		{
			LevelUp();

		}
		UpdateWidget();
	}  
}

void UAC_ExperieceSystem::LevelUp()
{
	if (CurrentLevel < 50)
	{
		CurrentLevel = FMath::Clamp(CurrentLevel + 1, 1, 50);
		ExpToNextLevel = Levels.LevelToExperience[CurrentLevel + 1] - Levels.LevelToExperience[CurrentLevel];
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
	LevelUpDelegate.Broadcast();
}

void UAC_ExperieceSystem::UpdateWidget()
{
	ExperienceAddedDelegate.Broadcast();
}

void UAC_ExperieceSystem::SaveExperience()
{
	if (UWorld* World = GetOwner()->GetWorld())
	{
		UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(World->GetGameInstance());
		USave_Experience* InvSave = NewObject<USave_Experience>(this, USave_Experience::StaticClass());

		if (IsValid(GameInstance) && IsValid(InvSave))
		{
			InvSave->sCurrentLevel = CurrentLevel;
			InvSave->sExperienceToNextLevel = ExpToNextLevel;
			InvSave->sExperience = CurrentExp;
			GameInstance->SaveGameData(InvSave,nullptr,nullptr);
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
				CurrentExp = GameInstance->ExperienceData->sExperience;
				ExpToNextLevel = GameInstance->ExperienceData->sExperienceToNextLevel;
				CurrentLevel = GameInstance->ExperienceData->sCurrentLevel;
				UE_LOG(LogTemp, Warning, TEXT("Experience Loaded"));
				
			}
		}
	}

}

