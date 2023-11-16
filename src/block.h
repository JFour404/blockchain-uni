#include "header.h"
#pragma once

class block {

private:

    int m_BlockIndex;
    string m_Hash = "";         // +
    string m_PrevHash;          // +
    string m_Timestamp;         // +
    string m_Version = "v0.3";  // +
    string m_MerkelRootHash;    
    int m_Nonce = 0;            // +
    int m_DifficultyTarget;     // +
    vector<transactionUtxo> m_TXutxo;
    vector<int> m_ChosenTxIndex;
    int m_Miner = 0;
    string hashText;

    int m_TxNum = 100;   //100 atrenkama 1 blokui

public:

    block() : m_PrevHash(""), m_Timestamp(""), m_Version("v0.3"), m_MerkelRootHash(""), 
              m_Nonce(0), m_DifficultyTarget(0), m_Miner(0), hashText(""), m_TxNum(100) {}

    block(vector<block> blockchain, vector<transactionUtxo> txPool, int difficultyTarget, bool blockMined) {

        m_BlockIndex = blockchain.size();

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();

        m_TXutxo = validTx(blockchain, txPool);

        m_MerkelRootHash = MerkelRoot();

        m_Timestamp = getTimestamp();
        
        hashText = m_PrevHash + m_Timestamp + m_Version + m_MerkelRootHash + to_string(m_DifficultyTarget);

    }

    //for custom tx
    block(vector<block> blockchain, transactionUtxo tx, int difficultyTarget) {

        m_BlockIndex = blockchain.size();

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();

        vector<transactionUtxo> temp;
        temp.push_back(tx);
        m_TXutxo = validTx(blockchain, temp);
        if (m_TXutxo.empty()) { cout << "Tx is invalid" << endl; }

        m_MerkelRootHash = MerkelRoot();

        m_Timestamp = getTimestamp();
        
        hashText = m_PrevHash + m_Timestamp + m_Version + m_MerkelRootHash + to_string(m_DifficultyTarget);
        
        m_Hash = blockHashGen();

    }

    block(vector<wallet> userPool) {

        m_BlockIndex = 0;

        m_DifficultyTarget = 0;

        m_PrevHash = "";

        for (wallet w: userPool) {

            transactionUtxo newAnnex(w);
            m_TXutxo.push_back(newAnnex);

        }

        m_MerkelRootHash = MerkelRoot();

        m_Timestamp = getTimestamp();

        m_Hash = blockHashGen();

    }

    string Hash() const { return m_Hash; }
    vector<transactionUtxo> Tx() const { return m_TXutxo; }
    vector<int> ChosenTxIndex() const { return m_ChosenTxIndex; }
    int Index() const { return m_BlockIndex; }
    void Miner(int miner) { m_Miner = miner; } 


    void BlockHashGenParallel() {
        
        string tempText;
        string tempHash;

        m_Nonce++;
        
        tempText = hashText + to_string(m_Nonce);
        tempHash = hexHashGen(tempText);

        if (checkHashDifficulty(tempHash) == true) {

            m_Hash = tempHash;
            hashText.clear();

        } 

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

public:

    void Info() {

        string fileRez = "block" + to_string(m_BlockIndex) + ".txt";

        Print (fileRez);

    }

    void Info(string fileRez) {

       Print(fileRez);

    }
    
private:

    void Print(string fileRez) {

        ofstream out_r("../blocks/" + fileRez);

        out_r << left << setw(20) << "Block " << m_BlockIndex << endl << endl;
        out_r << left << setw(20) << "Details" << endl;
        out_r << left << setw(20) << "Miner: " << m_Miner << endl;
        out_r << left << setw(20) << "Hash: " << m_Hash << endl;
        out_r << left << setw(20) << "Previous hash: " << m_PrevHash << endl;
        out_r << left << setw(20) << "Mined: " << m_Timestamp << endl;
        out_r << left << setw(20) << "Version: " << m_Version << endl;
        out_r << left << setw(20) << "Merkle Root: " << m_MerkelRootHash << endl;
        out_r << left << setw(20) << "Nonce: " << m_Nonce << endl;
        out_r << left << setw(20) << "Difficulty target: " << m_DifficultyTarget << endl << endl << endl;
        out_r << left << setw(20) << "Transactions: " << m_TXutxo.size() << endl;
        
        for (int i = 0; i < m_TXutxo.size(); i++) {
            
            m_TXutxo[i].FileInfo(out_r);

        }

        out_r.close();

    }

public:

    //Prideda ir istrina paskutiniame bloke panaudotus utxo
    void UpdateWallets(vector<wallet>& usersPool) { 

        //pridedame utxo


    }

    bool checkHashDifficulty(string hash) {
        
        size_t zerosNum = hash.find_first_not_of('0');
        
        if (zerosNum == string::npos) {

            zerosNum = hash.length();

        }

        if (zerosNum >= m_DifficultyTarget) { return true; } else { return false; }

    }

private:

    string MerkelRoot () {

        if (m_TXutxo.empty()) {

            return "";

        }

        else {

            vector<string> treeLeaves;
            
            for (int i = 0; i < m_TXutxo.size(); i++) {

                treeLeaves.push_back(m_TXutxo[i].Id());

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
        
    }

    vector<transactionUtxo> validTx(vector<block> blockchain, vector<transactionUtxo> txPool) {

        vector<transactionUtxo> chosenTx;

        vector<int> shuffledTx = genRandomNumbers (txPool.size() - 1);

        vector<wallet> sender;
        vector<double> balance; 
        int n = 0;
        
        while (chosenTx.size() < m_TxNum && n < txPool.size()) {
        
            transactionUtxo tx = txPool[shuffledTx[n]];
            
            wallet tempSender = tx.Transfer().from;
            double tempBalance = FindUsersBalance(blockchain, tempSender);
            bool newSender = true;

            int index;
            for (int i = 0; i < sender.size(); i++) {

                if (sender[i].PublicKey() == tx.Transfer().from.PublicKey()) {
                    
                    index = i;

                    tempSender = sender[i];
                    tempBalance = balance[i];

                    newSender = false;
                    break;
                }

            }
            
            if (tempBalance >= tx.Transfer().funds) {

                chosenTx.push_back(tx);
                m_ChosenTxIndex.push_back(shuffledTx[n]);
                
                if (newSender) {
                    
                    tempBalance -= tx.Transfer().funds;
                    sender.push_back(tempSender);
                    balance.push_back(tempBalance);

                } else {
                
                    balance[index] -= tx.Transfer().funds; 
                
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
            
            for (transactionUtxo tx: b.Tx()) {
                
                if (tx.Transfer().from.PublicKey() == user.PublicKey()) {
                    
                    balance -= tx.Transfer().funds;

                }
                
                if (tx.Transfer().to.PublicKey() == user.PublicKey()) {
                    
                    balance += tx.Transfer().funds;

                }
            
            }
        
        }

        return balance;
    }

};