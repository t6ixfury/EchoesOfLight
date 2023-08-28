// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_ExperieceSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Save/Save_Experience.h"


// Sets default values for this component's properties
UAC_ExperieceSystem::UAC_ExperieceSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_ExperieceSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_ExperieceSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ExperieceSystem::AddExperience(float ExpToAdd)
{
	CurrentExp += ExpToAdd;
	if (CurrentExp >= ExpToNextLevel)
	{
		LevelUp();

	}
	else
	{
		UpdateWidget();
	}
}

void UAC_ExperieceSystem::LevelUp()
{
	CurrentExp -= ExpToNextLevel;
	ExpToNextLevel *= NextExpMultiplier;

}

void UAC_ExperieceSystem::UpdateWidget()
{
}

void UAC_ExperieceSystem::SaveExperience()
{
	if (UGameplayStatics::DoesSaveGameExist(ExperienceSlot, 0))
	{
		if (USave_Experience* SaveToLoad = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(ExperienceSlot, 0)))
		{
			SaveReference = SaveToLoad;
			SaveReference->sExperience = CurrentExp;
			SaveReference->sCurrentLevel = CurrentLevel;
			SaveReference->sExperienceToNextLevel = ExpToNextLevel;
		}
		else
		{
			if (USave_Experience* NewSave = Cast<USave_Experience>(UGameplayStatics::CreateSaveGameObject(Save)))
			{
				SaveReference = NewSave;
				SaveReference->sExperience = CurrentExp;
				SaveReference->sCurrentLevel = CurrentLevel;
				SaveReference->sExperienceToNextLevel = ExpToNextLevel;
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(SaveReference, ExperienceSlot, 0);
}

void UAC_ExperieceSystem::LoadExperience()
{
	if (UGameplayStatics::DoesSaveGameExist(ExperienceSlot, 0))
	{
		if (USave_Experience* SaveToLoad = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(ExperienceSlot, 0)))
		{
			CurrentExp = SaveToLoad->sExperience;
			ExpToNextLevel = SaveToLoad->sExperienceToNextLevel;
			CurrentLevel = SaveToLoad->sCurrentLevel;
		}
	}
}

