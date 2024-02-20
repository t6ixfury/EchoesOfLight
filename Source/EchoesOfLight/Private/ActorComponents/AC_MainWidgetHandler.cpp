// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Components/ActorComponent.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_Interact.h"
#include "W_MainGUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Structures/Structs.h"
#include "Libraries/BFL_Utility.h"
#include "W_MainGUI.h"
#include "ActorComponents/AC_Inventory.h"




// Sets default values for this component's properties
UAC_MainWidgetHandler::UAC_MainWidgetHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAC_MainWidgetHandler::CreateAllPlayerWidgets()
{
	InitializePlayer();
	CreateMainWidget();
}

// Called when the game starts
void UAC_MainWidgetHandler::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("mainwidgethandler beginplay called"));
	CreateAllPlayerWidgets();
}


// Called every frame
void UAC_MainWidgetHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_MainWidgetHandler::InitializePlayer()
{

	MainCharacter = Cast<AMainCharacter>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("Maincharacter set"))
	if (MainCharacter)
	{
		MainCharacterController = Cast<APlayerController>(MainCharacter->GetController());
		UE_LOG(LogTemp, Warning, TEXT("MainCharacter present"));
	}
}

void UAC_MainWidgetHandler::CreateMainWidget()
{
	if (MainCharacterController && GUI_Class)
	{
		GUI = CreateWidget<UW_MainGUI>(MainCharacterController, GUI_Class);
		if (GUI)
		{
			GUI->AddToViewport();
		}

	}
}


void UAC_MainWidgetHandler::TogglePause()
{

}

