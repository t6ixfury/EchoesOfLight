// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Villager.h"
#include "ActorComponents/DialogueSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MainCharacter.h"
#include "Actors/Camera/DialogueCamera.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Widgets/W_DialogueBox.h"
#include "Widgets/W_DialogueGui.h"



// Sets default values
AVillager::AVillager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Dialogue = CreateDefaultSubobject<UDialogueSystem>(TEXT("Dialogue System"));

}

void AVillager::BeginFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginFocus Villager"))

	if (Dialogue->DialogueData.InteractionMontage)
	{
		USkeletalMeshComponent* meshcomp = GetMesh();
		
		UAnimInstance* anim = meshcomp->GetAnimInstance();

		anim->Montage_Play(Dialogue->DialogueData.InteractionMontage);
		anim->Montage_JumpToSection("");
	}
}

void AVillager::EndFocus()
{
}

void AVillager::BeginInteract()
{
}

void AVillager::EndInteract()
{
}

void AVillager::Interact(AMainCharacter* PlayerCharacter)
{

	if (PlayerCharacter && !Dialogue->bIsTalking)
	{
		Dialogue->bIsTalking = true;
		PlayerCharacter->DialogueSystem->bIsTalking = true;
		//TODO:
	//set villager rotation toward character
		CharacterRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerCharacter->GetActorLocation());
		

		//Set character camera to villager location. and lock position
		SetDialogueCameraView(PlayerCharacter);

		// Display character dialogue widget with village text
		PlayerCharacter->MainWidgetHandlerComponent->CreateDialogueWidget();
		Dialogue->RetrieveDialogueData();

		if (PlayerCharacter->MainWidgetHandlerComponent->DialogueGui)
		{
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->DialogueBox->SetName(Dialogue->DialogueData.Name);
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->DialogueBox->SetDialogueText(Dialogue->DialogueData.Dialoguetext);
		}

		Dialogue->SetDialogueSentencesArray(Dialogue->DialogueData.Dialoguetext);


		// Press f to go to the next. 

		// after all text are done. Reset character camera. unlock movement.
	}

}

void AVillager::SetInteractableData()
{
	InteractableData.Action = FText::FromString("Talk");
	InteractableData.InteractableType = EInteractableType::Villager;
	InteractableData.InteractionDuration = 0;
	InteractableData.Quantity = 0;
}

void AVillager::SetVillagerRotation(float DeltaTime)
{
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CharacterRotation, DeltaTime, RotationSpeed);
	SetActorRotation(NewRotation);

}

void AVillager::SetDialogueCameraView(AMainCharacter* Character)
{
	FVector ForwardVector = GetActorForwardVector();
	FVector CameraLocation = GetActorLocation() - (ForwardVector * 200); // Move 200 units in front
	FRotator CameraRotation = FRotationMatrix::MakeFromX(GetActorLocation() - CameraLocation).Rotator();

	DialogueCamera = GetWorld()->SpawnActor<ADialogueCamera>(ADialogueCamera::StaticClass(), CameraLocation, CameraRotation);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && DialogueCamera)
	{
		//set camera view to dialoge camera.
		PlayerController->SetViewTargetWithBlend(DialogueCamera, .8f);

		UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
		if (MovementComponent)
		{
			//stops all movement on character.
			MovementComponent->SetMovementMode(EMovementMode::MOVE_None);

			//hides all widgets
			Character->MainWidgetHandlerComponent->HideHUD();
			Character->MainWidgetHandlerComponent->HideInteractionWidget();

			//hides the main character in game
			Character->SetActorHiddenInGame(true);
		}

	}
}

// Called when the game starts or when spawned
void AVillager::BeginPlay()
{
	Super::BeginPlay();
	SetInteractableData();

	
}

// Called every frame
void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Dialogue->bIsTalking)
	{
		SetVillagerRotation(DeltaTime);
	}
}

// Called to bind functionality to input
void AVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

