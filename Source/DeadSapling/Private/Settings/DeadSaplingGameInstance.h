// ©2022 The Icecream Connection

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Engine/GameInstance.h"

#include "DataStructures/DA_TowerInfo.h"

#include "DeadSaplingGameInstance.generated.h"

/**
 * This is the GameInstance Class - here all information about the game, that will be used throughout and don't change over time are stored!
 * Keep it as lightweight as possible, because it will be loaded at the start of the game - he said and aded tower data, but i think it is not feasible in GameState /GameMode.
 *
 */
UCLASS()
class DEADSAPLING_API UDeadSaplingGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameParameters")
	float StartingTreeHealth = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameParameters")
	float StartingCountdown = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameParameters")
	float StartingEnemyCountdown = 30;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameParameters")
	float StartingPlayerMoney = 400;
	
	UPROPERTY(EditAnywhere, Category = "GameParameters")
	float DeathMoneyTax = 0.7;

	UPROPERTY(EditAnywhere, Category = "GameParameters")
	float DeathTimeTax = 30;

	UFUNCTION(BlueprintCallable, Category = "GameParameters")
	void ResetGameParameters();

	UFUNCTION(BlueprintCallable, Category = "GameParameters")
	void KillPlayer();
	
	
	// Changes to the tower (upgrades) have to be def. placed in GameState. The DA_TowerInfo is not to be changed!!
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TowerData")
	TArray<UDA_TowerInfo*> tower_data;
		
	UFUNCTION(BlueprintCallable, Category="Money")
	float GetMoney();
	
	UFUNCTION(BlueprintCallable, Category="Money")
	void SubtractMoney(double Amount);

	UFUNCTION(BlueprintCallable, Category="Money")
	void AddMoney(double Amount);

	UFUNCTION(BlueprintCallable, Category="Money")
	void ChargeDeathTax();

	UFUNCTION(BlueprintCallable, Category="Time")
	float GetGameTime();

	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetEnemyCountdown();

	UFUNCTION(BlueprintCallable, Category = "Time")
	void SetEnemyCountdown(float NewCountdown);
	
	UFUNCTION(BlueprintCallable, Category = "Time")
	void SetWaveCountdown(float NewCountdown);
		
	UFUNCTION(BlueprintCallable, Category = "Time")
	float GetWaveCountdown();

	UFUNCTION(BlueprintCallable, Category="Tree")
	float GetTreeHealth();

	UFUNCTION(BlueprintCallable, Category="Tree")
	void SubtractTreeHealth(float Amount);
	
	UFUNCTION(BlueprintImplementableEvent, Category="Tree")
	void GameLost();
	
private:
	float PlayerMoney;

	float GameTime;

	float TreeHealth;

	float EnemyCountdown;
	
	float WaveCountdown;
};
