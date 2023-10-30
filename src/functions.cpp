#include "header.h"

void setNames (vector<participant>& user) {

    string eilute;
    stringstream buferis;
    vector <string> names;

    ifstream fd("../data/names.txt");
    buferis << fd.rdbuf();

    while (buferis) {
        
        if (!buferis.eof()){

            getline (buferis, eilute);
            names.push_back(eilute);

        } else break;

    }
    buferis.clear();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for (int i=0; i < user.size(); i++) {

        int randomName = dis(gen);
        string name = names[randomName];

        int randomNumber = dis(gen);
        std::ostringstream ss;
        ss << setw(4) << std::setfill('0') << randomNumber;
        string filledNumber = ss.str();
        
        user[i].Name(name + "#" + filledNumber);
    }
}