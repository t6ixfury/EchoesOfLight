// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structures/Structs.h"
#include "AC_ExperieceSystem.generated.h"

class AMainCharacter;



USTRUCT()
struct FCharacterLevels
{

    GENERATED_USTRUCT_BODY()
public:
		TMap<int32, float> LevelToExperience;

	FCharacterLevels() {

		LevelToExperience.Add(1, 100.0f);
		LevelToExperience.Add(2, 215.0f);
		LevelToExperience.Add(3, 347.0f);
		LevelToExperience.Add(4, 499.0f);
		LevelToExperience.Add(5, 674.0f);
		LevelToExperience.Add(6, 875.0f);
		LevelToExperience.Add(7, 1106.0f);
		LevelToExperience.Add(8, 1372.0f);
		LevelToExperience.Add(9, 1678.0f);
		LevelToExperience.Add(10, 2030.0f);
		LevelToExperience.Add(11, 2435.0f);
		LevelToExperience.Add(12, 2900.0f);
		LevelToExperience.Add(13, 3435.0f);
		LevelToExperience.Add(14, 4050.0f);
		LevelToExperience.Add(15, 4758.0f);
		LevelToExperience.Add(16, 5572.0f);
		LevelToExperience.Add(17, 6508.0f);
		LevelToExperience.Add(18, 7584.0f);
		LevelToExperience.Add(19, 8822.0f);
		LevelToExperience.Add(20, 10245.0f);
		LevelToExperience.Add(21, 11882.0f);
		LevelToExperience.Add(22, 13764.0f);
		LevelToExperience.Add(23, 15928.0f);
		LevelToExperience.Add(24, 18417.0f);
		LevelToExperience.Add(25, 21280.0f);
		LevelToExperience.Add(26, 24572.0f);
		LevelToExperience.Add(27, 28358.0f);
		LevelToExperience.Add(28, 32712.0f);
		LevelToExperience.Add(29, 37719.0f);
		LevelToExperience.Add(30, 43477.0f);
		LevelToExperience.Add(31, 50098.0f);
		LevelToExperience.Add(32, 57712.0f);
		LevelToExperience.Add(33, 66469.0f);
		LevelToExperience.Add(34, 76539.0f);
		LevelToExperience.Add(35, 88119.0f);
		LevelToExperience.Add(36, 101437.0f);
		LevelToExperience.Add(37, 116752.0f);
		LevelToExperience.Add(38, 134364.0f);
		LevelToExperience.Add(39, 154618.0f);
		LevelToExperience.Add(40, 177910.0f);
		LevelToExperience.Add(41, 204696.0f);
		LevelToExperience.Add(42, 235500.0f);
		LevelToExperience.Add(43, 270925.0f);
		LevelToExperience.Add(44, 311664.0f);
		LevelToExperience.Add(45, 358514.0f);
		LevelToExperience.Add(46, 412391.0f);
		LevelToExperience.Add(47, 474349.0f);
		LevelToExperience.Add(48, 545601.0f);
		LevelToExperience.Add(49, 627541.0f);
		LevelToExperience.Add(50, 721772.0f);
	}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FLeveledUpDelegate, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FExperienceAddedDelegate, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class ECHOESOFLIGHT_API UAC_ExperieceSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ExperieceSystem();

		FCharacterLevels Levels;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float ExpToNextLevel = Levels.LevelToExperience[2] - Levels.LevelToExperience[1];

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float CurrentExp = Levels.LevelToExperience[1];

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		int32 CurrentLevel = 1;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float NextExpMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
		FString ExperienceSlot;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		class USave_Experience* SaveReference;

	AMainCharacter* CharacterRef;

	FLeveledUpDelegate LevelUpDelegate;
	FExperienceAddedDelegate ExperienceAddedDelegate;

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
