// ©2022 The Icecream Connection


#include "Tower.h"

// Sets default values
ATower::ATower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	TowerMesh->SetupAttachment(RootComponent);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	SphereComponent->SetupAttachment(RootComponent);
}

void ATower::Initialize(UDA_TowerInfo* TowerInfo, FVector Location, FRotator Rotation)
{
	if (!IsInitialized)
	{
		UStaticMesh* newMesh = Cast<UStaticMesh>(TowerInfo->TowerMesh.ResolveObject());

		if (newMesh == nullptr)
		{
			newMesh = Cast<UStaticMesh>(TowerInfo->TowerMesh.TryLoad());
		}

		if (newMesh)
		{
			TowerMesh->SetStaticMesh(newMesh);
			TowerMesh->SetWorldLocation(Location);
			TowerMesh->SetRelativeRotation(Rotation);
			TowerMesh->SetCollisionProfileName(TEXT("Pawn"));

			BaseDamage = TowerInfo->BaseDamage;
			DamageType = TowerInfo->DamageType;
			BaseRange = TowerInfo->BaseRange;

			// TODO: This Sphere should also visually indicate the range of the Tower
			SphereComponent->SetSphereRadius(BaseRange);
			SphereComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
			SphereComponent->SetWorldLocation(Location);
			SphereComponent->SetRelativeRotation(Rotation);
		}
		else
		{
			LOG_ERROR(LogInit, "TowerMesh couldn't be instantiated");
		}
	}
}

void ATower::ToggleDisplayRange()
{
	SphereComponent->SetVisibility(!SphereComponent->GetVisibleFlag());
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
