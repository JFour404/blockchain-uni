#include "header.h"
#pragma once

class wallet {

private:
    
    std::string m_Name;
    std::string m_PublicKey;
    std::vector<string> m_UTXOref;

public:

    wallet() {
        m_Name = "";
        m_PublicKey = "";
        m_UTXOref.clear();
    }

    wallet(std::vector<std::string> names, int id){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);

        int randomNameID = dis(gen) - 1;
        std::string name = names[randomNameID];

        int randomNumber = dis(gen);
        std::ostringstream ss;
        ss << std::setw(4) << std::setfill('0') << randomNumber;
        std::string filledNumber = ss.str();
        
        m_Name = (name + "#" + filledNumber);

        std::string index = std::to_string(id);
        std::string text = m_Name + index;
        m_PublicKey = hexHashGen(text);

        m_UTXOref.clear();

    }

    std::string Name() const { return m_Name; }
    std::string PublicKey() const { return m_PublicKey; }
    std::vector<string> UTXO() const { return m_UTXOref; }

    void UtxoAdd (vector<string> addedUtxo) {

        for (string utxo: addedUtxo) {

            m_UTXOref.push_back(utxo);

        }
        
    }

    void UtxoAdd (string addedUtxo) {

        m_UTXOref.push_back(addedUtxo);

    }

    void UtxoDelete (vector<string> deletedUtxo) {

        m_UTXOref.erase(remove_if(m_UTXOref.begin(), m_UTXOref.end(), [&](const string& m_UTXOref) {
        return find(deletedUtxo.begin(), deletedUtxo.end(), m_UTXOref) != deletedUtxo.end();
        }), m_UTXOref.end());

    }

    void UtxoDelete (string deletedUtxo) {

        m_UTXOref.erase(std::remove(m_UTXOref.begin(), m_UTXOref.end(), deletedUtxo), m_UTXOref.end());

    }

    bool operator==(const wallet& other) const {
        
        return this->m_PublicKey == other.m_PublicKey;
    
    }
};