// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Engine/DataTable.h"

#include "AC_MainWidgetHandler.generated.h"

class UW_Inventory;
class UW_Interact;
class UW_PauseMenu;
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

	UPROPERTY(BlueprintReadOnly)
		UW_MainGUI* GUI;

	UPROPERTY(BlueprintReadOnly)
		UW_Inventory* MH_Inventory;

	UPROPERTY(BlueprintReadOnly)
		UW_Interact* Interact;

	UPROPERTY(BlueprintReadOnly)
		UW_PauseMenu* PauseMenu;

	UPROPERTY(BlueprintReadOnly)
		AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* MainCharacterController;

	UPROPERTY(BlueprintReadOnly)
		FTimerHandle HoldTimer;

	UPROPERTY(BlueprintReadOnly)
		float HOLD_NeededTime;

	UPROPERTY(BlueprintReadOnly)
		AActor* HOLD_Actor;

	//accesses my library
	UBFL_Utility* Utility;

	UPROPERTY(BlueprintReadWrite, Category = DataTable)
	FDataTableRowHandle GameSetting;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitializePlayerWidgets_CustomEvent);
	FInitializePlayerWidgets_CustomEvent InitializePlayerWidgetsEvent;

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
		void CreateInventoryWidget();

	UFUNCTION(BlueprintCallable)
		void TogglePause();

		
};
