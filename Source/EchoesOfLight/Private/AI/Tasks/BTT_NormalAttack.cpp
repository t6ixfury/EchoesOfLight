// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_NormalAttack.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"



EBTNodeResult::Type UBTT_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    OwnerCompRef = &OwnerComp;

    if (Enemy)
    {
        //binds the OnEnemyhit to be called if the hit reaction montage plays.
        Enemy->OnHit.BindUObject(this, &UBTT_NormalAttack::OnEnemyHit);

        //get the interface of the enemy 
        IInterface_EnemyAi* Interface = Cast<IInterface_EnemyAi>(Enemy);
        if (Interface)
        {
            //call the normal attack and set timer to call SetMontageFinished to end the task.
            float MontageDuration = Interface->NormalAttack();
            Enemy->GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &UBTT_NormalAttack::SetMontageFinished, MontageDuration, false);
        }
    }

    return EBTNodeResult::InProgress;
}

void UBTT_NormalAttack::SetMontageFinished()
{
    if (OwnerCompRef)
    {
        FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded);
    }
}

void UBTT_NormalAttack::OnEnemyHit()
{
    if (OwnerCompRef)
    {
        FinishLatentTask(*OwnerCompRef, EBTNodeResult::Failed);
    }
}

EBTNodeResult::Type UBTT_NormalAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // Clean up: Unbind the hit event and invalidate the timer
    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if (Enemy)
    {
        Enemy->OnHit.Unbind();
    }

    if (Enemy && Enemy->GetWorld())
    {
        Enemy->GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
    }

    return EBTNodeResult::Aborted;
}

