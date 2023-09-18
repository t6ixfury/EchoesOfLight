// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePortal.h"
#include "Kismet/GameplayStatics.h"
#include "Character/MainCharacter.h"
#include "Components/BoxComponent.h"



// Sets default values
ABasePortal::ABasePortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PortalPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal Mesh"));
	RootComponent = PortalPlane;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);

	LevelToLoad = TEXT("ThirdPersonMap");
}

// Called when the game starts or when spawned
void ABasePortal::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Level Function binded"));
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePortal::LoadLevel);
	}

}

void ABasePortal::LoadLevel(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Load Level Function"));
	UGameplayStatics::OpenLevel(this, LevelToLoad);
}

// Called every frame
void ABasePortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

