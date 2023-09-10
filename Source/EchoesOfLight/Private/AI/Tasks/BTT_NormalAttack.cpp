// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_NormalAttack.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"
#include "EnemyCharacter.h"


EBTNodeResult::Type UBTT_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	CachedOwnerComp = &OwnerComp;

	if (Enemy)
	{
		IInterface_EnemyAi* Interface = Cast< IInterface_EnemyAi>(Enemy);
		if (Interface && NormalAttack)
		{
			float MontageDuration = Interface->Execute_NormalAttack(Enemy,NormalAttack);

			UE_LOG(LogTemp, Warning, TEXT("MontageDuration returned: %f"), MontageDuration);

			GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UBTT_NormalAttack::OnAttackFinish, MontageDuration, false);
		}
	}

	return EBTNodeResult::InProgress;
}

void UBTT_NormalAttack::OnAttackFinish()
{
	UE_LOG(LogTemp, Warning, TEXT("OnAttackFinish function has been called!"));

	FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Succeeded);
}
