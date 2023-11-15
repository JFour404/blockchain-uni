#include "header.h"


int main (){
    
    string mainFunction = "help";
    bool enableInspection = false;
    bool blockchainCreated = false;

    blockchainApp app;
    infoNet info;
    int blockchainSize = 5;
    int difficultyTarget = 3;


    while (mainFunction != "exit"){

        if (mainFunction == "help") {

            cout << "== Commands ==" << endl;
            cout << setw(15) << left << "help" << "Pateikia visas galimas komandas su aprasais" << endl;
            cout << setw(15) << left << "runChain" << "Generuojama bloku grandine pagal default konfiguracija" << endl;
            cout << setw(15) << left << " -c" << "Custom konfiguracja" << endl;
            cout << setw(15) << left << "cleanChain" << "Isvaloma bloku grandine" << endl;
            cout << setw(15) << left << "printBlock" << "Atspausdina faile block-1.txt pasirinkta bloka" << endl;
            cout << setw(15) << left << "printTx" << "Atspausdina cmd pasirinkta transakcija " << endl;
            cout << setw(15) << left << "wallet" << "Atspausdina pasirinktos pinigines informacija" << endl;
            cout << setw(15) << left << " -l" << "Atspausdina visu piniginiu informacija faile wallets.txt" << endl;
            cout << setw(15) << left << " -r" << "Atspausdina atsitiktiniu piniginiu informacija cmd" << endl;
            cout << setw(15) << left << "tx" << "Sukuria nauja transakcija" << endl;
            cout << setw(15) << left << " -g" << "Sugeneruojama automatiskai" << endl;
            cout << setw(15) << left << "script" << "Vykdomas skriptas" << endl;
            cout << setw(15) << left << "exit" << "Nutraukia programos vykdyma" << endl << endl;

        }

        cout << ">";
        mainFunction = askCommand(0);
        cout << endl;

        if (mainFunction == "runChain" || mainFunction == "runChain -c") {

            if (mainFunction == "runChain -c") {

                cout << "Iveskite bloku skaiciu: ";
                blockchainSize = intInput();
                cout << "Iveskite sudetingumo lygi: ";
                difficultyTarget = intInput();
                
            }
            
            if (blockchainCreated == false) {

                cout << "Generuojamos pinigines..." << endl;
                app.InitializeUsers();
                cout << "Sugeneruota piniginiu: " << app.m_UserPool.size() << endl;

                cout << "Generuojamas genesis blokas..." << endl;
                app.CreateGenesisBlock();
                cout << "Done" << endl;

                cout << "Generuojamos transakcijos..." << endl;
                app.InitializeTransactions();
                cout << "Sugeneruota transakciju: " << app.m_PaymentPool.size() << endl;

            }
            
            cout << "Generuojami blokai..." << endl;
            cout << "Sudetingumas: " << difficultyTarget << endl;
            cout << "Bloku kiekis: " << blockchainSize << endl;
            app.CreateBlocks(blockchainSize, difficultyTarget);
            cout << "Bloku generavimas baigtas!" << endl;
            cout << "Visus blokus ir ju trasakcijas galite rasti <blocks> aplankale." << endl << endl;

            enableInspection = true;
            blockchainCreated = true;

        } 
        
        else if (mainFunction == "cleanChain") {
            
            cout << "Istrinama bloku grandine..." << endl;
            app.m_LiveNet.clear();
            app.m_LiveNet.shrink_to_fit();
            cout << "Done" << endl;
            
            cout << "Istrinamos pinigines..." << endl;
            app.m_UserPool.clear();
            app.m_UserPool.shrink_to_fit();
            cout << "Done" << endl;
            
            cout << "Istrinamos transakcijos..." << endl;
            app.m_PaymentPool.clear();
            app.m_PaymentPool.shrink_to_fit();
            cout << "Done" << endl << endl;

            enableInspection = false;
            blockchainCreated = false;

        }

        else if (mainFunction == "printBlock") {

            if (enableInspection == false) {

                cout << "Bloku grandine nerasta, noredami sukurti nauja grandine naudokite komanda runChain" << endl << endl;

            }

            else {
                
                cout << "Pasirinkite bloka nuo 0 iki " << app.m_LiveNet.size() - 1 << ": ";
                int chosenBlock = intInput();

                app.m_LiveNet[chosenBlock].Info("block-1.txt");
                cout << "Informacija apie bloka pateikta <block-1.txt> faile" << endl << endl;

            }

        }

        else if (mainFunction == "printTx") {

            if (enableInspection == false) {

                cout << "Bloku grandine nerasta, noredami sukurti nauja grandine naudokite komanda runChain" << endl << endl;

            }

            else {

                cout << "Pasirinkite bloka nuo 0 iki " << app.m_LiveNet.size() - 1 << ": ";
                int chosenBlock = intInput();

                cout << "Pasirinkite transajcija nuo 0 iki " << app.m_LiveNet[chosenBlock].Tx().size() - 1 << ":";
                int chosenTransaction = intInput();

                app.m_LiveNet[chosenBlock].Tx()[chosenTransaction].CmdInfo();

            }

        }

        else if (mainFunction == "wallet") {

            cout << "In development..." << endl << endl;

        }

        else if (mainFunction == "wallet -l") {

            cout << "In development..." << endl << endl;

        }

        else if (mainFunction == "wallet -r") {

            cout << "In development..." << endl << endl;

        }

        else if (mainFunction == "tx") {

            cout << "In development..." << endl << endl;

        }

        else if (mainFunction == "tx -g") {

            cout << "In development..." << endl << endl;

        }

        else if (mainFunction == "script") {

            cout << "Generuojamos pinigines..." << endl;
            app.InitializeUsers();

            cout << "Generuojamas genesis blokas..." << endl;
            app.CreateGenesisBlock();
            
            // cout << "Generuojamos transakcijos..." << endl;
            // app.InitializeTransactionsUtxo();

            

            
            // cout << "Generuojamos transakcijos..." << endl;
            // app.InitializeTransactions();

            // cout << "Atnaujinama piniginiu info..." << endl;
            // info.UpadateWallets(app.m_LiveNet, app.m_UserPool);

            // double mintedSuply = 0;
            // for (wallet w: app.m_UserPool) {
            //     mintedSuply += info.FindUsersBalance(app.m_LiveNet, w);
            // }

            
            // cout << "Pirmosios pinigines info: " << endl;
            // cout << "Name: " << app.m_UserPool[0].Name() << endl;
            // cout << "Balance: " << info.FindUsersBalance(app.m_LiveNet, app.m_UserPool[0]) << endl;
            // cout << "UTXOs: " << endl;
            // for (string s: app.m_UserPool[0].UTXO()) {

            //     cout << s << endl;

            // }
            // cout << "-----------" << endl;



            // cout << "Sukurta monetu: " << mintedSuply << endl;

            // cout << "Generuojami blokai..." << endl;
            // app.CreateBlocks(blockchainSize, difficultyTarget);
            // cout << "Bloku generavimas baigtas!" << endl;

            // double circulatingSuply = 0;
            // for (wallet w: app.m_UserPool) {
            //     circulatingSuply += info.FindUsersBalance(app.m_LiveNet, w);
            // }

            // cout << "Apyvartoje esancios monetos: " << circulatingSuply << endl;





        }

    }

    return 0;
}