// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_SetMovementSpeed.h"
#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"

EBTNodeResult::Type UBTT_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy)
	{
		IInterface_EnemyAi* Interface = Cast< IInterface_EnemyAi>(Enemy);
		if (Interface)
		{
			Interface->SetMovementSpeed(NewSpeed);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
