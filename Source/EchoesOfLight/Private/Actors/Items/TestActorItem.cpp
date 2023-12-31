// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/TestActorItem.h"

// Sets default values
ATestActorItem::ATestActorItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("TestMeshItem");

	SetRootComponent(ItemMesh);

}

// Called when the game starts or when spawned
void ATestActorItem::BeginPlay()
{
	Super::BeginPlay();
	InteractableData = InstanceInteractableData;
	
}

// Called every frame
void ATestActorItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActorItem::BeginFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin focus called"))
		if (ItemMesh)
		{
			ItemMesh->SetRenderCustomDepth(true);
		}
}

void ATestActorItem::EndFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(false);
	}
}

void ATestActorItem::BeginInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling begin Interact on Interface Item"))
}

void ATestActorItem::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling end Interact on Interface Item"))
}

void ATestActorItem::Interact(AMainCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact on Interface Item"))
}


