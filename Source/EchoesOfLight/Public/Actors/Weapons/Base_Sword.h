// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/S_DamageInfo.h"
#include "Interfaces/Interface_Damagable.h"
#include "Base_Sword.generated.h"

class UItemBase;

UCLASS()
class ECHOESOFLIGHT_API ABase_Sword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABase_Sword();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		 FS_DamageInfo BaseAttackInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* WeaponTraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* WeaponTraceEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		class USkeletalMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties | Weapon Initialization")
		UDataTable* DualWeaponDataTable;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties | Weapon Initialization")
		FName DesiredItemId;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties | Item Reference")
		UItemBase* WeaponItemReference;
	UPROPERTY()
	UPrimitiveComponent* EnemyPrimitiveComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void BaseAttack();

	void InitializeWeapon();
	void SetEnemyPhysics();
	


};
