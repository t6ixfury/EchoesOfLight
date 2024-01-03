// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsMontagePlaying.generated.h"


///////////////////////////TO BE DELETED//////////////////
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UBTD_IsMontagePlaying : public UBTDecorator
{
	GENERATED_BODY()

public:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
