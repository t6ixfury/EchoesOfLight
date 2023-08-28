// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "EnemyCharacter.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClosestDistance = 100;
	hasTargetEnemy = false;

	InventoryComponent = CreateDefaultSubobject<UAC_Inventory>(TEXT("Inventory"));
	MainWidgetHandlerComponent = CreateDefaultSubobject<UAC_MainWidgetHandler>(TEXT("Main Widget Handler"));


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::ClosestEnemy(AEnemyCharacter* enemyActor)
{
	float Distance = FVector::Dist(GetActorLocation(), enemyActor->GetActorLocation());

	if (Distance <= ClosestDistance)
	{
		TargetEnemy = enemyActor;
		hasTargetEnemy = true;
	}
}



// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

