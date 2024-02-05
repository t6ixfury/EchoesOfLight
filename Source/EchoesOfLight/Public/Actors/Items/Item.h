// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/Structs.h"
#include "Interfaces/Interface_Interaction.h"
#include "Item.generated.h"
/// <summary>
/// WILL BE DELETING THIS CLASS AS BECAUSE IT IS THE WRONG ITEM CLASS AND WAS A FIRST ITERATION.
/// </summary>
UCLASS()
class ECHOESOFLIGHT_API AItem : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FS_Item ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		class USphereComponent* ItemCollision;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 indexInInventoryGrid;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void BeginFocus() override;
	UFUNCTION()
	virtual void EndFocus() override;
	UFUNCTION()
	virtual void BeginInteract() override;
	UFUNCTION()
	virtual void EndInteract() override;
	UFUNCTION()
	virtual void Interact(AMainCharacter* PlayerCharacter) override;


}; 

