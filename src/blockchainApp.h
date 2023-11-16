#include "header.h"
#pragma once



class blockchainApp {

    int m_TxNum = 10000;     //10000 naudojama txPool
    int m_UsersNum = 1000;    //1000

public:
    
    void InitializeUsers() {
        
        getNames(m_Names);

        m_UserPool.clear();
        m_UserPool.shrink_to_fit();

        for (int i = 0; i < m_UsersNum; i++) {
            
            m_UserPool.push_back(wallet(m_Names, i));
        
        }

    }

    // void InitializeTransactions() {
        
    //     while (m_PaymentPool.size() < m_TxNum) {
            
    //         transaction newTx(m_UserPool);
    //         wallet sender = newTx.Sender();

    //         if (info.FindUsersBalance(m_LiveNet, sender) >= newTx.Amount() && 
    //         hexHashGen(newTx.TransactionServiceInfo()) == newTx.Id() ) {

    //             m_PaymentPool.push_back(newTx);

    //         }
            
    //     }

    // }

    void CreateGenesisBlock() {

        block genesis(m_UserPool);
        m_LiveNet.push_back(genesis);
        genesis.Info();

    }

    void InitializeTransactionsUtxo() {

        while (m_PaymentPool.size() < m_TxNum) {
            
            transactionUtxo newTx(m_UserPool);
            m_PaymentPool.push_back(newTx);

        }

    }

    void CreateBlocks(int blockChainSize, int difficultyTarget) {

        for (int i = 0; i < blockChainSize; i++) {
            
            m_LiveNet.push_back(blockMining(difficultyTarget));
            m_LiveNet.back().Info();
            info.ReplaceUsedTx(m_LiveNet.back().ChosenTxIndex(), m_PaymentPool, m_UserPool);

        }

    }

    void CreateCustomBlock(transactionUtxo tx, int difficultyTarget) {

        block customBlock(m_LiveNet, tx, difficultyTarget);
        m_LiveNet.push_back(customBlock);
        m_LiveNet.back().Info();

    }

    block blockMining(int difficultyTarget) {
        
        block minedBlock;
        bool blockMined = false;
        int numThreads = 5;

        #pragma omp parallel num_threads(numThreads)
        {
            block localBlock;
            localBlock = block(m_LiveNet, m_PaymentPool, difficultyTarget, blockMined);

            while (!blockMined) {
                
                localBlock.BlockHashGenParallel();
                
                #pragma omp critical
                {
                    if (!blockMined && localBlock.checkHashDifficulty(localBlock.Hash())) {
                        
                        blockMined = true;
                        localBlock.Miner(omp_get_thread_num());
                        minedBlock = localBlock;
                        
                    }
                }
            }
        }

        return minedBlock;
    }

    vector<string> m_Names;
    vector<wallet> m_UserPool;
    vector<transactionUtxo> m_PaymentPool;
    vector<block> m_LiveNet;

    infoNet info;

};