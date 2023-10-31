#include "header.h"


int main (){
    vector<string> names;
    getNames(names);

    vector<participant> user;

    for (int i = 0; i < 10; i++){

        user.push_back(participant(names, i));

    }
    
    for (participant d: user) {
        cout << d.Name() << " " << d.PublicKey() << endl;
    }
    
    return 0;
}