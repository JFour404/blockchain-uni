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
        if (!(cin >> input)||(input!="/0"&&input!="/1"&&input!="/2"&&input!="/e")){
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

void updateWallets (vector<block> blockchain, vector<wallet>& userPool) {

    

}

