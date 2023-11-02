#include "header.h"


int main (){
    vector<string> names;
    getNames(names);

    vector<wallet> userPool;
    vector<transaction> paymentPool;

    for (int i = 0; i < 1000; i++){

        userPool.push_back(wallet(names, i));

    }
    
    for (int i = 0; i < 10000; i++){

        paymentPool.push_back(transaction(userPool));

    }

    vector<block> testNet;

    block genesis(userPool);
    testNet.push_back(genesis);
    genesis.Info(0);

    for (int i = 0; i < 999; i++){

        block newBlock (testNet, paymentPool, 4);
        testNet.push_back(newBlock);
        newBlock.Info(i+1);

    }
    
    return 0;
}