// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Items/Item.h"
#include "Components/SphereComponent.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_CurrencySystem.h"
#include "ActorComponents/AC_ExperieceSystem.h"
#include "ActorComponents/AC_Inventory.h"
#include "Enums/Enums.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));

	ItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Item Collision"));

	RootComponent = ItemMesh;

	ItemCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (ItemCollision)
	{
		// Set the the overlap event to give logic to what will happen when the actor ovelaps
		ItemCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
		UE_LOG(LogTemp, Warning, TEXT("OverLapped Function binded"));
	}
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);

	if (Character)
	{
		switch (ItemInfo.UsageType)
		{
		case E_Global_Systems::Currency:
			Character->CurrencySystem->Currency += 1;

			break;

		case E_Global_Systems::Experience:
			Character->ExperienceSystem->CurrentExp += 1;

			break;

		case E_Global_Systems::Inventory:
			//Character->InventorySystem->AddItems(this);

		default:
			break;
		}
	}
}

void AItem::BeginFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin focus called"))
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void AItem::EndFocus()
{
	if (ItemMesh)
	{
		ItemMesh->SetRenderCustomDepth(true);
	}
}

void AItem::BeginInteract()
{
	UE_LOG(LogTemp,Warning, TEXT("Calling begin Interact on Interface Item"))
}

void AItem::EndInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("Calling end Interact on Interface Item"))
}

void AItem::Interact(AMainCharacter* PlayerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling Interact on Interface Item"))
}


