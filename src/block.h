#include "header.h"
#pragma once


class block {

private:

    string m_Hash;              // +
    string m_PrevHash;          // +
    string m_Timestamp;         // +
    string m_Version = "v0.2";  // +
    string m_MerkelRootHash;    // + TODO: full implementation
    int m_Nonce = 0;            // +
    int m_DifficultyTarget;     // +
    vector<transaction> m_TX;   // + TODO: validation

    int m_TxQuantity = 5;

public:

    block(vector<block> blockchain, vector<transaction> txPool, int difficultyTarget) {

        m_DifficultyTarget = difficultyTarget;

        m_PrevHash = blockchain.back().Hash();


//         random_device rd;
//         mt19937 gen(rd());

// std::sample(txPool.begin(), txPool.end(), std::back_inserter(m_TX), m_TxQuantity, gen); // TODO: validation check

        m_TX = validTx(blockchain, txPool);

        m_MerkelRootHash = hexHashGen(MerkelRoot());

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

    vector<transaction> validTx(vector<block> blockchain, vector<transaction> txPool) {

        vector<transaction> chosenTx;

        //vector<vector<blockchainApp::reciept>> fundsCheck;

        vector<int> shuffledTx = genRandomNumbers (txPool.size() - 1);

        int i = 0;
        while (chosenTx.size() < m_TxQuantity && i < txPool.size()) {
        
            transaction tx = txPool[shuffledTx[i]];
            
            for (transaction::transfer t: tx.Transfer()) {

                wallet sender = t.from;

                double requiredFunds = 0;
                for (double d: t.amount) { requiredFunds += d; }

                double availableFunds = 0;
                vector<string> usedUtxo;
                
                UsableUtxoFinder(sender, requiredFunds, availableFunds, usedUtxo, blockchain);
                
                // cout << "Required funds: " << requiredFunds << endl;
                // cout << "Available funds: " << availableFunds << endl;

                if (requiredFunds > availableFunds) { break; }

                tx.Utxo(usedUtxo);
                chosenTx.push_back(tx);

            }

            i++;

        }        

        return chosenTx;

    }

    void UsableUtxoFinder(wallet sender, double coinsNeeded, double& foundCoins, vector<string>& usedUtxo, vector<block> blockchain) {

    bool valid = false;
    bool stopLoops = false;
    foundCoins = 0;
    
    vector<string> utxo;
    utxo = sender.UTXO();

//for (string s: utxo ) { cout << s << endl; }

    for (block b: blockchain) {
        if (stopLoops) break;

        for (transaction tx: b.Tx()) {
            if (stopLoops) break;

            auto it = std::find(utxo.begin(), utxo.end(), tx.Id());
            if (it != utxo.end()) {

                for (transaction::transfer t: tx.Transfer()) {
                    if (stopLoops) break;

                    for (int i = 0; i < t.to.size(); i++) {

                        if (t.to[i] == sender) {

                            foundCoins += t.amount[i];
                            usedUtxo.push_back(tx.Id());

                            if (foundCoins > coinsNeeded) {
                                stopLoops = true;
                                break;
                            } 

                        }

                    }

                }

            }

        }

    }

//cout << "Available funds: " << foundCoins << endl;

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

    string MerkelRoot () {

        string tempMerkel = "";

        for (transaction selected: m_TX) {

            tempMerkel += selected.Id();

        }

        return tempMerkel;

    }

};