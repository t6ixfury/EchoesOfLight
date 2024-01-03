// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetEnemyState.generated.h"



UENUM()
enum class EEnemyState : uint8
{
	Attacking UMETA(DisplayName = "Attacking"),
	Investigating UMETA(DisplayName = "Investigating"),
	Passive UMETA(DisplayName = "Passive"),
	Death UMETA(DisplayName = "Death")


};

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UBTT_SetEnemyState : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Blackboard keys")
		FBlackboardKeySelector PointOfInterestKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard keys")
		FBlackboardKeySelector AttackTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		EEnemyState EnemyState;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
