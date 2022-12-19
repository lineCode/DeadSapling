// ©2022 The Icecream Connection


#include "DeadSaplingGameInstance.h"

void UDeadSaplingGameInstance::Init()
{
	Super::Init();

	ResetGameParameters();
}

void UDeadSaplingGameInstance::ResetGameParameters()
{
	PlayerMoney = StartingPlayerMoney;
	TreeHealth = StartingTreeHealth;
	WaveCountdown = StartingCountdown;
	EnemyCountdown = StartingEnemyCountdown;
	GameTime = StartingGameTime;
	GameIsDone = false;
}

void UDeadSaplingGameInstance::KillPlayer()
{
	PlayerMoney = PlayerMoney*DeathMoneyTax;
	//GameTime = GameTime + DeathTimeTax;
}

float UDeadSaplingGameInstance::GetMoney()
{
	return PlayerMoney;
}

void UDeadSaplingGameInstance::SubtractMoney(const double Amount)
{
	PlayerMoney -= Amount;
	if (PlayerMoney < 0) PlayerMoney = 0;
}

auto UDeadSaplingGameInstance::AddMoney(double Amount) -> void
{
	PlayerMoney += Amount;
}

void UDeadSaplingGameInstance::ChargeDeathTax()
{
	PlayerMoney *= 0.7;
}


float UDeadSaplingGameInstance::GetTreeHealth()
{
	return TreeHealth;
}

void UDeadSaplingGameInstance::SubtractTreeHealth(float Amount)
{
	TreeHealth -= Amount;
	if (TreeHealth <= 0)
	{
		TreeHealth = 0;
		GameLost();
	}
}

float UDeadSaplingGameInstance::GetGameTime()
{
	if (GameTime <= 0)
	{
		GameTime = 0;
		if (!GameIsDone)
		{
			GameWon();
			GameIsDone = true;
		}

	}
	return GameTime;
}

float UDeadSaplingGameInstance::GetEnemyCountdown() 
{
	return EnemyCountdown;
}

float UDeadSaplingGameInstance::GetWaveCountdown()
{
	return WaveCountdown;
}

float UDeadSaplingGameInstance::GetWaveCounter()
{
	return WaveCounter;
}

void UDeadSaplingGameInstance::SetGameTime(float NewTime)
{
	GameTime = NewTime;
}

void UDeadSaplingGameInstance::SetEnemyCountdown(float NewCountdown)
{
	EnemyCountdown = NewCountdown;
}


void UDeadSaplingGameInstance::SetWaveCountdown(float NewCountdown)
{
	WaveCountdown = NewCountdown;
}

void UDeadSaplingGameInstance::AddToWaveCounter(float Amount)
{
	WaveCounter += Amount;
}

bool UDeadSaplingGameInstance::GetWaveCounterVisibiliy()
{
	return WaveCounterVisibility;
}

void UDeadSaplingGameInstance::SetWaveCounterVisibiliy(bool NewVisibilty)
{
	WaveCounterVisibility = NewVisibilty;
}

bool UDeadSaplingGameInstance::GetNewWaveHappened()
{
	return NewWaveHappened;
}

void UDeadSaplingGameInstance::SetNewWaveHappened(bool Reset)
{
	NewWaveHappened = Reset;
}