#include "header.h"
#pragma once


class participant {

private:
    std::string m_Name;
    std::string m_PublicKey;

public:

    participant(std::vector<std::string> names, int id){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);

        int randomName = dis(gen);
        std::string name = names[randomName];

        int randomNumber = dis(gen);
        std::ostringstream ss;
        ss << std::setw(4) << std::setfill('0') << randomNumber;
        std::string filledNumber = ss.str();
        
        m_Name = (name + "#" + filledNumber);

        std::string index = std::to_string(id);
        std::string text = m_Name + index;
        m_PublicKey = hexHashGen(text);
    }

    std::string Name() const { return m_Name; }
    std::string PublicKey() const { return m_PublicKey; }
};