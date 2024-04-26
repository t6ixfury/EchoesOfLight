// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ExitPortal.h"
#include "Save/EchoesGameInstance.h"
#include "Managers/GameInfo.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"

void AExitPortal::LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMainCharacter* character = Cast<AMainCharacter>(OtherActor))
	{
		character->SaveAll();
	}
	if (UEchoesGameInstance* GameInstance = Cast< UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (GameInstance->GameInfo)
		{
			GameInstance->GameInfo->CurrentDungeonIndex = FMath::Clamp((GameInstance->GameInfo->CurrentDungeonIndex + 1), 0, GameInstance->DungeonLevels.Num() - 1);
			GameInstance->GameInfo->CurrentTownIndex = FMath::Clamp((GameInstance->GameInfo->CurrentTownIndex + 1), 0, GameInstance->TownLevels.Num() - 1);
			GameInstance->GameInfo->CurrentDungeonLevel = GameInstance->DungeonLevels[GameInstance->GameInfo->CurrentDungeonIndex];
			GameInstance->GameInfo->CurrentTownLevel = GameInstance->TownLevels[GameInstance->GameInfo->CurrentTownIndex];
			int32 index = GameInstance->GameInfo->CurrentTownIndex;

			LeveltoLoad = GameInstance->TownLevels[index];
			UGameplayStatics::OpenLevel(GetWorld(), LeveltoLoad);

		}
	}
}

void AExitPortal::finishLoadLevel()
{
	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{

	}
}
