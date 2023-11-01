#include "header.h"


int main (){
    vector<string> names;
    getNames(names);

    vector<wallet> user;
    vector<transaction> payment;

    for (int i = 0; i < 100; i++){

        user.push_back(wallet(names, i));

    }
    

    for (int i = 0; i < 500; i++){

        payment.push_back(transaction(user));

    }

    vector<block> testNet;

    for (int i = 0; i < 10; i++){

        block newBlock (testNet, payment, 0);
        testNet.push_back(newBlock);
        newBlock.Info(i);

    }
    
    return 0;
}