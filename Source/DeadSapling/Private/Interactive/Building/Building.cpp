﻿// ©2022 The Icecream Connection


#include "Building.h"

#include "BuildingGrid.h"
#include "Interactive/Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Settings/DeadSaplingGameInstance.h"


// Sets default values
ABuilding::ABuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	// Hide Until BuildMenu is active
	BaseMesh->SetVisibility(false);
}

void ABuilding::Initialize(ABuildingGrid* BuildingGrid)
{
	if (BuildingGrid)
	{
		this->BuildingGridRef = BuildingGrid;
	}
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	GameInstance = Cast<UDeadSaplingGameInstance>(GetGameInstance());
	Controller = Cast<ADeadSaplingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Controller->OnBuildMenuToggle.AddDynamic(this, &ABuilding::ToggleBuildMode);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::ToggleBuildMode()
{
	IsInBuildMode = !IsInBuildMode;

	if (!BuiltTower)
	{
		BaseMesh->SetVisibility(IsInBuildMode);
	}
}

void ABuilding::Interact_Implementation()
{
	if (!IsInBuildMode) return;

	// TODO: Right now we can only buy somewhere once. this should be fixed at some point
	if (BuiltTower) return;

	if (UDA_TowerInfo* TowerInfo = Cast<UDA_TowerInfo>(GameInstance->tower_data.GetData()[0]))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.bNoFail = true;
		Params.Owner = this;

		BuiltTower = GetWorld()->SpawnActor<ATower>(TowerInfo->TowerBase, GetActorLocation(), GetActorRotation(),
		                                            Params);
		if (GameInstance->GetPlayerMoney() >= TowerInfo->TowerCost)
		{
			BuiltTower->Initialize(TowerInfo, TowerInfo->TowerMesh);
			GameInstance->SubtractMoney(TowerInfo->TowerCost);
			// This is a very simplistic implementation, revisit this when selling /rebuilding is possible
			BuildingGridRef->GridWeight += TowerInfo->TowerWeight;
			GetWorldTimerManager().ClearTimer(TimerTraceLeave);
			CleanUp();
		}
	}
	else
	{
		LOG_ERROR(LogInit, "TowerInfo doesn't exist!");
	}
}


void ABuilding::OnTrace_Implementation()
{
	if (!IsInBuildMode) return;

	//Mark the current selection

	SetSelectedVisual();

	// TODO: Right now we can only buy somewhere once. this should be fixed at some point
	if (BuiltTower) return;

	// TODO: Here activate particle effects / display of tower before building
	if (!IsTraced)
	{
		IsTraced = true;
		if (UDA_TowerInfo* TowerInfo = Cast<UDA_TowerInfo>(GameInstance->tower_data.GetData()[0]))
		{
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			Params.bNoFail = true;
			Params.Owner = this;

			BaseMesh->SetVisibility(false);

			this->TowerPreview = GetWorld()->SpawnActor<ATower>(TowerInfo->TowerBase, GetActorLocation(),
			                                                    GetActorRotation(), Params);
			if (TowerPreview)
			{
				if (GameInstance->GetPlayerMoney() > TowerInfo->TowerCost)
				{
					this->TowerPreview->Initialize(TowerInfo, TowerInfo->PreviewMesh);
				}
				else
				{
					this->TowerPreview->Initialize(TowerInfo, TowerInfo->NoMoneyMesh);
				}
			}
		}
		else
		{
			LOG_ERROR(LogInit, "TowerInfo doesn't exist!");
		}
		//Set a call to on leaveTrace if there was no trace for 0.2s
		GetWorldTimerManager().SetTimer(TimerTraceLeave, this, &ABuilding::OnLeaveTrace, 0.25f, false);
	}
}

void ABuilding::OnLeaveTrace()
{
	if (IsTraced)
	{
		IsTraced = false;
		CleanUp();
	}
}

void ABuilding::CleanUp()
{
	BaseMesh->SetVisibility(!BuiltTower && IsInBuildMode);
	
	if (TowerPreview)
	{
		TowerPreview->Destroy();
	}
	BuildingGridRef->SelectionMesh->SetVisibility(false);
}

void ABuilding::SetSelectedVisual()
{
	UProceduralMeshComponent* pmc = BuildingGridRef->SelectionMesh;
	FVector Location = FVector(GetActorLocation().X - (BuildingGridRef->HalfTileSize),
	                           GetActorLocation().Y - (BuildingGridRef->HalfTileSize), 111);
	pmc->SetWorldLocation(Location);
	pmc->SetVisibility(true);
}