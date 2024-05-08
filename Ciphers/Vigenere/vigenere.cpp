// C++ code to implement Vigenere Cipher
#include<bits/stdc++.h>
using namespace std;

// This function generates the key in
// a cyclic manner until it's length isn't
// equal to the length of original text
string generateKey(string str, string key)
{
	int x = str.size();

	for (int i = 0; ; i++)
	{
		if (x == i)
			i = 0;
		if (key.size() == str.size())
			break;
		key.push_back(key[i]);
	}
	return key;
}

// This function returns the encrypted text
// generated with the help of the key
string cipherText(string str, string key)
{
	string ciphertext;

	for (int i = 0; i < str.size(); i++)
	{
		// converting in range 0-25
		char x = (str[i] + key[i]) %26;

		// convert into alphabets(ASCII)
		x += 'A';

		ciphertext.push_back(x);
	}
	return ciphertext;
}

// This function decrypts the encrypted text
// and returns the original text
string originalText(string ciphertext, string key)
{
	string orig_text;

	for (int i = 0 ; i < ciphertext.size(); i++)
	{
		// converting in range 0-25
		char x = (ciphertext[i] - key[i] + 26) %26;

		// convert into alphabets(ASCII)
		x += 'A';
		orig_text.push_back(x);
	}
	return orig_text;
}


/* Functions to break Vigenere */

int calculateHammingDistance(const string& block1, const string& block2) {
    int total = 0;
    // Assuming block1 and block2 are of equal length
    for (size_t j = 0; j < block1.length(); j++) {
        if (block1[j] != block2[j]) {
            total++;
        }
    }
    return total;
}

string ascii_to_binary(const string& text) {
    string binary_result = "";
    for (char c : text) {
        // Convert each character to its ASCII value
        int ascii_value = static_cast<int>(c);
        // Convert ASCII value to binary, format with 8 bits
        string binary_value = bitset<8>(ascii_value).to_string();
        // Append binary value to the result
        binary_result += binary_value;
    }
    return binary_result;
}

int getKeyLength(string ciphertext) {
    vector<int> lengths;
    for (int i = 1; i < 41; i++) {
        lengths.push_back(i);
    }

    int keyLenCandidate;
    double minNormalized = 1e6;
    for (int keyLength : lengths) {
        double totalHammingDistance = 0;
        double totalNormalizedDistance = 0;

        int numBlocks = ciphertext.length() / keyLength;
        for (int i = 0; i < numBlocks - 1; i++) {
            string block1 = ciphertext.substr(i * keyLength, keyLength);
            string block2 = ciphertext.substr((i + 1) * keyLength, keyLength);

            string blockBinary = ascii_to_binary(block1);
            string blockBinary2 = ascii_to_binary(block2);

            int hammingDistance = calculateHammingDistance(blockBinary, blockBinary2);
            double normalizedDistance = static_cast<double>(hammingDistance) / keyLength;

            totalHammingDistance += hammingDistance;
            totalNormalizedDistance += normalizedDistance;
        }

        double averageHammingDistance = totalHammingDistance / (numBlocks - 1);
        double averageNormalizedDistance = totalNormalizedDistance / (numBlocks - 1);

        if (averageNormalizedDistance < minNormalized){
            keyLenCandidate = keyLength;
            minNormalized = averageNormalizedDistance;
        }
    }

    return keyLenCandidate;
}

string breakVigenere(string ciphertext, string key)
{
	string orig_text;

	for (int i = 0; i < ciphertext.size(); i++)
	{
		// converting in range 0-25
		char x = (ciphertext[i] + key[i]) %26;

		// convert into alphabets(ASCII)
		x += 'A';

		orig_text.push_back(x);
	}
	return orig_text;
}

// Driver program to test the above function
int main()
{
	string str = "GEEKSFORGEEKS";
	string keyword = "KEY"; // The key cannot be longer than the text and has to be uppercase

	string key = generateKey(str, keyword);
	string ciphertext = cipherText(str, key);

	cout << "Ciphertext: " << ciphertext << "\n";

	cout << "Original/Decrypted Text: " << originalText(ciphertext, key) << "\n";

    cout << "Found Possible Key length: " << getKeyLength(ciphertext) << "\n";

    cout << "Decrypted Broken Text: " << breakVigenere(ciphertext, "A");
	return 0;
}
