#include "header.h"
#pragma once

class transaction {

private:

    string m_ID; //prideti utxo
    vector<string> m_UTXO;
    string m_Timestamp;

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
        
        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        m_Timestamp = std::ctime(&timestamp);
        
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

        string transactionsInfo;

        for (transfer t: m_Transfer) {

            transactionsInfo += t.from.PublicKey();

            for (int i = 0; i < t.to.size(); i++) {

                transactionsInfo += t.to[i].PublicKey();
                transactionsInfo += t.amount[i];

            }

        }

        string hashText = m_Timestamp + transactionsInfo;

        m_ID = hexHashGen(hashText);
    
    }

    void Info () {
        
        cout << "-----Transaction-----" << endl;
        cout << "ID: " << m_ID << endl;
        cout << m_Timestamp << endl;
        
        vector<wallet> fromList;
        for (transfer d: m_Transfer) {
            
            wallet newSender = d.from;
            auto findSender = find(fromList.begin(), fromList.end(), newSender);
            
            if (findSender == fromList.end()) {

                fromList.push_back(newSender);

            }

        }

        cout << "From: " << endl;
        for (wallet d: fromList) {

            cout << d.PublicKey() << " $ " << "SOON" << endl;

        }
        cout << endl;
//-----------------------------------------------

        vector<wallet> toList;
        vector<double> amountList;
        for (transfer d: m_Transfer) {
            
            for (int i = 0; i < d.to.size(); i++) {

                wallet newReciever = d.to[i];
                auto findReciever = find(toList.begin(), toList.end(), newReciever);

                if (findReciever == toList.end()) {

                    toList.push_back(newReciever);
                    amountList.push_back(d.amount[i]);

                } else {

                    int index = std::distance(toList.begin(), findReciever);
                    amountList[index] += d.amount[i];

                }

            }

        }

        cout << "To: " << endl;
        for (int i = 0; i < toList.size(); i++) {

            cout << toList[i].PublicKey() << " $ " << amountList[i] << endl;

        }
        cout << endl;

        




        
    }

    string Id () const { return m_ID; }

};