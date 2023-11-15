#include "header.h"
#pragma once

class transactionUtxo {

public:

    struct input {

        wallet sender;
        vector <wallet::utxo> usedUtxo;
        double balance; //TODO: automaticly calculate 

    };

    struct output {

        wallet reciever;
        double amount;

    };

private:

    string m_Timestamp;
    string m_ID;
    
    vector<input> m_Input;
    vector<output> m_Output;
    
    void Timestamp() {

        auto now = std::chrono::system_clock::now();
        time_t timestamp = std::chrono::system_clock::to_time_t(now);
        m_Timestamp = std::ctime(&timestamp);

    }
    
public:

    transactionUtxo(vector<wallet>& userPool) {
        
        Timestamp();
        
        random_device rd;
        mt19937 gen(rd());
        
        uniform_int_distribution<> userID(1, userPool.size());
        uniform_int_distribution<> coinsQuantity(10, 100000);
        
        input tempInput;
        int randomWalletID1 = userID(gen) - 1;
        tempInput.sender = userPool[randomWalletID1];
        wallet::utxo tempUtxo;
        tempUtxo.txId = "Waiting for validation...";
        tempInput.usedUtxo.push_back(tempUtxo); 
        m_Input.push_back(tempInput);

        output tempOutput;
        int randomWalletID2;
        do { randomWalletID2 = userID(gen) - 1; } while (randomWalletID1 == randomWalletID2);
        tempOutput.reciever = userPool[randomWalletID2];
        
        int randomCoinsQuantity = coinsQuantity(gen);
        tempOutput.amount = randomCoinsQuantity;
        m_Output.push_back(tempOutput);

    
        m_ID = hexHashGen(TransactionServiceInfo());
    
    }

    //for genesis block
    transactionUtxo(wallet user) {    
        
        Timestamp();

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution coins(100, 1000000);
        double mintedCoins = coins(gen);

        output genesis;
        genesis.reciever = user;
        genesis.amount = mintedCoins;

        m_Output.push_back(genesis);
        
        m_ID = hexHashGen(TransactionServiceInfo());

    }


    string TransactionServiceInfo() {

        string transactionsInfo;

        for (input i: m_Input) {

            transactionsInfo += i.sender.PublicKey();

            for (wallet::utxo u: i.usedUtxo) {

                transactionsInfo += u.txId;
                transactionsInfo += u.outputNum;

            }

        }

        for (output o: m_Output) {

            transactionsInfo += o.reciever.PublicKey();
            transactionsInfo += o.amount;

        }

        return (m_Timestamp + transactionsInfo);

    }

    void CmdInfo() {
        
        cout << "-------------------------------------$$-------------------------------------" << endl;
        cout << "Transaction " << m_ID << endl;
        cout << m_Timestamp << endl;
        cout << "INPUTS:" << endl;
        
        for (input i: m_Input) {

            for (wallet::utxo u: i.usedUtxo) {

                cout << u.txId << " : " << u.outputNum << endl;
                cout << right << setw(26) << i.sender.Name() << setw(50) << "Utxo Value" << endl;
                cout << endl;

            }

        }

        cout << "OUTPUTS:" << endl;

        for (int i = 0; i < m_Output.size(); i++) {

            cout << "#" << i << " " << right << setw(23) << m_Output[i].reciever.Name() << setw(50) << m_Output[i].amount << endl; 

        }
        
        cout << "----------------------------------------------------------------------------" << endl;

    }
    
    void FileInfo(ofstream& out_r) {
        
        out_r << "----------------------------------------------------------------------------" << endl;
        out_r << "Transaction " << m_ID << endl;
        out_r << m_Timestamp << endl;
        out_r << "INPUTS:" << endl;
        
        for (input i: m_Input) {

            for (wallet::utxo u: i.usedUtxo) {

                out_r << u.txId << " : " << u.outputNum << endl;
                out_r << right << setw(26) << i.sender.Name() << setw(50) << "Utxo Value" << endl;
                out_r << endl;

            }

        }

        out_r << "OUTPUTS:" << endl;

        for (int i = 0; i < m_Output.size(); i++) {

            out_r << "#" << i << " " << right << setw(23) << m_Output[i].reciever.Name() << setw(50) << m_Output[i].amount << endl; 

        }
        
        out_r << "----------------------------------------------------------------------------" << endl;
    
    }

    
    string Id() const { return m_ID; }
    string TimestampInfo() const { return m_Timestamp; }
    vector<input> Input() const { return m_Input; }
    vector<output> Output() const { return m_Output; }
    
};