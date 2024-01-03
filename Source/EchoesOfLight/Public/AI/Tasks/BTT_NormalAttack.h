// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_NormalAttack.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UBTT_NormalAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Normal attack Montage")
		class UAnimMontage* NormalAttack;

	FTimerHandle AttackTimer;

	bool bIsMontageFinished = false;

	UBehaviorTreeComponent* OwnerCompRef;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);


	//The Attack Montage Was able to fully play so return succeeded
	void SetMontageFinished();

	//the enemy was hit so the full attack was not able to be played. Return Failed.
	void OnEnemyHit();

};