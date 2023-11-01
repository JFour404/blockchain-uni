#include "header.h"
#pragma once

class block {

private:

    string m_Hash;              // +
    string m_PrevHash = "soon";          // +
    string m_Timestamp;         // +
    string m_Version = "v0.1";  // +
    string m_MerkelRootHash;    // + TODO: full implementation
    int m_Nonce = 0;            // +
    int m_DifficultyTarget;     // +
    vector<transaction> m_TX;   // + TODO: validation

public:

    block (vector<block> blockchain, vector<transaction> txPool, int difficultyTarget) {

        m_DifficultyTarget = difficultyTarget;

        //m_PrevHash = blockchain.back().Hash();

        
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


        string tempMerkel = "";

        for (transaction selected: m_TX) {

            tempMerkel += selected.Id();

        }

        m_MerkelRootHash = hexHashGen(tempMerkel);

        m_Hash = blockHashGen();

        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        m_Timestamp = std::ctime(&timestamp);

    }

    string Hash() const { return m_Hash; }
    vector<transaction> Tx() const { return m_TX; }

    void Info(int index) {

        string fileRez = "block" + to_string(index) + ".txt";

        ofstream out_r("../blocks/" + fileRez);

        out_r << left << setw(20) << "Block " << index << endl << endl;
        out_r << left << setw(20) << "Details" << endl;
        out_r << left << setw(20) << "Hash: " << m_Hash << endl;
        out_r << left << setw(20) << "Previous hash: " << m_PrevHash << endl;
        out_r << left << setw(20) << "Mined: " << m_Timestamp << endl;
        out_r << left << setw(20) << "Version: " << m_Version << endl;
        out_r << left << setw(20) << "Merkle Root: " << m_MerkelRootHash << endl;
        out_r << left << setw(20) << "Nonce: " << m_Nonce << endl;
        out_r << left << setw(20) << "Difficulty target: " << m_DifficultyTarget << endl;
        out_r << left << setw(20) << "Transactions: " << m_TX.size() << endl;

    }


private:

    string blockHashGen() {

        string hashText = "";
        string tempText;
        string tempHash;
        hashText = m_PrevHash + m_Timestamp + m_Version + m_MerkelRootHash + to_string(m_DifficultyTarget);

        do {
            m_Nonce++;
            
            tempText = hashText + to_string(m_Nonce);
            tempHash = hexHashGen(tempText);

        } while (checkHashDifficulty(tempHash) == false);

        return tempHash;
    }

    bool checkHashDifficulty(string hash) {
        
        size_t zerosNum = hash.find_first_not_of('0');
        
        if (zerosNum == string::npos) {

            zerosNum = hash.length();

        }

        if (zerosNum >= m_DifficultyTarget) { return true; } else { return false; }

    }

};