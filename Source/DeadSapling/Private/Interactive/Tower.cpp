// ©2022 The Icecream Connection


#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Settings/DeadSaplingGameInstance.h"



// Sets default values
ATower::ATower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	RootComponent = TowerMesh;
	ActivationRadius = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	ActivationRadius->SetupAttachment(RootComponent);
	ActivationRadius->SetWorldLocation(GetActorLocation());
	ActivationRadius->SetRelativeRotation(GetActorRotation());
	ActivationRadius->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlapActivationRadius);
	ActivationRadius->OnComponentEndOverlap.AddDynamic(this, &ATower::OnOverlapEndActivationRadius);
}

void ATower::Initialize(UDA_TowerInfo* TowerInfo,UStaticMesh* mesh)
{

	if (!IsInitialized)
	{
		// This whole part is dirty as fuck, but tbh: if the turret data is broken the game will crash sooner or later anyhow.
		TowerMesh->SetStaticMesh(mesh);
		TowerMesh->SetCollisionProfileName(TEXT("Pawn"));

		BaseDamage = TowerInfo->BaseDamage;
		DamageType = TowerInfo->DamageType;
		BaseRange = TowerInfo->BaseRange;
		BaseSpeed = TowerInfo->BaseSpeed <= 0? 1 : TowerInfo->BaseSpeed;
		BaseAmmunition = TowerInfo->BaseAmmunition;

		// This Sphere also visually indicates the range of the Tower
		ActivationRadius->SetSphereRadius(BaseRange);
		
	}
	UpdateLoop();
}

void ATower::UpdateLoop()
{
	GetWorldTimerManager().SetTimer(UpdateTimer, this, &ATower::UpdateLoop, 1/BaseSpeed, false);
	if(!Target)
	{
		TArray<AActor*> OverlappingEnemies;
		float Distance;
		ActivationRadius->GetOverlappingActors(OverlappingEnemies, AAI_Character_Base::StaticClass());
		AActor* Actor = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappingEnemies, Distance);
		Target = Actor;
		
	}

	if(Target)
	{
		
		
		// shoot at it.
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.bNoFail = true;
		Params.Owner = this;
		FVector ProjectileLocation = GetActorLocation() + MuzzleLocation;
		ABaseAmmunition* Projectile = GetWorld()->SpawnActor<ABaseAmmunition>(BaseAmmunition, ProjectileLocation, GetActorRotation(), Params);
		if (Projectile)
		{
			// Set the projectile's initial trajectory.
			Projectile->FireInDirection(Target->GetActorLocation());
		}
	}
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
	if (Target)
	{
		//maybe lerp this or something, idk, idc
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
		FRotator Rotator = FRotator(0.0, Rotation.Yaw, 0.0);
		this->SetActorRotation(Rotator);
	}	
}

void ATower::OnOverlapActivationRadius(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(Actor->IsA(AAI_Character_Base::StaticClass()))
	{
		if(!Target)
		{
			Target = Actor;
		}
	}

}

void ATower::OnOverlapEndActivationRadius(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I)
{
	if (Target == Actor)
	{
		Target = nullptr;
	}	
}


