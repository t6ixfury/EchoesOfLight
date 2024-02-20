// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structures/S_DamageInfo.h"
#include "Interface_Damagable.generated.h"

// This class does not need to be modified.
UINTERFACE()
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
	virtual float GetCurrentHealth()=0;

	virtual float GetMaxHealth()=0;

	virtual void Heal(float amount)=0;

	virtual bool TakeIncomingDamage(FS_DamageInfo DamageInfo)=0;

};
