// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstanceBase.generated.h"

class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UEnemyAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:
	UPROPERTY(VisibleAnywhere)
		AEnemyCharacter* EnemyCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Properties")
		float EnemycharacterSpeed;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
public:
	
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
};
