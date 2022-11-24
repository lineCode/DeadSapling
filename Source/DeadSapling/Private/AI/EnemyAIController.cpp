// ©2022 The Icecream Connection


#include "AI/EnemyAIController.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "VectorTypes.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Player/DeadSaplingCharacter.h"
#include "Routing/RoutePoint.h"
#include "Tree/Tree.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer): Super(
	ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));

	SenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseConfigSight"));

	SenseConfig_Sight.Get()->SightRadius = 2000.f;
	SenseConfig_Sight.Get()->LoseSightRadius = 2500.f;
	SenseConfig_Sight.Get()->PeripheralVisionAngleDegrees = 180.f;
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

FVector AEnemyAIController::CalculateNextPathTarget()
{
	if (!IsRetreating)
	{
		//Usual pathing
		if (FVector::Dist(GetPawn()->GetActorLocation(), CurrentPathTarget->GetActorLocation()) < PathingTolerance)
		{
			if (const int32 PathPosition = this->Path.Find(CurrentPathTarget);
				PathPosition != INDEX_NONE && PathPosition < Path.Num() - 1)
			{
				this->CurrentPathTarget = this->Path[PathPosition + 1];
			}
		}
	}
	else
	{
		// Retreat handling
		if (FVector::Dist(GetPawn()->GetActorLocation(), RetreatPoint) < PathingTolerance)
		{
			IsRetreating = false;
			return this->CurrentPathTarget->GetActorLocation();
		}

		return RetreatPoint;
	}


	return this->CurrentPathTarget->GetActorLocation();
}

void AEnemyAIController::SetRetreatTarget(const FVector RetreatLocation)
{
	if (!IsRetreating)
	{
		this->RetreatPoint = RetreatLocation;
		this->IsRetreating = true;
	}
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

void AEnemyAIController::CheckIfTargetable(AActor* Actor)
{
	const bool bHasBeenSeen = this->PerceptionComponent->GetActorInfo(*GetPawn())->Target == Actor;
	
	DetermineIfEnemyIsTargetable(Actor, bHasBeenSeen);
}

void AEnemyAIController::DetermineIfEnemyIsTargetable(AActor* Actor, bool bHasBeenSeen)
{
	if (bHasBeenSeen)
	{
		const UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(
			GetWorld(), GetPawn()->GetActorLocation(), Actor, NULL);
		if (NavPath && !NavPath->IsPartial())
		{
			if (IsRetreating)
			{
				if (FVector::Dist(RetreatPoint, Actor->GetActorLocation()) < ChasingRange)
				{
					BlackboardComponent->SetValueAsBool("IsEnemyTargetable", true);
					BlackboardComponent->SetValueAsObject("TargetActor", Actor);
					return;
				}
			}
			else
			{
				if (FVector::Dist(GetPawn()->GetActorLocation(), Actor->GetActorLocation()) < ChasingRange)
				{
					BlackboardComponent->SetValueAsBool("IsEnemyTargetable", true);
					SetRetreatTarget(GetPawn()->GetActorLocation());
					BlackboardComponent->SetValueAsObject("TargetActor", Actor);
					return;
				}
			}
		}
	}

	BlackboardComponent->SetValueAsBool("IsEnemyTargetable", false);
	BlackboardComponent->SetValueAsObject("TargetActor", nullptr);
}

void AEnemyAIController::OnActorSensed(AActor* Actor, FAIStimulus Stimulus)
{
	const TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(Actor, Stimulus);

	if (SenseClass == UAISense_Sight::StaticClass())
	{
		if (Actor->GetClass()->IsChildOf(ADeadSaplingCharacter::StaticClass()) || Actor->GetClass()->IsChildOf(ATree::StaticClass()))
		{
			DetermineIfEnemyIsTargetable(Actor, true);
		}
	}
}
