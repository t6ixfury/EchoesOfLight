// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "TestActorItem.generated.h"

UCLASS()
class ECHOESOFLIGHT_API ATestActorItem : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestActorItem();

	UPROPERTY(EditAnywhere, Category = "TestActorItem")
		UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditInstanceOnly, Category = "Iteractable data")
	FInteractableData InstanceInteractableData;

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




};
