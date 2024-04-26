// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BasePortal.h"
#include "ExitPortal.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AExitPortal : public ABasePortal
{
	GENERATED_BODY()

 public:
	 FTimerHandle LoadwaitTimer;

	 FName LeveltoLoad;

	 virtual void LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	 void finishLoadLevel();
	
};
