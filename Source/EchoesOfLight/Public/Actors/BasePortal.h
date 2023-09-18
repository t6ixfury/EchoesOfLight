// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePortal.generated.h"

UCLASS()
class ECHOESOFLIGHT_API ABasePortal : public AActor
{
	GENERATED_BODY()
//FOR vARIABLES	
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal Mesh")
		UStaticMeshComponent* PortalPlane;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Variables")
		FName LevelToLoad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* CollisionBox;

// FOR FUNCTIONS
public:	
	ABasePortal();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
