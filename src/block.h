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
    int m_Miner = 0;

    int m_TxNum = 100;   //100 atrenkama 1 blokui

public:

    block() {};
    
    block(vector<block> blockchain, vector<transaction> txPool, int difficultyTarget) {

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();

        m_TX = validTx(blockchain, txPool);

        m_MerkelRootHash = MerkelRoot();

        m_Timestamp = getTimestamp();

        m_Hash = blockHashGen();

    }

    block(vector<wallet> user) {

        m_DifficultyTarget = 0;
        m_PrevHash = "";

        for (wallet w: user) {

            transaction newAnnex(w);
            m_TX.push_back(newAnnex);

        }

        m_MerkelRootHash = MerkelRoot();

        m_Timestamp = getTimestamp();

        m_Hash = blockHashGen();

    }

    string Hash() const { return m_Hash; }
    vector<transaction> Tx() const { return m_TX; }
    void Miner(int miner) { m_Miner = miner; } 

    void Info(int index) {

        string fileRez = "block" + to_string(index) + ".txt";

        ofstream out_r("../blocks/" + fileRez);

        out_r << left << setw(20) << "Block " << index << endl << endl;
        out_r << left << setw(20) << "Details" << endl;
        out_r << left << setw(20) << "Miner: " << m_Miner << endl;
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
    
    //Prideda ir istrina paskutiniame bloke panaudotus utxo
    void UpdateWallets(vector<wallet>& usersPool) { 

        //pridedame utxo


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

        vector<string> treeLeaves;

        for (int i = 0; i < m_TX.size(); i++) {

            treeLeaves.push_back(m_TX[i].Id());

        }

        while (treeLeaves.size() > 1) {
            
            if (treeLeaves.size() % 2 != 0) {
                
                treeLeaves.push_back(treeLeaves.back());

            }

            vector<string> newHashes;
            for (int i = 0; i < treeLeaves.size(); i += 2) {

                newHashes.push_back(hexHashGen(treeLeaves[i] + treeLeaves[i + 1]));

            }

            treeLeaves = newHashes;

        }

        return treeLeaves[0];

    }

    vector<transaction> validTx(vector<block> blockchain, vector<transaction> txPool) {

        vector<transaction> chosenTx;

        vector<int> shuffledTx = genRandomNumbers (txPool.size() - 1);

        vector<wallet> sender;
        vector<double> balance; 
        int n = 0;
        
        while (chosenTx.size() < m_TxNum && n < txPool.size()) {
        
            transaction tx = txPool[shuffledTx[n]];
            
            wallet tempSender = tx.Sender();
            double tempBalance = FindUsersBalance(blockchain, tempSender);
            bool newSender = true;

            int index;
            for (int i = 0; i < sender.size(); i++) {

                if (sender[i].PublicKey() == tx.SenderPkey()) {
                    
                    index = i;

                    tempSender = sender[i];
                    tempBalance = balance[i];

                    newSender = false;
                    break;
                }

            }
            
            if (tempBalance >= tx.Amount()) {

                chosenTx.push_back(tx);
                
                if (newSender) {
                    
                    tempBalance -= tx.Amount();
                    sender.push_back(tempSender);
                    balance.push_back(tempBalance);

                } else {
                
                    balance[index] -= tx.Amount(); 
                
                }

            }

            n++;

        }        

        return chosenTx;

    }

    
    vector<int> genRandomNumbers (int upper) {

        random_device rd;
        mt19937 gen(rd());

        int lower = 0;

        vector<int> numbers(upper - lower + 1);
        std::iota(numbers.begin(), numbers.end(), lower);

        std::shuffle(numbers.begin(), numbers.end(), gen);

        return numbers;

    }

    double FindUsersBalance(vector<block> blockchain, wallet user) {
    
        double balance = 0;

        for (block b: blockchain) {
            
            for (transaction tx: b.Tx()) {
                
                if (tx.SenderPkey() == user.PublicKey()) {
                    
                    balance -= tx.Amount();

                }
                
                if (tx.RecieverPkey() == user.PublicKey()) {
                    
                    balance += tx.Amount();

                }
            
            }
        
        }

        return balance;
    }

};