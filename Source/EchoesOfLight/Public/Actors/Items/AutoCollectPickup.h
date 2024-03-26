// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Items/Pickup.h"
#include "AutoCollectPickup.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AAutoCollectPickup : public APickup
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AutoPickup")
		bool bIsItem = true;

	AAutoCollectPickup();


	UFUNCTION()
	void CollectPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

};
