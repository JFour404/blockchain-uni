#include "header.h"

class blockchainApp {

public:
    void initializeUsers(vector<string>& names) {
        getNames(names);
        for (int i = 0; i < 1000; i++) {
            userPool.push_back(wallet(names, i));
        }
    }

    void initializeTransactions() {
        for (int i = 0; i < 10000; i++) {
            paymentPool.push_back(transaction(userPool));
        }
    }

    void createGenesisBlock() {
        block genesis(userPool);
        testNet.push_back(genesis);
        genesis.Info(0);
    }

    void createBlocks() {
        for (int i = 0; i < 999; i++) {
            block newBlock (testNet, paymentPool, 4);
            testNet.push_back(newBlock);
            newBlock.Info(i+1);
        }
    }

private:
    vector<wallet> userPool;
    vector<transaction> paymentPool;
    vector<block> testNet;
    
};