// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_DamageSystem.h"
#include "Structures/S_DamageInfo.h"


// Sets default values for this component's properties
UAC_DamageSystem::UAC_DamageSystem()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	Health = MaxHealth;
	bisDead = false;
	bisBlocking = false;
	bisInterruptible = false;
	bisInterruptible = false;
	bCanBeParried = false;
	DamageState = E_Damage_State::None;

}


// Called when the game starts
void UAC_DamageSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_DamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UAC_DamageSystem::Heal(float amount)
{
	if (!bisDead)
	{
		Health = FMath::Clamp((Health + amount), 0, MaxHealth);
	}

	return Health;
}

bool UAC_DamageSystem::TakeDamage(FS_DamageInfo DamageInfo)
{
	CanBeDamaged(DamageInfo.bShouldDamageInvincible, DamageInfo.bCanBeBlocked);
	
	switch (DamageState)
	{
	case E_Damage_State::DoDamage:
	{
		float newHealth = SetHealth(DamageInfo.amount);

		if (newHealth <= 0)
		{

			bisDead = true;
			On_Death.Broadcast();
		}
		else
		{
			if (bisInterruptible || DamageInfo.bShouldForceInterrupt)
			{
				On_Damage_Response.Broadcast();
			}
		}
		return true;
	}
	case E_Damage_State::NoDamage:
		return false;

	case E_Damage_State::OnBlockDamage:
		BlockedDamage.Broadcast(DamageInfo.bCanBeParried);
		return false;

	default:
		return false;
	}



}

E_Damage_State UAC_DamageSystem::CanBeDamaged(bool shouldDamageInvincible, bool canBeBlocked)
{
	if (!bisDead && (!bisInvincible || shouldDamageInvincible))
	{
		if (canBeBlocked && bisBlocking)
		{
			DamageState = E_Damage_State::OnBlockDamage;
		}
		else
		{
			DamageState = E_Damage_State::DoDamage;
		}

	}
	else
	{
		DamageState = E_Damage_State::NoDamage;

	}

	return DamageState;
}

float UAC_DamageSystem::SetHealth(float amount)
{
	Health = FMath::Clamp((Health - amount), 0, MaxHealth);

	return Health;
}

