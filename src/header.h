#pragma once
#include <iomanip>
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <fstream>
#include <limits>
#include <chrono>
#include <list>
#include <deque>
#include <filesystem>
#include <bitset>
#include <locale>
#include <codecvt>
#include <unordered_map>
#include <cstdlib>

using std::string;
using std::cout;
using std::cin;
using std::stoi;
using std::left;
using std::right;
using std::fixed;
using std::setw;
using std::setprecision;
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
using std::bernoulli_distribution;
using std::vector;
using std::isspace;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::ofstream;
using std::sort;
using std::runtime_error;
using std::exception;
using std::cerr;
using std::to_string;
using std::count_if;
using std::isdigit;
using std::list;
using std::advance;
using std::deque;
using std::remove_if;
using std::istream;
using std::getline;
using std::bitset;

void getNames (vector<string>& names);

string hexHashGen(string text);
vector<int> hashGen(string text);
vector<int> sequenceGen (unsigned int textSize, int seedSum);
wint_t seedGen (char symbol);
vector <int> bitsGen (unsigned int seed);
void shiftRight (vector<int>& hash, int seq);
vector <int> hashTornado (vector<int> prevHash, vector<int> newHash);
string binaryToHex(vector <int> hashBi);

#include "wallet.h"
#include "transaction.h"
#include "block.h"