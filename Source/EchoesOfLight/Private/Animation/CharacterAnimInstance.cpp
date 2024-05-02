// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"
#include "Character/MainCharacter.h"

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	SetCharacterRef();
	SetDelegates();
}

void UCharacterAnimInstance::SetCharacterRef()
{
	if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetOwningActor()))
	{
		Character = MainCharacter;
	}
}

void UCharacterAnimInstance::SetDelegates()
{
	if (Character && !bIsInitialized)
	{
		bIsInitialized = true;
		Character->CharacterStateChangeDelegate.AddDynamic(this, &UCharacterAnimInstance::SetCombatState);
		UE_LOG(LogTemp, Warning, TEXT("Setdelegate called"))
	}
}

void UCharacterAnimInstance::SetCombatState()
{
	if (Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCombatState called"))
		CombatState = Character->GetCharacterState();
	}
}


