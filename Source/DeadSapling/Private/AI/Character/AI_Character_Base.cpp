// ©2022 The Icecream Connection


#include "AI/Character/AI_Character_Base.h"

// Sets default values
AAI_Character_Base::AAI_Character_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAI_Character_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Character_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Character_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAI_Character_Base::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,	AActor* DamageCauser)
{
	DamageAmount = FMath::Clamp(DamageAmount, 0, MaxHP);
	OnHit();
	HP -= DamageAmount;
	
	this->GetMesh()->SetRenderCustomDepth(true);

	if (HP <= 0)
	{
		//TODO: Proper Death animation and not just destroy the enemy - maybe? ^^
			/*** //TODO this shit would actually make us push the enemy back and stuff
					FHitResult hitRes;
					FVector impulseDir;
					DamageEvent.GetBestHitInfo(this, DamageCauser, hitRes, impulseDir);
					impulseDir.Normalize();
					 - 
					**/
		OnDeath();
		this->Destroy();
	}
	else {
		GetWorldTimerManager().SetTimer(GlowHandle, this, &AAI_Character_Base::HitGlow, .5f, false);
	}
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AAI_Character_Base::HitGlow()
{
	this->GetMesh()->SetRenderCustomDepth(false);
}
