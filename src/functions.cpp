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
        set<string> commands = {"help", "genesis", "runChain", "runChain -c", "cleanChain", 
        "printBlock", "printTx", "wallet", "wallet -l", "wallet -r", "tx", "tx -g", "script", "exit"};
        while(1){
            if (!getline(cin, input)) {
                if (!input.empty())
                    cout << "Neteisinga ivestis. Prasome ivesti is naujo" << endl << endl;
                cout << ">";
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else if (commands.find(input) == commands.end()) {
                if (!input.empty())
                    cout << "Neteisinga ivestis. Prasome ivesti is naujo" << endl << endl;
                cout << ">";
            } else {
                break;
            }
        } 
    }

    if (select==1){
        while(1){
        if (!(cin >> input)||(input!="y"&&input!="n")){
            if (!input.empty())
                cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }

    if (select==2){
        while(1){
        if (!(cin >> input)||(input!="/b"&&input!="/t")){
            if (!input.empty())
                cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }

    if (select==3){
        while(1){
        if (!(cin >> input)||(input!="/0"&&input!="/1"&&input!="/2"&&input!="/3"&&input!="/4"&&input!="/5"&&input!="/e")){
            if (!input.empty())
                cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            } else break;
        } 
    }
    
    return input;
}

int intInput () {
    string input;
    while (1) {
        if (!(cin >> input) || count_if(input.begin(), input.end(), [](char c){ return !isdigit(c); }) > 0 || input.find_first_of(",.") != string::npos) {
            if (!input.empty())
                cout << "Neteisinga ivestis. Prasome ivesti is naujo" << std::endl;
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return stoi(input);
}

string getTimestamp() {

    auto now = std::chrono::system_clock::now();
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&timestamp);

}

void updateWallets (vector<block> blockchain, vector<wallet>& userPool) {

    

}

