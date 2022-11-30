// ©2022 The Icecream Connection


#include "BaseAmmunition.h"

#include "AI/Character/AI_Character_Base.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseAmmunition::ABaseAmmunition()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmunition::OnOverlapBegin);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
		
	}


	
	if(!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
		ProjectileMovementComponent->InitialSpeed = 600.0f;
		ProjectileMovementComponent->MaxSpeed = 600.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
		
	}
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void ABaseAmmunition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseAmmunition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseAmmunition::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp) 
	{
		if (OtherActor->GetClass()->IsChildOf(AAI_Character_Base::StaticClass()))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bullet did some Damage to AI Character"));
			this->Destroy();
		}
	}
}

void ABaseAmmunition::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}



