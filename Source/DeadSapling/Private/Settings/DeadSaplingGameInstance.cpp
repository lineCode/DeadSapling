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
	GameTime = StartingGameTime;
}

void UDeadSaplingGameInstance::KillPlayer()
{
	PlayerMoney = PlayerMoney*DeathMoneyTax;
	GameTime = GameTime + DeathTimeTax;
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
}

float UDeadSaplingGameInstance::GetGameTime()
{
	return GameTime;
}
