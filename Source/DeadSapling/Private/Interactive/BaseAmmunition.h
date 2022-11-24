// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BaseAmmunition.generated.h"

UCLASS()
class DEADSAPLING_API ABaseAmmunition : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseAmmunition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Damage System")
	bool IsEvil = false;

	UPROPERTY(EditDefaultsOnly, Category="Damage System")
	float Damage = 1.0f;

	UPROPERTY(EditAnywhere, Category="Damage System")
	UClass* DamageTypeClass = UDamageType::StaticClass();

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);
};
