// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Engine/DataTable.h"

#include "AC_MainWidgetHandler.generated.h"

class UW_Interact;
class UW_MainGUI;
class AMainCharacter;
class UBFL_Utility;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UAC_MainWidgetHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_MainWidgetHandler();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_MainGUI> GUI_Class;

	UPROPERTY(BlueprintReadWrite)
		UW_MainGUI* GUI;

	UPROPERTY(BlueprintReadOnly)
		UW_Interact* Interact;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TSubclassOf<AMainCharacter> CharacterClass ;

	UPROPERTY(BlueprintReadOnly)
		AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* MainCharacterController;

	UFUNCTION()
		void CreateAllPlayerWidgets();

	
		


protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void InitializePlayer();

	UFUNCTION(BlueprintCallable)
		void CreateMainWidget();

	UFUNCTION(BlueprintCallable)
		void TogglePause();

		
};
