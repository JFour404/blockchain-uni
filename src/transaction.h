#include "header.h"
#pragma once

class transaction {

private:

    string m_ID;
    vector<string> m_UTXO;

    struct transfer{
        wallet from;
        vector<wallet> to;
        vector<double> amount;

        void clear(){
            from = wallet();
            to.clear();
            amount.clear();
        }
    };

    vector<transfer> m_Transfer;
    transfer m_NewTransfer;

public:

    transaction (vector<wallet>& user) {
        
        random_device rd;
        mt19937 gen(rd());
        std::discrete_distribution<> usersQuantity({80, 15, 2, 1.5, 1, 0.5});
        uniform_int_distribution<> userID(1, user.size());
        uniform_int_distribution<> coinsQuantity(100, 1000000);
        
        int sendersNum = usersQuantity(gen) + 1;

        for(int i = 0; i < sendersNum; i++) {
            
            int randomWalletID = userID(gen) - 1;
            m_NewTransfer.from = user[randomWalletID];

            for (string d: m_NewTransfer.from.UTXO()) {

                m_UTXO.push_back(d);

            }
            
            int randomRecieversQuantity = usersQuantity(gen) + 1;
            for (int j = 0; j < randomRecieversQuantity; j++) {

                randomWalletID = userID(gen) - 1;
                m_NewTransfer.to.push_back(user[randomWalletID]);
                
                int randomCoinsQuantity = coinsQuantity(gen);
                m_NewTransfer.amount.push_back(randomCoinsQuantity);

                m_Transfer.push_back(m_NewTransfer);
                m_NewTransfer.clear();
            
            }
        
        }
    
    }

    void Info () {


        
    }

};