// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_PauseMenu.h"
#include "Character/MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Components/Button.h"

void UW_PauseMenu::NativeConstruct()
{
	ResumeButton->OnClicked.AddDynamic(this, &UW_PauseMenu::ResumeGame);
	SaveButton->OnClicked.AddDynamic(this, &UW_PauseMenu::SaveGame);
	QuitButton->OnClicked.AddDynamic(this, &UW_PauseMenu::QuitGame);
}

void UW_PauseMenu::ResumeGame()
{
	if (AMainCharacter* Character = Cast<AMainCharacter>(GetOwningPlayerPawn()))
	{
		Character->MainWidgetHandlerComponent->ClosePauseMenu();
	}
	
}

void UW_PauseMenu::SaveGame()
{
	if (AMainCharacter* Character = Cast<AMainCharacter>(GetOwningPlayerPawn()))
	{
		Character->SaveAll();
		if (Character->MainWidgetHandlerComponent)
		{
			Character->MainWidgetHandlerComponent->ShowAlertWidget(FText::FromString("Game Saved!"), FText::FromString(""));

			ResumeGame();
		}
	}
}

void UW_PauseMenu::QuitGame()
{
	UWorld* World = GEngine->GetWorldFromContextObject(GetWorld(), EGetWorldErrorMode::LogAndReturnNull);
	if (World != nullptr)
	{
		FGenericPlatformMisc::RequestExit(false);
	}
}
