// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enums/Enums.h"

#include "CharacterAnimInstance.generated.h"

class AMainCharacter;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY()
		AMainCharacter* Character = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character variables")
		ECharacterState CombatState = ECharacterState::NonCombat;

	bool bIsInitialized = false;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

	void SetCharacterRef();
	void SetDelegates();
	UFUNCTION()
	void SetCombatState();


	
};
