#include "header.h"


int main (){
    vector<participant> user(10);
    
    setNames(user);

    for (participant d: user) {
        cout << d.Name() << endl;
    }
    
    return 0;
}