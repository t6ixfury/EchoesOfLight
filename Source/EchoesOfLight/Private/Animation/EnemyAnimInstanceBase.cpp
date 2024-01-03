// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Animation/EnemyAnimInstanceBase.h"
#include "EnemyCharacter.h"

//engine



void UEnemyAnimInstanceBase::NativeInitializeAnimation()
{
	//enemycharacter reference
	EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	//check to make sure referenct to enemy character is set
	if (EnemyCharacter)
	{
		//Get and set the speed 
		EnemycharacterSpeed = EnemyCharacter->MovementSpeed;
	}

}
