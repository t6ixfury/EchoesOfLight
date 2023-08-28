// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class ECHOESOFLIGHT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_Inventory* InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_MainWidgetHandler* MainWidgetHandlerComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ClosestEnemy(class AEnemyCharacter* enemyActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	float ClosestDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		 AEnemyCharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		bool hasTargetEnemy;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
