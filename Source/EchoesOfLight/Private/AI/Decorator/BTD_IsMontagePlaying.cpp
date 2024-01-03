// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorator/BTD_IsMontagePlaying.h"
#include "AI/Controllers/EnemyBaseController.h"
#include "EnemyCharacter.h"




void UBTD_IsMontagePlaying::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	USkeletalMeshComponent* EnemyMesh = Enemy ? Enemy->GetMesh() : nullptr;

	UAnimInstance* EnemyAnimInstance = EnemyMesh ? EnemyMesh->GetAnimInstance() : nullptr;

	if (EnemyAnimInstance && Enemy)
	{
		bool HitReactMontageIsPlaying = EnemyAnimInstance->Montage_IsPlaying(Enemy->HitReactMontage);

		if (HitReactMontageIsPlaying)
		{

		}


	}


}
