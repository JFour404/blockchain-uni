#include "header.h"


int main (){
    vector<string> names;
    getNames(names);

    vector<wallet> user;

    for (int i = 0; i < 10; i++){

        user.push_back(wallet(names, i));

    }
    
    for (wallet d: user) {
        cout << d.Name() << " " << d.PublicKey() << endl;
    }
    
    return 0;
}