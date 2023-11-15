#include "header.h"
#pragma once

class infoNet {

public:

    void UpadateWallets(vector<block> blockchain, vector<wallet>& userPool) {

        block latestBlock = blockchain.back();

        for (transaction tx: latestBlock.Tx()){

            string sendersPkey = tx.SenderPkey();
            string recieversPkey = tx.RecieverPkey();

            for (wallet& w : userPool) {
                
                if (w.PublicKey() == sendersPkey) {

                    double sendersBalance = FindUsersBalance(blockchain, w);

                    if (sendersBalance > tx.Amount()){
                        
                        wallet::utxo temp;
                        temp.txId = tx.Id();
                        w.UtxoAdd(temp);

                    }    


                    double foundFunds = 0;
                    bool goalReached = false;
                    
                    for (block b: blockchain) {

                        if ( goalReached ) break;

                        for (transaction tX: b.Tx()) {

                            for (int i = 0; i < w.UTXO().size(); i++) {

                                if (tX.Id() == w.UTXO()[i].txId) {

                                    if (w.PublicKey() == tX.RecieverPkey()) { 
                                        
                                        foundFunds += tX.Amount();
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

                            if (foundFunds >= tx.Amount()) { goalReached = true; }
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
    
    double FindUsersBalance(vector<block> blockchain, wallet user) {
    
        double balance = 0;

        for (block b: blockchain) {
            
            for (transaction tx: b.Tx()) {
                
                if (tx.SenderPkey() == user.PublicKey()) {
                    
                    balance -= tx.Amount();

                }
                
                if (tx.RecieverPkey() == user.PublicKey()) {
                    
                    balance += tx.Amount();

                }
            
            }
        
        }

        return balance;
    }



};