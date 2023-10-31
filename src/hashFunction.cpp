#include "header.h"

string hexHashGen(string text){
    vector<int> hash = hashGen(text);
    string hexHash = binaryToHex(hash);
    
    return hexHash;
}

vector<int> hashGen(string text){
    int i = 0, seedSum = 0;
    vector <int> hash = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0};
    
    for (char symbol: text){
            wint_t seed = seedGen (symbol);
            seedSum += seed;
        }

    size_t textSize = text.size(); 
    vector<int> lag = sequenceGen (textSize, seedSum);
    vector<int> newHash;

    for (char symbol: text) {
        wint_t seed = seedGen (symbol);
        int seq = lag[i];
        newHash = bitsGen(seed);
        shiftRight (newHash, seq);
        hash = hashTornado (hash, newHash);
        i++;
    }

    return hash;
}

vector<int> sequenceGen (unsigned int textSize, int seedSum){
    mt19937 generator(textSize + seedSum);
    uniform_int_distribution<int> distribution(0, 255);

    vector<int> randomSeq;

    for (int i = 0; i < textSize; ++i) {
        int seq = distribution(generator); 
        randomSeq.push_back(seq);
    }

    return randomSeq;
}

wint_t seedGen (char symbol){
    wint_t seed = static_cast<wint_t>(symbol);
    return seed;
}

vector <int> bitsGen (unsigned int seed){
    mt19937 generator((seed));
    bernoulli_distribution distribution(0.5);

    vector<int> randomBits;

    for (int i = 0; i < 256; ++i) {
        int bit = distribution(generator); 
        randomBits.push_back(bit);
    }

    return randomBits;
}

void shiftRight (vector<int>& hash, int seq){
    if (hash.empty() || seq <= 0) {
        return;
    }

    int size = hash.size();
    seq %= size;

    vector<int> temp(size);

    for (int i = 0; i < size; ++i) {
        int newIdex = (i+seq) % size;
        temp[newIdex] = hash[i];
    }

    hash = temp;
}

vector <int> hashTornado (vector<int> prevHash, vector<int> newHash){
    vector<int> hash;
    int size = prevHash.size();

    for (int i = 0; i < size; ++i){
        if (prevHash[i] == 0 && newHash[i] == 0) 
            hash.push_back(0);
        else
        if (prevHash[i] == 0 && newHash[i] == 1) 
            hash.push_back(1);
        else
        if (prevHash[i] == 1 && newHash[i] == 0) 
            hash.push_back(1);
        else
        if (prevHash[i] == 1 && newHash[i] == 1) 
            hash.push_back(0);
    }

    return hash;
}

string binaryToHex(vector <int> hashBi) {
    int i = 0;
    string temp1;
    string temp4 = "";
    int tempInt;
    string tempHex;

    for (int d : hashBi) {
        if (i==3) {
            temp1 = to_string(d);
            temp4 += temp1;
            
            tempInt = stoi(temp4);

                switch (tempInt) {
                    case 0:
                        tempHex += "0";
                        break;
                    case 1:
                        tempHex += "1";
                        break;
                    case 10:
                        tempHex += "2";
                        break;
                    case 11:
                        tempHex += "3";
                        break;
                    case 100:
                        tempHex += "4";
                        break;
                    case 101:
                        tempHex += "5";
                        break;
                    case 110:
                        tempHex += "6";
                        break;
                    case 111:
                        tempHex += "7";
                        break;
                    case 1000:
                        tempHex += "8";
                        break;
                    case 1001:
                        tempHex += "9";
                        break;
                    case 1010:
                        tempHex += "a";
                        break;
                    case 1011:
                        tempHex += "b";
                        break;
                    case 1100:
                        tempHex += "c";
                        break;
                    case 1101:
                        tempHex += "d";
                        break;
                    case 1110:
                        tempHex += "e";
                        break;
                    case 1111:
                        tempHex += "f";
                        break;
                    default:
                        tempHex += "0";
                
                }

            temp4 = "";
            i = 0;
        } else {
            temp1 = to_string(d);
            temp4 += temp1;
            i++;
        } 
    } 

    return tempHex;
}