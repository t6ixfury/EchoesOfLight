// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_StartScreen.h"
#include "Components/Button.h"
#include "Save/EchoesGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GameInfo.h"



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
		if (GameInstance->GameInfo)
		{
			UGameplayStatics::OpenLevel(this, GameInstance->TownLevels[GameInstance->GameInfo->CurrentTownIndex]);
		}
	}

}

void UW_StartScreen::Quit()
{
	FGenericPlatformMisc::RequestExit(false);
}


