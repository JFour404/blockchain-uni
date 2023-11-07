#include "header.h"


int main (){
    
    string mainFunction = "";
    bool enableInspection = "false";

    blockchainApp app;
    int blockchainSize = 5;
    int difficultyTarget = 3;

    cout << "Pasirinkite programos funkcija: " << endl;
    cout << "/0 Paleisti bloku grandine." << endl;
    cout << "/1 Atspausdinti informacija (cmd)." << endl;
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

            cout << "Generuojamos transakcijos..." << endl;
            app.InitializeTransactions();

            cout << "Generuojamas genesis blokas..." << endl;
            app.CreateGenesisBlock();

            cout << "Generuojami blokai..." << endl;
            app.CreateBlocks(blockchainSize, difficultyTarget);
            cout << "Bloku generavimas baigtas!" << endl;
            cout << "Visus blokus ir ju trasakcijas galite rasti <blocks> aplankale." << endl;

            enableInspection = "true";

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

    }

    return 0;
}