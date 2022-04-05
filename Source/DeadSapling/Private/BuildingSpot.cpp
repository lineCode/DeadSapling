// ©2022 The Icecream Connection


#include "BuildingSpot.h"

#include "Engine/Engine.h"

// Sets default values
ABuildingSpot::ABuildingSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	BaseMesh->SetupAttachment(RootComponent);

	// Hide Until BuildMenu is active
	BaseMesh->SetVisibility(IsInBuildMode);
}

// Called when the game starts or when spawned
void ABuildingSpot::BeginPlay()
{
	Super::BeginPlay();
	// Listen to OnBuildMenuToggle
	Controller = Cast<ADeadSaplingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Controller->OnBuildMenuToggle.AddDynamic(this, &ABuildingSpot::ToggleBuildMode);
}

// Called every frame
void ABuildingSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuildingSpot::ToggleBuildMode()
{
	IsInBuildMode = !IsInBuildMode;
	RootComponent->SetVisibility(IsInBuildMode);
}

void ABuildingSpot::Interact_Implementation()
{
	// Don't do stuff if not in build mode
	if (IsInBuildMode) {
		UDA_TowerInfo* TowerInfo = Cast<UDA_TowerInfo>(Cast<UDeadSaplingGameInstance>(GetGameInstance())->tower_data.GetData()[0]);

		if (TowerInfo) {
			ATower* NewTower = GetWorld()->SpawnActor<ATower>(GetActorLocation(), GetActorRotation());
			NewTower->Initialize(TowerInfo, GetActorLocation(), GetActorRotation());
		}
		else {
			LOG_ERROR(LogInit, "TowerInfo doesn't exist.");
		}
	}
}

void ABuildingSpot::OnTrace_Implementation()
{
	// Don't do stuff if not in build mode
	if (IsInBuildMode) {
		// TODO: Here activate particle effects / display of tower before building
		if (!IsTraced) {
			IsTraced = true;
			// Listen to OnLeaveTrace
			Controller->OnLeaveTrace.BindDynamic(this, &ABuildingSpot::OnLeaveTrace);
			LOG_SCREENMSG("OnTrace - BuildingSpot");
		}
		
	}
}

void ABuildingSpot::OnLeaveTrace()
{
	if (IsTraced) {
		IsTraced = false;
		// Don't listen to OnLeaveTrace

		LOG_SCREENMSG("OnLeaveTrace - BuildingSpot");
		Controller->OnLeaveTrace.Clear();

	}
}

