// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UBTT_GetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Blackboard keys")
		FBlackboardKeySelector RandomLocationOnNavigableArea;

	UPROPERTY(EditAnywhere, Category = "Parameters")
		float Radius = 0;


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
