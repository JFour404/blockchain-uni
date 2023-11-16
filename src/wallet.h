#include "header.h"
#pragma once

class wallet {

public:

    struct utxo
    {
        string txId;
        int outputNum;
        double value = 0;

        bool operator==(const utxo& other) const {
            
            return txId == other.txId && outputNum == other.outputNum;
        
        }
    };

private:
    
    std::string m_Name;
    std::string m_PublicKey;
    std::vector<utxo> m_UTXO;

public:

    wallet() {
        m_Name = "";
        m_PublicKey = "";
        m_UTXO.clear();
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

        m_UTXO.clear();

    }

    std::string Name() const { return m_Name; }
    std::string PublicKey() const { return m_PublicKey; }
    std::vector<utxo> UTXO() const { return m_UTXO; }

    void UtxoAdd (vector<utxo> addedUtxo) {

        for (utxo u: addedUtxo) {

            m_UTXO.push_back(u);

        }
        
    }

    void UtxoAdd (utxo addedUtxo) {

        m_UTXO.push_back(addedUtxo);

    }

    void UtxoDelete (vector<utxo> deletedUtxo) {

        m_UTXO.erase(remove_if(m_UTXO.begin(), m_UTXO.end(), [&](const utxo& m_UTXO) {
        return find(deletedUtxo.begin(), deletedUtxo.end(), m_UTXO) != deletedUtxo.end();
        }), m_UTXO.end());

    }

    void UtxoDelete (utxo deletedUtxo) {

        m_UTXO.erase(std::remove(m_UTXO.begin(), m_UTXO.end(), deletedUtxo), m_UTXO.end());

    }

    bool operator==(const wallet& other) const {
        
        return this->m_PublicKey == other.m_PublicKey;
    
    }

};