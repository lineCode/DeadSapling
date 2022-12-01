// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Tree/Tree.h"
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
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category="AI Controller")
	TSubclassOf<ATree> TreeRef;
	
	UFUNCTION()
	ARoutePoint* GetCurrentTarget() const;
	
	UFUNCTION()
	void SetPath(TArray<ARoutePoint*> const NewPath);
	
	UFUNCTION(BlueprintCallable, Category="AI Controller")
	FVector CalculateNextPathTarget();

	UFUNCTION(BlueprintCallable, Category="AI Controller")
	void SetRetreatTarget(FVector RetreatPoint);
	
	UFUNCTION()
	void SetCurrentTarget(ARoutePoint* Element);

	UFUNCTION(BlueprintCallable, Category="AI Controller")
	void CheckIfTargetable(AActor* Actor);

	bool HasTreeBeenSeen = false;
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	void DetermineIfEnemyIsTargetable(AActor* Actor, bool bHasBeenSeen);	


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
	
	TObjectPtr<UAISenseConfig_Sight> SenseConfig_Sight;
	TObjectPtr<UBlackboardData> BlackboardData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	FVector RetreatPoint;

	UPROPERTY()
	bool IsRetreating = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI Character", meta = (AllowPrivateAccess = true))
	ARoutePoint* CurrentPathTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Character", meta = (AllowPrivateAccess= true))
	TArray<ARoutePoint*> Path;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess=true))
	bool IsChasing = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	float ChasingRange = 2500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AI", meta=(AllowPrivateAccess=true))
	float PathingTolerance = 100.f;
};