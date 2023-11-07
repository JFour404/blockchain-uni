#include "header.h"
#pragma once

class block {

private:

    string m_Hash;              // +
    string m_PrevHash;          // +
    string m_Timestamp;         // +
    string m_Version = "v0.1";  // +
    string m_MerkelRootHash;    // + TODO: full implementation
    int m_Nonce = 0;            // +
    int m_DifficultyTarget;     // +
    vector<transaction> m_TX;   // + TODO: validation

public:

    block(vector<block> blockchain, vector<transaction> txPool, int difficultyTarget) {

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();


        random_device rd;
        mt19937 gen(rd());

        std::sample(txPool.begin(), txPool.end(), std::back_inserter(m_TX), 100, gen);


        m_MerkelRootHash = hexHashGen(MerkelRoot());

        m_Timestamp = getTimestamp();

        m_Hash = blockHashGen();

    }

    block(vector<wallet>& user) {

        m_DifficultyTarget = 0;
        m_PrevHash = "";

        for (wallet& w: user) {

            transaction newAnnex(w);
            m_TX.push_back(newAnnex);

        }

        m_MerkelRootHash = hexHashGen(MerkelRoot());

        m_Timestamp = getTimestamp();

        m_Hash = blockHashGen();

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
        out_r << left << setw(20) << "Difficulty target: " << m_DifficultyTarget << endl << endl << endl;
        out_r << left << setw(20) << "Transactions: " << m_TX.size() << endl;
        out_r << "------------------------------------------------------------------------------------" << endl;
        
        for (int i = 0; i < m_TX.size(); i++) {
            
            out_r << endl;
            out_r << i << " ID: " << m_TX[i].Id() << endl;
            out_r << m_TX[i].TimestampInfo() << endl;

            m_TX[i].FileInfo(out_r);
        }

        out_r.close();

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

    string MerkelRoot () {

        string tempMerkel = "";

        for (transaction selected: m_TX) {

            tempMerkel += selected.Id();

        }

        return tempMerkel;

    }

};