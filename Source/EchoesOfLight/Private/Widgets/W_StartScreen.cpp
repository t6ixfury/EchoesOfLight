// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_StartScreen.h"
#include "Components/Button.h"
#include "Save/EchoesGameInstance.h"
#include "Save/Save_PlayerInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/W_LoadScreen.h"
#include "Components/ProgressBar.h"


void UW_StartScreen::NativeConstruct()
{
	if (APlayerController* controller = GetWorld()->GetFirstPlayerController())
	{
		controller->bShowMouseCursor = true;

		FInputModeUIOnly UI;

		controller->SetInputMode(UI);
	}

	StartGame->OnClicked.AddDynamic(this, &UW_StartScreen::Start);
	QuitGame->OnClicked.AddDynamic(this, &UW_StartScreen::Quit);

	
}

void UW_StartScreen::Start()
{

	UE_LOG(LogTemp, Warning, TEXT("Start Called"));
	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance exist"));
		if (IsValid(GameInstance->PlayerInfoData))
		{
			if (!GameInstance->PlayerInfoData->CurrentTownVariation.IsNone())
			{

				LevelBeingLoaded = GameInstance->PlayerInfoData->CurrentTownVariation;
				UGameplayStatics::OpenLevel(this, LevelBeingLoaded);
				UE_LOG(LogTemp, Warning, TEXT("trying to open level from save data"));

			}
		}
		else
		{
			LevelBeingLoaded = FirstLevel;
			UGameplayStatics::OpenLevel(GetWorld(), FirstLevel);
			UE_LOG(LogTemp, Warning, TEXT("Opening first level"));
		}
	}

}

void UW_StartScreen::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
}


