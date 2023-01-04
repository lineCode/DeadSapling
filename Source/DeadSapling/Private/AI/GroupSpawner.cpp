// ©2022 The Icecream Connection


#include "AI/GroupSpawner.h"

#include "EnemyAIController.h"
#include "SelectionSet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGroupSpawner::AGroupSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGroupSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AGroupSpawner::SpawnGroup(TArray<ARoutePoint*> GroupPath)
{
	Path = GroupPath;

	MaxSplits = FMath::DivideAndRoundUp(WaveComposition.Num(), 4);
	
	GetWorldTimerManager().SetTimer(UniqueHandle, this, &AGroupSpawner::Spawn, 1.0f, true);

}

void AGroupSpawner::Spawn()
{
	const ARoutePoint* const SpawnPoint = Path[0];
	
	if(this->CurrentSplits < MaxSplits)
	{
		TArray<ASpawnPoints*> SpawnPoints = SpawnPoint->SpawnPoints;

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;

		int SpawnCounter = 0;
		for (int i = (this->CurrentSplits * 4); i < WaveComposition.Num(); i++)
		{
			if (SpawnCounter == 4)
			{
				break;
			}
		
			AAI_Character_Base* NewlySpawned = GetWorld()->SpawnActor<AAI_Character_Base>(
				WaveComposition[i], SpawnPoints[SpawnCounter]->GetActorLocation(), FRotator::ZeroRotator, SpawnInfo);
		
			if (NewlySpawned)
			{
				AEnemyAIController* Controller = Cast<AEnemyAIController>(NewlySpawned->GetController());
				Controller->SetPath(Path);
				Controller->SetCurrentTarget(Path[1]);
			}
		
			SpawnCounter++;
		}
		
		this->CurrentSplits += 1;

	} else
	{
		GetWorldTimerManager().ClearTimer(UniqueHandle);
	}
}
