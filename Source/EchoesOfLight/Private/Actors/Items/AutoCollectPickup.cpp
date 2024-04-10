// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/AutoCollectPickup.h"
#include "Components/BoxComponent.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Actors/Items/ItemBase.h"

AAutoCollectPickup::AAutoCollectPickup()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collison Box"));

	CollisionBox->SetupAttachment(RootComponent);
}


void AAutoCollectPickup::CollectPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	
	if (Character && bIsItem)
	{
		TakePickup(Character);
		if (this->ItemReference)
		{
			FText ItemAddedText = FText::Format(
				NSLOCTEXT("YourNamespace", "ItemAddedToInventory", "{0} has been added to your inventory!"),
				FText::FromName(this->ItemReference->ID)
			);

			Character->MainWidgetHandlerComponent->ShowAlertWidget(ItemAddedText);
		}
	}
}

void AAutoCollectPickup::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AAutoCollectPickup::CollectPickup);
}
