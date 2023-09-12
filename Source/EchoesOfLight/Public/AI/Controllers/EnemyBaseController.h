// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enums/E_EnemyStates.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyBaseController.generated.h"

struct FActorPerceptionBlueprintInfo;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AEnemyBaseController : public AAIController
{
	GENERATED_BODY()

//FOR VARIABLES
public:
	AEnemyBaseController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackboard Variable Names")
		FName StateKeyName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackboard Variable Names")
		FName AttackTargetKeyName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blackboard Variable Names")
		FName PointOfInterestKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
		UBlackboardComponent* AiBlackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
		UBehaviorTree* AiBehaviorTree;

	UPROPERTY(BlueprintReadWrite, Category = "Perception")
		FActorPerceptionBlueprintInfo PerceptionInfo;



private:
	UPROPERTY()
		E_EnemyAI_Sense Sensed;

		


//FOR FUNCTIONS
public: 

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "States")
		void SetStateAsPassive();

	UFUNCTION(BlueprintCallable, Category = "States")
		void SetStateAsInvestigating(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "States")
		void SetStateAsDeath();

	UFUNCTION(BlueprintCallable, Category = "States")
		void SetStateAsAttacking(AActor* AttackTarget);

	UFUNCTION(BlueprintCallable, Category = "States")
		E_EnemyAI_State GetCurrentState();

	UFUNCTION(BlueprintCallable, Category = "Sense Functions")
		void AICanSenseActor(AActor* SensedActor);

	UFUNCTION(BlueprintCallable, Category = "Sense Functions")
		void AIHandleSenseSight(AActor* SensedActor);

	UFUNCTION(BlueprintCallable, Category = "Sense Functions")
		void AIHandleSenseHearing(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Sense Functions")
		void AIHandleSenseDamage(AActor* SensedActor);



	

//HELPER FUNCTIONS=

		class AMainCharacter* GetPlayerCharacterInWorld(UWorld* WorldContext);

		E_EnemyAI_Sense AIHandleAiSenseConversion(FAISenseID SenseID);

		UFUNCTION(BlueprintCallable, Category = "AI Perception")
		void AIHandleUpdatedPerception(const TArray<AActor*>& UpdatedActors);

// GETTER FUNCTIONS
		// may delete
		class UBlackboardComponent* GetEnemyAiControllerBlackBoard();



};
