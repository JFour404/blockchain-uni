#include "header.h"
#pragma once

class transaction {

private:

    string m_Timestamp;
    string m_ID;
    
    vector<string> m_UTXO;
    wallet m_Sender;
    wallet m_Reciever;
    double m_Amount;

    void Timestamp() {

        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        m_Timestamp = std::ctime(&timestamp);

    }
    
public:

    transaction(vector<wallet>& userPool) {
        
        Timestamp();
        
        random_device rd;
        mt19937 gen(rd());
        
        uniform_int_distribution<> userID(1, userPool.size());
        uniform_int_distribution<> coinsQuantity(10, 100000);
        
        int randomWalletID1 = userID(gen) - 1;
        m_Sender = userPool[randomWalletID1];

        int randomWalletID2;
        do { randomWalletID2 = userID(gen) - 1; } while (randomWalletID1 == randomWalletID2);
        m_Reciever = userPool[randomWalletID2];
        
        int randomCoinsQuantity = coinsQuantity(gen);
        m_Amount = randomCoinsQuantity;

    
        m_ID = hexHashGen(TransactionServiceInfo());
    
    }

    //for genesis block
    transaction(wallet user) {    
        
        Timestamp();

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution coins(100, 1000000);
        double mintedCoins = coins(gen);

        m_Reciever = user;
        m_Amount = mintedCoins;
        
        m_ID = hexHashGen(TransactionServiceInfo());

    }


    string TransactionServiceInfo() {

        string transactionsInfo;

        transactionsInfo += m_Sender.PublicKey();

        transactionsInfo += m_Reciever.PublicKey();
        transactionsInfo += m_Amount;
            
        for (string utxo: m_UTXO) {

            transactionsInfo += utxo;

        }

        return (m_Timestamp + transactionsInfo);

    }

    void CmdInfo() {
        
        cout << "-----Transaction-----" << endl;
        cout << "ID: " << m_ID << endl;
        cout << m_Timestamp << endl;
        cout << "From: " << endl;
        cout << m_Sender.PublicKey() << " $ " << "Balance" << endl;
        cout << "To: " << endl;
        cout << m_Reciever.PublicKey() << " $ " << m_Amount << endl;
        cout << "-----------------------------------------------------------------------------" << endl;

    }
    
    void FileInfo(ofstream& out_r) {
        
        out_r << "From: " << endl;
        out_r << m_Sender.PublicKey() << " $ " << "Balance" << endl;
        out_r << "To: " << endl;
        out_r << m_Reciever.PublicKey() << " $ " << m_Amount << endl;
        out_r << endl;
        out_r << "------------------------------------------------------------------------------------" << endl;
    
    }

    string Id() const { return m_ID; }
    string TimestampInfo() const { return m_Timestamp; }
    vector<string> Utxo() const { return m_UTXO; }
    double Amount() const { return m_Amount; }
    string SenderPkey() const { return m_Sender.PublicKey(); }
    string RecieverPkey() const { return m_Reciever.PublicKey(); }
    wallet Sender() const { return m_Sender; }

};