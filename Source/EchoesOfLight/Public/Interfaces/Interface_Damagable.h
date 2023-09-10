// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structures/S_DamageInfo.h"
#include "Interface_Damagable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UInterface_Damagable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECHOESOFLIGHT_API IInterface_Damagable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	float GetCurrentHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Health")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Abilities")
	void Heal(float amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damage")
	bool TakeIncomingDamage(FS_DamageInfo DamageInfo);

};
