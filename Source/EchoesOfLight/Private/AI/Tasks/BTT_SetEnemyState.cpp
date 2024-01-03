// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_SetEnemyState.h"
#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/MainCharacter.h"



EBTNodeResult::Type UBTT_SetEnemyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemyBaseController* EnemyController = Cast<AEnemyBaseController>(OwnerComp.GetAIOwner());

	if (EnemyController)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (!BlackboardComp)
		{
			return EBTNodeResult::Failed;
		}

		AMainCharacter* AttackTargetToPassOn = Cast<AMainCharacter>(BlackboardComp->GetValueAsObject(AttackTarget.SelectedKeyName));
		FVector InvestigationPosition = BlackboardComp->GetValueAsVector(PointOfInterestKey.SelectedKeyName);


		return EBTNodeResult::Succeeded;
		
		switch (EnemyState)
		{
		case EEnemyState::Attacking:
			EnemyController->SetStateAsAttacking(AttackTargetToPassOn);
			break;
		case EEnemyState::Investigating:
			EnemyController->SetStateAsInvestigating(InvestigationPosition);
			break;
		case EEnemyState::Passive:
			EnemyController->SetStateAsPassive();
			return EBTNodeResult::Succeeded;
			break;
		case EEnemyState::Death:
			EnemyController->SetStateAsDeath();
			return EBTNodeResult::Succeeded;
		default:
			break;
		}

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}

