// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Character/AI_Character_Base.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/DeadSaplingCharacter.h"
#include "EnemyAIController.generated.h"

class ARoutePoint;
struct FAIStimulus;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	UFUNCTION()
	ARoutePoint* GetCurrentTarget() const;
	
	UFUNCTION()
	void SetPath(TArray<ARoutePoint*> const NewPath);
	
	UFUNCTION(BlueprintCallable, Category="AI Character")
	ARoutePoint* CalculateNextPathTarget();
	
	UFUNCTION()
	void SetCurrentTarget(ARoutePoint* Element);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	

private:
	UFUNCTION()
	void OnActorSensed(AActor* Actor, FAIStimulus Stimulus);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess = true))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = true))
	TSubclassOf<ADeadSaplingCharacter> PlayerClass;

	TObjectPtr<UAISenseConfig_Sight> SenseConfig_Sight;
	TObjectPtr<UBlackboardData> BlackboardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	FVector InterruptedLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI Character", meta = (AllowPrivateAccess = true))
	ARoutePoint* CurrentPathTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Character", meta = (AllowPrivateAccess= true))
	TArray<ARoutePoint*> Path;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	bool IsChasing = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	float ChasingRange = 2500.f;
};