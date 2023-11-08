#include "header.h"


int main (){
    
    string mainFunction = "";
    bool enableInspection = false;

    blockchainApp app;
    infoNet info;
    int blockchainSize = 5;
    int difficultyTarget = 3;

    cout << "Pasirinkite programos funkcija: " << endl;
    cout << "/0 Paleisti bloku grandine." << endl;
    cout << "/1 Atspausdinti informacija (cmd)." << endl;
    cout << "/2 Sandbox" << endl;
    cout << "/e exit" << endl;

    while ((mainFunction = askCommand(0)) != "/e"){

        if (mainFunction == "/0") {

            cout << "Ar norite naudoti numatytaji bloku skaiciu ir sudetinguma? (y/n) :  ";
            
            if (askCommand(1) == "n") {

                cout << "Iveskite bloku skaiciu: ";
                cin >> blockchainSize;
                cout << "Iveskite sudetingumo lygi: ";
                cin >> difficultyTarget;
                
            }
            
            cout << "Generuojamos pinigines..." << endl;
            app.InitializeUsers();

            cout << "Generuojamas genesis blokas..." << endl;
            app.CreateGenesisBlock();

            cout << "Generuojamos transakcijos..." << endl;
            app.InitializeTransactions();

            cout << "Generuojami blokai..." << endl;
            app.CreateBlocks(blockchainSize, difficultyTarget);
            cout << "Bloku generavimas baigtas!" << endl;
            cout << "Visus blokus ir ju trasakcijas galite rasti <blocks> aplankale." << endl;

            


            enableInspection = true;

        } 
        
        else if (mainFunction == "/1" && enableInspection == 1) {

            cout << "Spausdinti bloko (/b) ar transakcijos (/t) informacija? :  ";
            string printInfo = askCommand(2);

            int chosenBlock;
            int chosenTransaction;
            
            cout << "Pasirinkite bloka nuo 0 iki " << app.m_LiveNet.size() - 1 << ":";
            cin >> chosenBlock;

            if (printInfo == "/b") {

                app.m_LiveNet[chosenBlock].Info(-1);
                cout << "Informacija apie bloka pateikta <block-1.txt> faile" << endl;

            }
            
            if (printInfo == "/t") {

                cout << "Pasirinkite transajcija nuo 0 iki " << app.m_LiveNet[chosenBlock].Tx().size() - 1 << ":";
                cin >> chosenTransaction;

                app.m_LiveNet[chosenBlock].Tx()[chosenTransaction].CmdInfo();

            }

        }

        else if (mainFunction == "/2") {

            cout << "Generuojamos pinigines..." << endl;
            app.InitializeUsers();

            cout << "Generuojamos transakcijos..." << endl;
            app.InitializeTransactions();

            cout << "Generuojamas genesis blokas..." << endl;
            app.CreateGenesisBlock();

            cout << "Atnaujinama piniginiu info..." << endl;
            info.UpadateWallets(app.m_LiveNet, app.m_UserPool);

            double mintedSuply = 0;
            for (wallet w: app.m_UserPool) {
                mintedSuply += info.FindUsersBalance(app.m_LiveNet, w);
            }

            
            // cout << "Pirmosios pinigines info: " << endl;
            // cout << "Name: " << app.m_UserPool[0].Name() << endl;
            // cout << "Balance: " << info.FindUsersBalance(app.m_LiveNet, app.m_UserPool[0]) << endl;
            // cout << "UTXOs: " << endl;
            // for (string s: app.m_UserPool[0].UTXO()) {

            //     cout << s << endl;

            // }
            // cout << "-----------" << endl;



            cout << "Sukurta monetu: " << mintedSuply << endl;

            cout << "Generuojami blokai..." << endl;
            app.CreateBlocks(blockchainSize, difficultyTarget);
            cout << "Bloku generavimas baigtas!" << endl;

            double circulatingSuply = 0;
            for (wallet w: app.m_UserPool) {
                circulatingSuply += info.FindUsersBalance(app.m_LiveNet, w);
            }

            cout << "Apyvartoje esancios monetos: " << circulatingSuply << endl;





        }

    }

    return 0;
}