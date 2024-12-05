#pragma once

//define interface here
class MoneyTransferTarget
{
	public:
		virtual void credit(unsigned deposit) = 0;
};
