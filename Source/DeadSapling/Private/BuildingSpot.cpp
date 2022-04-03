// ©2022 The Icecream Connection


#include "BuildingSpot.h"

#include "Engine/Engine.h"




// Sets default values
ABuildingSpot::ABuildingSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	// Hide Until BuildMenu is active
	RootComponent->SetVisibility(IsInBuildMode);
}

// Called when the game starts or when spawned
void ABuildingSpot::BeginPlay()
{
	Super::BeginPlay();
	// Listen to OnBuildMenuToggle
	Cast<ADeadSaplingPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->onBuildMenuToggle.AddDynamic(this, &ABuildingSpot::ToggleBuildMode);
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
	if (IsInBuildMode) {
	//TODO: Here we should get the Mesh from GameState
	GEngine->AddOnScreenDebugMessage(1, 2, FColor::Green, TEXT("Building Spot: Interact WORKS"));
	}
}

void ABuildingSpot::OnTrace_Implementation()
{
	if (IsInBuildMode) {
		// TODO: Here activate particle effects / display of tower before building
		GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, TEXT("Building Spot: Trace WORKS"));
	}
}

