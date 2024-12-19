#pragma once
 
class UnsupportedSystem
{
public:
    UnsupportedSystem(const std::string p_systemName)
     : m_systemName(std::move(p_systemName))
    {
    }

    std::string getSystemName() const { return m_systemName; }

protected:
    const std::string m_systemName;
};
