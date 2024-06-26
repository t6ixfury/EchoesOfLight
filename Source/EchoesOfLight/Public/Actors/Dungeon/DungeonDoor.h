// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "DungeonDoor.generated.h"


class UStaticMeshComponent;
class AAutoCollectPickup;

UCLASS()
class ECHOESOFLIGHT_API ADungeonDoor : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		UStaticMeshComponent* RightDoor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		bool bIsDoorOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		TSubclassOf<AAutoCollectPickup> DungeonKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		FName DungeonKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door properties")
		FText AlertMessage = FText::FromString("You do not have the dungeon key!\nHint: Try killing the rest of the enemies.");

	FRotator TargetLeftDoorRotation;
	FRotator TargetRightDoorRotation;

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 1.0f;

	// Tracks whether the door is currently being operated
	bool bIsOperating = false;




	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginFocus() override;

	virtual void EndFocus() override;

	virtual void BeginInteract() override;

	virtual void EndInteract() override;

	virtual void Interact(AMainCharacter* PlayerCharacter) override;

	UFUNCTION(BlueprintCallable)
	void OperateDoor();

	void UpdateInteractable();

	bool HasDungeonKey(AMainCharacter* PlayerCharacter);

};
