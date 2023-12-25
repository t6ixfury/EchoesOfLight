// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_ExperieceSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class ECHOESOFLIGHT_API UAC_ExperieceSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ExperieceSystem();


	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float ExpToNextLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float CurrentExp = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		int32 CurrentLevel;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float NextExpMultiplier;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		FString ExperienceSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		class USave_Experience* SaveReference;
	
	UPROPERTY()
		TSubclassOf<class USave_Experience> Save;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Experience System Functions")
		void AddExperience(float ExpToAdd);

	UFUNCTION(BlueprintCallable, Category = "Experience System Functions")
		void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "Experience System Functions")
		void UpdateWidget();

	UFUNCTION(BlueprintCallable, Category = "Experience System Functions")
		void SaveExperience();

	UFUNCTION(BlueprintCallable, Category = "Experience System Functions")
		void LoadExperience();


		
};
