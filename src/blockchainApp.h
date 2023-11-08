#include "header.h"
#pragma once

class blockchainApp {

    int m_TxNum = 1000;     //10000 naudojama txPool
    int m_UsersNum = 10;    //1000

public:
    
    void InitializeUsers() {
        
        getNames(m_Names);
        
        for (int i = 0; i < m_UsersNum; i++) {
            
            m_UserPool.push_back(wallet(m_Names, i));
        
        }

    }

    void InitializeTransactions() {
        
        while (m_PaymentPool.size() < m_TxNum) {
            
            transaction newTx(m_UserPool);
            wallet sender = newTx.Sender();

            if (info.FindUsersBalance(m_LiveNet, sender) >= newTx.Amount()) {

                m_PaymentPool.push_back(newTx);

            }
            
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
        
            info.UpadateWallets(m_LiveNet, m_UserPool);


            // cout << "Pirmosios pinigines info: " << endl;
            // cout << "Name: " << m_UserPool[0].Name() << endl;
            // cout << "Balance: " << info.FindUsersBalance(m_LiveNet, m_UserPool[0]) << endl;
            // cout << "UTXOs: " << endl;
            // for (string s: m_UserPool[0].UTXO()) {

            //     cout << s << endl;

            // }
            // cout << "-----------" << endl;
            
        }

        

    }

    vector<string> m_Names;
    vector<wallet> m_UserPool;
    vector<transaction> m_PaymentPool;
    vector<block> m_LiveNet;

    infoNet info;

};