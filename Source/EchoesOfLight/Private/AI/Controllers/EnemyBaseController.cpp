
// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controllers/EnemyBaseController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Touch.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AISense_Team.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Character/MainCharacter.h"



AEnemyBaseController::AEnemyBaseController()
{
	//PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	Sensed = E_EnemyAI_Sense::None;
	AiBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
	StateKeyName = TEXT("State");
	PointOfInterestKeyName = TEXT("PointOfInterest");
	AttackTargetKeyName = TEXT("AttackTarget");
}

void AEnemyBaseController::BeginPlay()
{
	Super::BeginPlay();

	if (AiBehaviorTree)
	{
		RunBehaviorTree(AiBehaviorTree);
		if (UseBlackboard(AiBehaviorTree->BlackboardAsset, AiBlackboard))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully initialized the blackboard for AI."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to initialize the blackboard for AI."));
		}

	}

	if (PerceptionComponent)
	{
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEnemyBaseController::AIHandleUpdatedPerception);

	}
	SetStateAsPassive();
}

void AEnemyBaseController::SetStateAsPassive()
{
	if (AiBlackboard)
	{
		AiBlackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(E_EnemyAI_State::Passive));
	}
}

void AEnemyBaseController::SetStateAsInvestigating(FVector Location)
{
	if (AiBlackboard)
	{
		AiBlackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(E_EnemyAI_State::Investigating));
		AiBlackboard->SetValueAsVector(PointOfInterestKeyName, Location);
	}
}

void AEnemyBaseController::SetStateAsDeath()
{
	if (AiBlackboard)
	{
		AiBlackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(E_EnemyAI_State::Death));
	}

}

void AEnemyBaseController::SetStateAsAttacking(AActor* AttackTarget)
{
	if (AiBlackboard)
	{
		AiBlackboard->SetValueAsObject(AttackTargetKeyName, AttackTarget);
		AiBlackboard->SetValueAsEnum(StateKeyName, static_cast<uint8>(E_EnemyAI_State::Attacking));
	}
}

E_EnemyAI_State AEnemyBaseController::GetCurrentState()
{
	if (AiBlackboard)
	{
		
		return static_cast<E_EnemyAI_State>(AiBlackboard->GetValueAsEnum(StateKeyName));
	}

	return E_EnemyAI_State::Passive;
}

void AEnemyBaseController::AICanSenseActor(AActor* SensedActor)
{

	if (PerceptionComponent)
	{
		if (PerceptionComponent->GetActorsPerception(SensedActor, PerceptionInfo))
		{
			for (FAIStimulus ActorStimuli : PerceptionInfo.LastSensedStimuli)
			{
				if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Sight)
				{
					UE_LOG(LogTemp, Warning, TEXT("Sight sense was successfully triggered for actor: %s"), *SensedActor->GetName());
					if (ActorStimuli.WasSuccessfullySensed())
					{
						UE_LOG(LogTemp, Warning, TEXT("Sight sense true"))
						AIHandleSenseSight(SensedActor);
					}

				}
				
				else if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Hearing)
				{
					UE_LOG(LogTemp, Warning, TEXT("Hearing sense was successfully triggered for actor: %s"), *SensedActor->GetName());
					if (ActorStimuli.WasSuccessfullySensed())
					{
						AIHandleSenseHearing(ActorStimuli.StimulusLocation);

					}


				}
				else if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Damage)
				{
					if (ActorStimuli.WasSuccessfullySensed())
					{
						AIHandleSenseDamage(SensedActor);
					}


				}
				else if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Prediction)
				{
					if (ActorStimuli.WasSuccessfullySensed())
					{
						// to be implemented later
					}

				}
				else if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Team)
				{
					if (ActorStimuli.WasSuccessfullySensed())
					{
						// to be implemented later
					}

				}
				else if (AIHandleAiSenseConversion(ActorStimuli.Type) == E_EnemyAI_Sense::Touch)
				{
					if (ActorStimuli.WasSuccessfullySensed())
					{
						// to be implemented later
					}


				}
			}
		}
	}
}

void AEnemyBaseController::AIHandleSenseSight(AActor* SensedActor)
{
	E_EnemyAI_State CurrentState = GetCurrentState();
	switch(CurrentState)
	{
		case E_EnemyAI_State::Passive:
			if (SensedActor == GetPlayerCharacterInWorld(GetWorld()))
			{
				SetStateAsAttacking(SensedActor);
				UE_LOG(LogTemp, Warning, TEXT("Current state: %s"), *UEnum::GetValueAsString(CurrentState));

				UE_LOG(LogTemp, Warning, TEXT("SetStateAsAttacking: % d"), *SensedActor->GetName(), static_cast<uint8>(CurrentState));
			}
			break;

		case E_EnemyAI_State::Investigating:
			if (SensedActor == GetPlayerCharacterInWorld(GetWorld()))
			{
				SetStateAsAttacking(SensedActor);
				
			}
			break;

		default:
			break;

	}
}

void AEnemyBaseController::AIHandleSenseHearing(FVector Location)
{
	switch (GetCurrentState())
	{
		case E_EnemyAI_State::Passive:
			SetStateAsInvestigating(Location);

		case E_EnemyAI_State::Investigating:
			SetStateAsInvestigating(Location);
			break;

		default:
			break;
	}
}

void AEnemyBaseController::AIHandleSenseDamage(AActor* SensedActor)
{
	switch (GetCurrentState())
	{
	case E_EnemyAI_State::Passive:
		SetStateAsAttacking(SensedActor);
		break;

	case E_EnemyAI_State::Investigating:
		SetStateAsAttacking(SensedActor);
		break;

	default:
		break;
	}
}

void AEnemyBaseController::AIHandleUpdatedPerception(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* SensedTarget : UpdatedActors)
	{
		AICanSenseActor(SensedTarget);
	}

}

UBlackboardComponent* AEnemyBaseController::GetEnemyAiControllerBlackBoard()
{
	return AiBlackboard;
}


AMainCharacter* AEnemyBaseController::GetPlayerCharacterInWorld(UWorld* WorldContext)
{
	if (!WorldContext) return nullptr;  // Check for a valid world context

	APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
	if (PlayerController)
	{
		return Cast<AMainCharacter>(PlayerController->GetPawn());
	}

	return nullptr;
}

E_EnemyAI_Sense AEnemyBaseController::AIHandleAiSenseConversion(FAISenseID SenseID)
{
	FAISenseID SightSenseID = UAISense::GetSenseID<UAISense_Sight>();
	FAISenseID HearingSenseID = UAISense::GetSenseID<UAISense_Hearing>();
	FAISenseID DamageSenseID = UAISense::GetSenseID<UAISense_Damage>();
	FAISenseID TouchSenseID = UAISense::GetSenseID<UAISense_Touch>();
	FAISenseID PredictionSenseID = UAISense::GetSenseID<UAISense_Prediction>();
	FAISenseID TeamSenseID = UAISense::GetSenseID<UAISense_Team>();

	if (SenseID == SightSenseID)
	{
		return E_EnemyAI_Sense::Sight;
	}
	else if (SenseID == HearingSenseID)
	{
		return E_EnemyAI_Sense::Hearing;
	}
	else if (SenseID == DamageSenseID)
	{
		return E_EnemyAI_Sense::Damage;
	}
	else if (SenseID == TouchSenseID)
	{
		return E_EnemyAI_Sense::Touch;
	}
	else if (SenseID == PredictionSenseID)
	{
		return E_EnemyAI_Sense::Prediction;
	}
	else if (SenseID == TeamSenseID)
	{
		return E_EnemyAI_Sense::Team;
	}
	else
	{
		return E_EnemyAI_Sense::None;
	}
}



