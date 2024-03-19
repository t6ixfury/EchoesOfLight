// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Camera/DialogueCamera.h"
#include "Camera/CameraComponent.h"


// Sets default values
ADialogueCamera::ADialogueCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = FollowCamera;
}

// Called when the game starts or when spawned
void ADialogueCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

