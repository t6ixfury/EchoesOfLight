// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_DeathMenu.h"
#include "Character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Components/Button.h"
#include "Save/EchoesGameInstance.h"
#include "Managers/GameInfo.h"

void UW_DeathMenu::NativeConstruct()
{
}

void UW_DeathMenu::Restart()
{
	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (GameInstance->GameInfo)
		{
			GameInstance->GameInfo->LoadGameInfo(GameInstance);

			UGameplayStatics::OpenLevel(this, GameInstance->GameInfo->CurrentDungeonLevel);

			RemoveFromParent();
		}
	}
}

void UW_DeathMenu::QuitGame()
{
	UWorld* World = GEngine->GetWorldFromContextObject(GetWorld(), EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		FGenericPlatformMisc::RequestExit(false);
	};
}
