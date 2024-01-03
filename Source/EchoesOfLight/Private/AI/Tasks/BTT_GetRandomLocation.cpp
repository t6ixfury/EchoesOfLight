// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTT_GetRandomLocation.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"


EBTNodeResult::Type UBTT_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get black board component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	//get enemy character ref
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (EnemyCharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//get nav mesh ref
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSys == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	//variable to save the results of get randompoint in navigable radius;
	FNavLocation OutLocation;

	//Variable to save the location from the function
	FVector Randomlocation;

	//function to set random variable. if randomlocation is found, returns true
	bool bFound = NavSys->GetRandomPointInNavigableRadius(EnemyCharacter->GetActorLocation(), Radius, OutLocation);

	if (bFound)
	{
		//set randomlocation and set the blackboard key associated with the randomlocation.
		Randomlocation = OutLocation.Location;
		BlackboardComp->SetValueAsVector(RandomLocationOnNavigableArea.SelectedKeyName, Randomlocation);

		return EBTNodeResult::Succeeded;
		
	}

	return EBTNodeResult::Failed;
}
