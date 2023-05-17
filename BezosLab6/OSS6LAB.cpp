#include <iostream>
#include "Des.h"
#include <bitset>
#include <fstream>

string to64bit(string s) {
	string binaryResult = "";
	for (std::size_t i = 0; i < s.size(); ++i)
	{
		binaryResult += (bitset<8>(s.c_str()[i])).to_string();
	}
	if (binaryResult.length() % 64 == 0) return binaryResult;

	int n = 64 - (binaryResult.length() % 64);

	for (int i = 0; i < n; i++) {
		binaryResult += "0";
	}

	return binaryResult;
}

string from64bit(string s) {
	string result = "";
	int pos = 0;
	while (pos < s.size())
	{
		string word = s.substr(pos, 8);
		pos += 8;

		bitset<8> bits(word);
		int n = bits.to_ulong();
		result += char(n);
	}
	return result;
}

string encrypt()
{
	string textToEncrypt;
	string keyToEncrypt;
	cout << "Enter key: ";
	getline(cin, keyToEncrypt);
	keyToEncrypt = to64bit(keyToEncrypt);

	//cout << "Enter plain text: ";
	//cin >> textToEncrypt;


	//_flushall();
	getline(cin, textToEncrypt);
	textToEncrypt = to64bit(textToEncrypt);

	cout << "Text: " << from64bit(textToEncrypt) << endl;

	generate_keys(keyToEncrypt);
	int n = div(textToEncrypt.length(), 64).quot;
	string ct;
	//cout << textToEncrypt.length() << endl;
	//cout << n << endl;
	//cout << textToEncrypt << endl;
	for (int i = 0; i < n; i++) {
		ct += DES(textToEncrypt.substr(i * 64, 64), keyToEncrypt, round_keys);
	}

	string encrypt_text = from64bit(ct);
	FILE* out;
	fopen_s(&out, "enc.dat", "wb");

	//std::ofstream out("enc.txt");
	if (out != NULL)
	{
		fprintf(out, encrypt_text.c_str());
		fclose(out);
	}
	std::cout << "Ecnrypt:" << encrypt_text << std::endl;

	return encrypt_text;
}

void decrypt(string textToDecrypt)
{
	string keyToDecrypt;
	cout << "Enter key to decrypt: ";
	//cin >> keyToDecrypt;
	getline(cin, keyToDecrypt);
	keyToDecrypt = to64bit(keyToDecrypt);
	string txt;
	std::cout << "Decrypt Text ";

	//textToDecrypt = "";
	//getline(cin, textToDecrypt);


	textToDecrypt = to64bit(textToDecrypt);

	generate_keys(keyToDecrypt);
	int i = 15;
	int j = 0;
	while (i > j)
	{
		string temp = round_keys[i];
		round_keys[i] = round_keys[j];
		round_keys[j] = temp;
		i--;
		j++;
	}
	int n = div(textToDecrypt.length(), 64).quot;
	string decrypted;
	//cout << textToDecrypt.length() << endl;
	//cout << n << endl;
	for (int i = 0; i < n; i++) {
		decrypted += DES(textToDecrypt.substr(i * 64, 64), keyToDecrypt, round_keys);
	}
	cout << "Decrypted text:" << from64bit(decrypted) << endl;
}


int main() {
	auto txt = encrypt();

	string line;
	string line2;
	ifstream in("enc.dat");

	while (!in.eof())
	{
		getline(in, line);
		line2 += line;
	}
	in.close();

	std::cout << "ENCRYPT FROM FILE__" << line2 << std::endl;

	decrypt(line);
	return 0;
}