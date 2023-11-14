#include "header.h"
#pragma once



class blockchainApp {

    int m_TxNum = 10000;     //10000 naudojama txPool
    int m_UsersNum = 1000;    //1000

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

            if (info.FindUsersBalance(m_LiveNet, sender) >= newTx.Amount() && 
            hexHashGen(newTx.TransactionServiceInfo()) == newTx.Id() ) {

                m_PaymentPool.push_back(newTx);

            }
            
        }

    }

    void CreateGenesisBlock() {

        block genesis(m_UserPool);
        m_LiveNet.push_back(genesis);
        genesis.Info();

    }

    void CreateBlocks(int blockChainSize, int difficultyTarget) {

        for (int i = 0; i < blockChainSize; i++) {
            
            m_LiveNet.push_back(blockMining(difficultyTarget));
            m_LiveNet.back().Info();

        }

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
    
    









    void Mining(int difficultyTarget) {

        int numMiners = 5;
        omp_set_num_threads(numMiners);
        bool blockMined = false;
        block newBlock(m_LiveNet, m_PaymentPool, difficultyTarget);

        #pragma omp parallel shared(blockMined, newBlock)
        {
            #pragma omp for
            for(int i = 0; i < omp_get_num_threads(); i++)
            {
                if(!blockMined)
                {
                    #pragma omp critical
                    {
                        if(!blockMined)
                        {
                            newBlock.Miner(i);
                            
                            #pragma omp atomic write
                            blockMined = true;
                            
                            m_LiveNet.push_back(newBlock);
                            newBlock.Info();

                            info.UpadateWallets(m_LiveNet, m_UserPool);
                        }
                    }
                }
            }
        }
    }

    vector<string> m_Names;
    vector<wallet> m_UserPool;
    vector<transaction> m_PaymentPool;
    vector<block> m_LiveNet;

    infoNet info;

};