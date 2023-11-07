#include "header.h"

class blockchainApp {

public:
    
    void InitializeUsers() {
        
        getNames(m_Names);
        
        for (int i = 0; i < 1000; i++) {
            
            m_UserPool.push_back(wallet(m_Names, i));
        
        }

    }

    void InitializeTransactions() {
        
        for (int i = 0; i < 1000; i++) {
            
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
        
        }

    }

    vector<string> m_Names;
    vector<wallet> m_UserPool;
    vector<transaction> m_PaymentPool;
    vector<block> m_LiveNet;

};