#pragma once
#include "header.h"


class blockchainApp {

public:
    
    void UtxoTestCase() {

        InitializeUsers();
        CreateGenesisBlock();
        UpdateWallets();
        InitializeTransactions();

        cout << "Balance of 1st wallet: " << FindBalance(m_UserPool[0]) << endl;
        CreateBlocks(5, 2);
        

        //PrintWalletsInfo();

//-----------------------------------------

        // InitializeUsers();
        // CreateGenesisBlock();

        // cout << m_LiveNet.back().Hash();

        // for (transaction tx: m_LiveNet.back().Tx()) {

        //     cout << tx.Id() << endl;
            
        //     for (transaction::transfer t: tx.Transfer()) {

        //         cout << "wallets:" << endl;
        //         for (wallet w: t.to) {

        //              cout << w.PublicKey() << endl;

        //         }
        //         cout << "----------" << endl;
               

        //     }

        // }


    }

    void InitializeUsers() {
        
        getNames(m_Names);
        
        for (int i = 0; i < 10; i++) {
            
            m_UserPool.push_back(wallet(m_Names, i));
        
        }

    }

    void InitializeTransactions() {
        
        for (int i = 0; i < 10000; i++) {
            
            m_PaymentPool.push_back(transaction(m_UserPool));
        
        }

    }

    void CreateGenesisBlock() {

        block genesis(m_UserPool);
        m_LiveNet.push_back(genesis);
        genesis.Info(0);

    }

    void CreateBlocks(int blockChainSize, int difficultyTarget) {
        
        for (int i = 0; i < blockChainSize; i++) {
            
            block newBlock (m_LiveNet, m_PaymentPool, difficultyTarget);
            m_LiveNet.push_back(newBlock);
            newBlock.Info(i+1);

            UpdateWallets();

            cout << "Balance of 1st wallet: " << FindBalance(m_UserPool[0]) << endl;
        
        }

        

    }

    void UpdateWallets() {

        block latestBlock = m_LiveNet.back();

        for (transaction tx: latestBlock.Tx()) {

            string newUtxo = tx.Id();
            vector<wallet> addedTo;

            //adding utxo to wallets
            for (transaction::transfer t: tx.Transfer()) {

                for (wallet w: t.to) {

                    addedTo.push_back(w);

                }

            }

            for (wallet& w: m_UserPool) {

                if (std::find(addedTo.begin(), addedTo.end(), w) != addedTo.end()){

                    w.UtxoAdd(newUtxo);

                }

            }

            //deleting used utxo from wallets
            vector<wallet> sendFrom;
            vector<vector<string>> utxoToDelete;
            for (transaction::transfer t: tx.Transfer()) {
                
                wallet sender;
                
                auto it = std::find(m_UserPool.begin(), m_UserPool.end(), t.from);

                if (it != m_UserPool.end()) { sender = *it; } 

                double spendCoins = 0;
                for (double coins: t.amount) {

                    spendCoins += coins;

                }

                double foundCoins = 0;
                vector<string> usedUtxo;

                UsableUtxoFinder(sender, spendCoins, foundCoins, usedUtxo);
        
                sendFrom.push_back(sender);
                utxoToDelete.push_back(usedUtxo);

            }

            for (wallet& w: m_UserPool) {

                auto it = std::find(sendFrom.begin(), sendFrom.end(), w);
                if (it != sendFrom.end()){
                    
                    auto index = std::distance(sendFrom.begin(), it);
                    w.UtxoDelete(utxoToDelete[index]);

                }

            }

        }
    
    }

    void UsableUtxoFinder(wallet sender, double coinsNeeded, double& foundCoins, vector<string>& usedUtxo) {

        bool valid = false;
        bool stopLoops = false;
        foundCoins = 0;
        
        vector<string> utxo;
        utxo = sender.UTXO();

        for (block b: m_LiveNet) {
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

        



    }

    struct reciept {

            string utxoID;
            double amount;

    };

    vector<reciept> FindReciept(wallet user) {

        vector<reciept> spreadsheet;
        
        
        for (block b: m_LiveNet) {

            for (transaction tx: b.Tx()) {

                for (auto it = spreadsheet.begin(); it != spreadsheet.end(); ) {
                    
                    if (it->utxoID == tx.Id()) { it = spreadsheet.erase(it);} 
                    else { ++it; }

                }
                
                for (transaction::transfer t: tx.Transfer()) {

                    for (int i = 0; i < t.to.size(); i++) {

                        if (t.to[i] == user) {  

                            reciept temp;
                            temp.utxoID = tx.Id();
                            temp.amount = t.amount[i];

                            spreadsheet.push_back(temp);

                        }

                    }

                }

            }

        }

        return spreadsheet;

    }

    double FindBalance (wallet user) {

        vector<reciept> temp = FindReciept(user);

        double total = 0;

        for (reciept r: temp) {

            total += r.amount;

        }

        return total;

    }

    void PrintWalletsInfo() {

        for (wallet w: m_UserPool) {

            cout << w.Name() << endl;
            cout << w.PublicKey() << endl;
            cout << "UTXO's:" << endl;
            for (string txId: w.UTXO()) { 
                
                cout << txId << endl; 
                
            }
            cout << "-----" << endl;

        }

    }

    vector<string> m_Names;
    vector<wallet> m_UserPool;
    vector<transaction> m_PaymentPool;
    vector<block> m_LiveNet;

};