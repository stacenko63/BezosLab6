#pragma once
#include <string>
using namespace std;

extern string round_keys[16];

string shift_left_once(string key_chunk);

string shift_left_twice(string key_chunk);

void generate_keys(string key); //16 раундов

string convertDecimalToBinary(int decimal);

int convertBinaryToDecimal(string binary);

string Xor(string a, string b);

string DES(string pt, string key, string round_keys[16]);