#pragma once

//create interface here
class Storage
{
public:
		virtual void append(const std::string& entry) = 0;
};
