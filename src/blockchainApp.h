#pragma once
#include "header.h"


class blockchainApp {

public:
    
    void UtxoTestCase() {

        InitializeUsers();
        InitializeTransactions();
        CreateGenesisBlock();
        UpdateWallets();
        CreateBlocks(5, 2);
        PrintWalletsInfo();

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
        
        }

    }

    void UpdateWallets() {

        block latestBlock = m_LiveNet.back();

        for (transaction tx: latestBlock.Tx()) {

            string newUtxo = tx.Id();
            vector<wallet> addedTo;

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

            

        }
    
    }

    void ValidateTransaction(wallet sender, double coinsNeeded, double& foundCoins, vector<string>& usedUtxo) {

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

        if (coinsNeeded > foundCoins) {

            usedUtxo[0] = "insuficient";

        }




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