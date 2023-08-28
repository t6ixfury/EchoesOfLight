// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_DamageSystem.h"

// Sets default values for this component's properties
UAC_DamageSystem::UAC_DamageSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_DamageSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_DamageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

