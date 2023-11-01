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

