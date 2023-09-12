// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_NormalAttack.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"


EBTNodeResult::Type UBTT_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy)
	{
		IInterface_EnemyAi* Interface = Cast< IInterface_EnemyAi>(Enemy);
		if (Interface && NormalAttack)
		{
			float MontageDuration = Interface->Execute_NormalAttack(Enemy,NormalAttack);

			UE_LOG(LogTemp, Warning, TEXT("MontageDuration returned: %f"), MontageDuration);

			return EBTNodeResult::Succeeded;

			
		}
	}

	return EBTNodeResult::Failed;
}
