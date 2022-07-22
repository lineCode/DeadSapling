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
		if (OtherActor->GetClass()->IsChildOf(AAI_Character_Base::StaticClass()) && IsEvil)
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Bullet did some Damage to AI Character"));
			this->Destroy();
		}
	}
}



