// ©2022 The Icecream Connection


#include "DeadSaplingGameInstance.h"

double UDeadSaplingGameInstance::GetPlayerMoney()
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
