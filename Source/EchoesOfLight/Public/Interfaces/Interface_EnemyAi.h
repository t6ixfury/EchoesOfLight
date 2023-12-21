// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_EnemyAi.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_EnemyAi : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECHOESOFLIGHT_API IInterface_EnemyAi
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:  

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attacks")
		float NormalAttack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "States")
		void Death();
};
