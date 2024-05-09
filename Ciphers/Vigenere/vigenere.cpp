// C++ code to implement Vigenere Cipher
#include<bits/stdc++.h>
using namespace std;

// This function generates the key in a cyclic manner until it's length is equal to the length of original text
string generateKey(string str, string key) {
    string generatedKey;
    int keyIndex = 0;
    for (char c : str) {
        if (keyIndex == key.size()) {
            keyIndex = 0; // Reset keyIndex to reuse the key
        }
        generatedKey.push_back(key[keyIndex++]);
    }
    return generatedKey;
}

// This function returns the encrypted text generated with the help of the key
string cipherText(string str, string key) {
    string ciphertext;

    for (int i = 0; i < str.size(); i++) {
        char x = ((str[i] - 32 + key[i] - 32) % 95) + 32; // Adjust modulo and offset

        ciphertext.push_back(x);
    }
    return ciphertext;
}

// This function decrypts the encrypted text and returns the original text
string originalText(string ciphertext, string key) {
    string orig_text;

    for (int i = 0; i < ciphertext.size(); i++) {
        char x = ((ciphertext[i] - 32 - (key[i] - 32) + 95) % 95) + 32; // Adjust modulo and offset

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
    for (int i = 1; i <= 10; i++) { // Try key lengths up to a certain limit, e.g., 10
        lengths.push_back(i);
    }

    int keyLenCandidate;
    double minNormalized = 1e6;
    for (int keyLength : lengths) {
        double totalNormalizedDistance = 0;

        int numBlocks = ciphertext.length() / keyLength;
        for (int i = 0; i < numBlocks - 1; i++) {
            string block1 = ciphertext.substr(i * keyLength, keyLength);
            string block2 = ciphertext.substr((i + 1) * keyLength, keyLength);

            // Calculate Hamming distance between block1 and block2
            int hammingDistance = calculateHammingDistance(block1, block2);

            // Normalize Hamming distance
            double normalizedDistance = static_cast<double>(hammingDistance) / keyLength;

            // Accumulate normalized distances
            totalNormalizedDistance += normalizedDistance;
        }

        // Calculate average normalized distance
        double averageNormalizedDistance = totalNormalizedDistance / (numBlocks - 1);

        // Update candidate key length if average distance is smaller
        if (averageNormalizedDistance < minNormalized) {
            keyLenCandidate = keyLength;
            minNormalized = averageNormalizedDistance;
        }
    }

    return keyLenCandidate;
}

string breakVigenere(string ciphertext, string key) {
    string orig_text;

    for (int i = 0; i < ciphertext.size(); i++) {
        char x = ((ciphertext[i] - 32 - (key[i] - 32) + 95) % 95) + 32; // Adjust modulo and offset

        orig_text.push_back(x);
    }
    return orig_text;
}

int main()
{
	string str = "This is my message";
	string keyword = "This is my key that is long";

	string key = generateKey(str, keyword);
	string ciphertext = cipherText(str, key);

    cout << "Key: " << key << "\n";

	cout << "Ciphertext: " << ciphertext << "\n";

	cout << "Original/Decrypted Text: " << originalText(ciphertext, key) << "\n";

    cout << "Found Possible Key length: " << getKeyLength(ciphertext) << "\n";

    cout << "Decrypted Broken Text: " << breakVigenere(ciphertext, "A");
	return 0;
}
