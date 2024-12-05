#pragma once

//define interface here
class Debitable
{
	public:
		virtual bool debit(unsigned amount) = 0;
};
