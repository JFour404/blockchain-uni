#pragma once
#include "header.h"

class participant {

private:
    std::string m_Name;
    std::string m_PublicKey;

public:

    //participant();

    std::string Name() const { return m_Name; }
    void Name (std::string name) { m_Name = name; }
    std::string PublicKey() const { return m_PublicKey; }
};