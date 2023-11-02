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

string getTimestamp() {

    auto now = std::chrono::system_clock::now();
    time_t timestamp = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&timestamp);

}