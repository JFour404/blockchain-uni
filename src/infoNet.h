#include "header.h"
#pragma once

class infoNet {

public:

    void UpadateWallets(vector<block> blockchain, vector<wallet>& userPool) {

        block latestBlock = blockchain.back();

        for (transactionUtxo tx: latestBlock.Tx()){

            string sendersPkey = tx.Transfer().from.PublicKey();
            string recieversPkey = tx.Transfer().to.PublicKey();

            for (wallet& w : userPool) {
                
                if (w.PublicKey() == sendersPkey) {

                    double sendersBalance = FindUsersBalance(blockchain, w);

                    //graza
                    if (sendersBalance > tx.Transfer().funds){
                        
                        wallet::utxo temp;
                        temp.txId = tx.Id();
                        w.UtxoAdd(temp);

                    }    


                    double foundFunds = 0;
                    bool goalReached = false;
                    
                    for (block b: blockchain) {

                        if ( goalReached ) break;

                        for (transactionUtxo tX: b.Tx()) {

                            for (int i = 0; i < w.UTXO().size(); i++) {

                                if (tX.Id() == w.UTXO()[i].txId) {

                                    if (w.PublicKey() == tX.Transfer().from.PublicKey()) { 
                                        
                                        foundFunds += tX.Transfer().funds;
                                        wallet::utxo temp;
                                        temp.txId = tx.Id();
                                        w.UtxoDelete(temp);
                                        
                                        break;
                                    }

                                    // if (w.PublicKey() == tX.SenderPkey()) {

                                        

                                    //     break;
                                    // }

                                }

                            }

                            if (foundFunds >= tx.Transfer().funds) { goalReached = true; }
                            if ( goalReached ) break;


                        }


                    }

                    

                    





                }

                if (w.PublicKey() == recieversPkey) {

                    wallet::utxo temp;
                    temp.txId = tx.Id();
                    w.UtxoAdd(temp);

                }
            
            }

        }

    }
    
    void UpdateWalletsUtxo(vector<block> blockchain, vector<wallet>& userPool) {

        block latestBlock = blockchain.back();

        //pridedam utxo
        for (transactionUtxo tx: latestBlock.Tx()) {

            for (int i = 0; i < tx.Output().size(); i++) {
                
                transactionUtxo::output out = tx.Output()[i];

                for (wallet& w: userPool) {

                    if (w == out.reciever) {

                        wallet::utxo tempUtxo;
                        tempUtxo.outputNum = i;
                        tempUtxo.txId = tx.Id();
                        tempUtxo.value = out.amount;

                        w.UtxoAdd(tempUtxo);

                    }

                }

            }

            for (int i = 0; i < tx.Input().size(); i++) {

                transactionUtxo::input in = tx.Input()[i];

                for (wallet& w: userPool) {

                    if (w == in.sender) {

                        w.UtxoDelete(in.usedUtxo);

                    }

                }

            }

        }

    }

    double FindUsersBalance(vector<block> blockchain, wallet user) {
    
        double balance = 0;

        for (block b: blockchain) {
            
            for (transactionUtxo tx: b.Tx()) {
                
                if (tx.Transfer().from.PublicKey() == user.PublicKey()) {
                    
                    balance -= tx.Transfer().funds;

                }
                
                if (tx.Transfer().to.PublicKey() == user.PublicKey()) {
                    
                    balance += tx.Transfer().funds;

                }
            
            }
        
        }

        return balance;
    }

    void ReplaceUsedTx(vector<int> usedTx, vector<transactionUtxo>& paymentPool, vector<wallet> userPool) {

        for (int i: usedTx) {

            transactionUtxo newTx(userPool);
            paymentPool[i] = newTx;

        }

    }

    void WalletInfo(wallet user, int index, vector<block> blockchain) {

        cout << "----==Wallet #" << index << "==----" << endl;
        cout << "Name: " << user.Name() << endl;
        cout << "PublicKey: " << user.PublicKey() << endl;
        cout << "Balance: " << FindUsersBalance(blockchain, user) << endl;
        cout << "Utxo: " << endl;
        
        for (wallet::utxo u: user.UTXO()) {

            cout << u.txId << " : " << u.outputNum << " " << u.value << endl;

        }

        cout << endl;

    }

};