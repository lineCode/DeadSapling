// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Character_Base.generated.h"

UCLASS()
class AAI_Character_Base : public ACharacter
{
	GENERATED_BODY()

	FTimerHandle GlowHandle;

public:
	// Sets default values for this character's properties
	AAI_Character_Base();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Character", meta = (AllowPrivateAccess = true))
	int Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI Character", meta = (AllowPrivateAccess = true))
	int MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI Character", meta = (AllowPrivateAccess = true))
	float AttackRange = 500.f;
public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	
	UFUNCTION()
	void HitGlow();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();
};
