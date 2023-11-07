#include "header.h"

void getNames (vector<string>& names){

    string eilute;
    stringstream buferis;

    ifstream fd("../data/names.txt");
    buferis << fd.rdbuf();

    while (buferis) {
        
        if (!buferis.eof()){

            getline (buferis, eilute);
            names.push_back(eilute);

        } else break;

    }
    buferis.clear();

}

string askCommand (int select) {
    
    string input;
    if (select==0){
        while(1){
        if (!(cin >> input)||(input!="/0"&&input!="/1"&&input!="/e")){
            cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }
    if (select==1){
        while(1){
        if (!(cin >> input)||(input!="y"&&input!="n")){
            cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }
    if (select==2){
        while(1){
        if (!(cin >> input)||(input!="/b"&&input!="/t")){
            cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }


    if (select==3){
        while(1){
        if (!(cin >> input)||(input!="/0"&&input!="/1"&&input!="/2"&&input!="/3"&&input!="/4"&&input!="/5"&&input!="/e")){
            cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }
    return input;
}

string getTimestamp() {

    auto now = std::chrono::system_clock::now();
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&timestamp);

}



vector<blockchainApp::reciept> findReciept(wallet user, vector<block> m_LiveNet) {

    vector<blockchainApp::reciept> spreadsheet;
    
    
    for (block b: m_LiveNet) {

        for (transaction tx: b.Tx()) {

            for (auto it = spreadsheet.begin(); it != spreadsheet.end(); ) {
                
                if (it->utxoID == tx.Id()) { it = spreadsheet.erase(it);} 
                else { ++it; }

            }
            
            for (transaction::transfer t: tx.Transfer()) {

                for (int i = 0; i < t.to.size(); i++) {

                    if (t.to[i] == user) {  

                        blockchainApp::reciept temp;
                        temp.utxoID = tx.Id();
                        temp.amount = t.amount[i];

                        spreadsheet.push_back(temp);

                    }

                }

            }

        }

    }

    return spreadsheet;

}

double findBalance (wallet user, vector<block> m_LiveNet) {


    vector<blockchainApp::reciept> temp = findReciept(user, m_LiveNet);

    double total = 0;

    for (blockchainApp::reciept r: temp) {

        total += r.amount;

    }

    return total;

}

void usableUtxoFinder(wallet sender, double coinsNeeded, double& foundCoins, vector<string>& usedUtxo, vector<block> m_LiveNet) {

    bool valid = false;
    bool stopLoops = false;
    foundCoins = 0;
    
    vector<string> utxo;
    utxo = sender.UTXO();

    for (block b: m_LiveNet) {
        if (stopLoops) break;

        for (transaction tx: b.Tx()) {
            if (stopLoops) break;

            auto it = std::find(utxo.begin(), utxo.end(), tx.Id());
            if (it != utxo.end()) {

                for (transaction::transfer t: tx.Transfer()) {
                    if (stopLoops) break;

                    for (int i = 0; i < t.to.size(); i++) {

                        if (t.to[i] == sender) {

                            foundCoins += t.amount[i];
                            usedUtxo.push_back(tx.Id());

                            if (foundCoins > coinsNeeded) {
                                stopLoops = true;
                                break;
                            } 

                        }

                    }

                }

            }

        }

    }

}
