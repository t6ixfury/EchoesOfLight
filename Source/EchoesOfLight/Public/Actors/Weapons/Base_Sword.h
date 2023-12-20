// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/S_DamageInfo.h"
#include "Interfaces/Interface_Damagable.h"
#include "Base_Sword.generated.h"

UCLASS()
class ECHOESOFLIGHT_API ABase_Sword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Sword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		 FS_DamageInfo BaseAttackInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		float BaseWeaponDamage = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* WeaponTraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* WeaponTraceEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		class USkeletalMeshComponent* SwordMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BaseAttack();


};
