// ©2022 The Icecream Connection


#include "AI/EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DeadSapling/LogMacros.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"

AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));

	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfigSight"));

	SenseConfig_Sight.Get()->SightRadius = 2000.f;
	SenseConfig_Sight.Get()->LoseSightRadius = 2500.f;
	SenseConfig_Sight.Get()->PeripheralVisionAngleDegrees = 360.f;
	SenseConfig_Sight.Get()->SetMaxAge(5.f);
	SenseConfig_Sight.Get()->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfig_Sight.Get()->DetectionByAffiliation.bDetectFriendlies = true;
	SenseConfig_Sight.Get()->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent.Get()->ConfigureSense(*SenseConfig_Sight);
	AIPerceptionComponent.Get()->SetDominantSense(*SenseConfig_Sight->GetSenseImplementation());
}

ARoutePoint* AEnemyAIController::GetCurrentTarget() const
{
	return this->CurrentPathTarget;
}


void AEnemyAIController::SetPath(TArray<ARoutePoint*> const NewPath)
{
	this->Path = NewPath;
}

ARoutePoint* AEnemyAIController::CalculateNextPathTarget()
{
	if (const int32 PathPosition = this->Path.Find(CurrentPathTarget); PathPosition != INDEX_NONE && PathPosition < Path
		.Num() - 1)
	{
		this->CurrentPathTarget = this->Path[PathPosition + 1];
	}
	else
	{
		LOG_ERROR(LogInit, "No More Targets, but still queried for targets!");
	}

	return this->CurrentPathTarget;
}

void AEnemyAIController::SetCurrentTarget(ARoutePoint* Element)
{
	this->CurrentPathTarget = Element;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	AIPerceptionComponent.Get()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnActorSensed);

	if (IsValid(BlackboardData.Get()))
	{
		UseBlackboard(BlackboardData.Get(), BlackboardComponent);
	}

	if (IsValid(BehaviorTree.Get()))
	{
		RunBehaviorTree(BehaviorTree.Get());
		BehaviorTreeComponent->StartTree(*BehaviorTree.Get());
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard.Get()) && IsValid(BehaviorTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree.Get()->BlackboardAsset.Get());
	}
}

void AEnemyAIController::OnActorSensed(AActor* Actor, FAIStimulus Stimulus)
{
	const TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(Actor, Stimulus);

	if (SenseClass == UAISense_Sight::StaticClass())
	{
		if(Stimulus.WasSuccessfullySensed())
		{
			if (Actor->GetClass() == PlayerClass)
			{
				BlackboardComponent->SetValueAsBool("PlayerSpotted", true);
				BlackboardComponent->SetValueAsVector("TargetLocation", Stimulus.StimulusLocation);
				BlackboardComponent->SetValueAsObject("TargetActor", Actor);
			}
		} else
		{
			BlackboardComponent->SetValueAsBool("PlayerSpotted", false);
		}
	}
}
