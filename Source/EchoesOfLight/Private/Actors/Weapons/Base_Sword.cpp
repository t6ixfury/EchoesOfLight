// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "Interfaces/Interface_Damagable.h"
#include "Character/MainCharacter.h"
#include "Actors/Weapons/Base_Sword.h"

// Sets default values
ABase_Sword::ABase_Sword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Begin of Weapon line Trace
    WeaponTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Trace Start"));

    RootComponent = WeaponTraceStart;


    //Mesh for weapon
    SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordMesh"));
    SwordMesh->SetupAttachment(RootComponent);

    //End of Weapon line trace
    WeaponTraceEnd= CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Trace End"));

    //attaching weapon trace end to root component
    WeaponTraceEnd->SetupAttachment(RootComponent);

    // Damage system for Weapon
    DamageSystem = CreateDefaultSubobject<UAC_DamageSystem>(TEXT("Damage System"));

    //Set BaseAttack weapon info
    BaseAttackInfo.amount = BaseWeaponDamage;
    BaseAttackInfo.bCanBeBlocked = true;
    BaseAttackInfo.DamageType = E_Damage_Type::Melee;
    BaseAttackInfo.DamageResponse = E_Damage_Response::None;



}

// Called when the game starts or when spawned
void ABase_Sword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase_Sword::BaseAttack()
{
    TArray<AActor*> ActorsToIgnore;
    UWorld* World = GetWorld();
    if (WeaponTraceStart && WeaponTraceEnd && World)
    {
        ECollisionChannel TraceChannel = ECC_Pawn;

        FHitResult HitResult;
        bool bHit = UKismetSystemLibrary::LineTraceSingle(
            World,
            WeaponTraceStart->GetComponentLocation(),
            WeaponTraceEnd->GetComponentLocation(),
            ETraceTypeQuery::TraceTypeQuery1,
            false,
            ActorsToIgnore,
            EDrawDebugTrace::None,
            HitResult,
            true,
            FLinearColor::Red, // Trace color
            FLinearColor::Green, // Hit color
            5.0f
        );

       // UE_LOG(LogTemp, Warning, TEXT("BaseAttack has been called"))

        if (HitResult.GetActor())
        {
            //UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
            IInterface_Damagable* HitActor = Cast<IInterface_Damagable>(HitResult.GetActor());

            if (HitActor)
            {
                HitActor->Execute_TakeIncomingDamage(HitResult.GetActor(),BaseAttackInfo);
               // UE_LOG(LogTemp, Warning, TEXT("hit actor found"))
            }

        }
           
    }

}