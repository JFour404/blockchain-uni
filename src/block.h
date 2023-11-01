#include "header.h"
#pragma once

class block {

private:

    string m_Hash;              //
    string m_PrevHash;          // +
    string m_Timestamp;         // +
    string m_Version = "v0.1";  // +
    string m_MerkelRootHash;    //
    int m_Nonce;                //
    int m_DifficultyTarget;     //+
    vector<transaction> m_TX;   //+ reikia validation

public:

    block (vector<block> blockchain, vector<transaction> txPool, int difficultyTarget) {

        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        m_Timestamp = std::ctime(&timestamp);

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();

        
        int lower = 0, upper = txPool.size();
        vector<int> chosenTX(upper - lower + 1);
        std::iota(chosenTX.begin(), chosenTX.end(), lower);

        random_device rd;
        mt19937 gen(rd()); 

        std::shuffle(chosenTX.begin(), chosenTX.end(), gen);

        chosenTX.resize(100);

        for (int txIndex: chosenTX) {

            m_TX.push_back(txPool[txIndex]);

        }



    }

    string Hash() const { return m_Hash; }
    vector<transaction> Tx() const { return m_TX; }

};