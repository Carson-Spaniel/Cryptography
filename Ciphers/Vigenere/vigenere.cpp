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
    string plaintext;

    for (int i = 0; i < ciphertext.size(); i++) {
        char x = ((ciphertext[i] - 32 - (key[i] - 32) + 95) % 95) + 32; // Adjust modulo and offset

        plaintext.push_back(x);
    }
    return plaintext;
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
    string binaryResult = "";
    for (char c : text) {
        // Convert each character to its ASCII value
        int asciiValue = static_cast<int>(c);
        // Convert ASCII value to binary, format with 8 bits
        string binaryValue = bitset<8>(asciiValue).to_string();
        // Append binary value to the result
        binaryResult += binaryValue;
    }
    return binaryResult;
}

int getKeyLength(string ciphertext) {
    int maxLen = 30;
    if (ciphertext.size() < maxLen){
        maxLen = ciphertext.size();
    }

    vector<int> lengths;
    for (int i = 1; i <= maxLen; i++) {
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

int scoreText(string data) {
    int s = 0;
    transform(data.begin(), data.end(), data.begin(), ::tolower);
    string common = "etaoin shrdlu";
    string alphabet = "abcdefghijklmnopqrstuvwxyz .";

    for (char c : data) {
        if (!isprint(c) || alphabet.find(tolower(c)) == string::npos) {
            return 0; // Return 0 if the character is not in the common string
        }

        size_t i = common.find(tolower(c));
        s += i;
    }

    return s;
}

void generateCombinations(string& currentKey, int index, int keyLength, string& ciphertext, string& plaintext, int& bestScore, string& bestKey) {
    // Base case: if index reaches the length of the key, decrypt the ciphertext and update the plaintext and best score
    if (index == keyLength) {

        // cout << currentKey << "\n";

        // Decrypt the ciphertext using the current key
        string decryptedText = originalText(ciphertext, generateKey(ciphertext, currentKey));

        // Score the decrypted text
        int score = scoreText(decryptedText);

        // Keep track of the best key based on the score
        if (score > bestScore) {
            bestScore = score;
            plaintext = decryptedText;
            bestKey = currentKey;
        }
        return;
    }

    // Loop through all possible characters from 'a' to 'Z' for the current index in the key
    for (char ch = 'A'; ch <= 'z'; ++ch) {
        // Set the current character in the key
        currentKey[index] = ch;

        // Recur for the next index
        generateCombinations(currentKey, index + 1, keyLength, ciphertext, plaintext, bestScore, bestKey);
    }
}

string breakVigenere(string ciphertext, int keyLength) {
    string plaintext;
    int bestScore = 0;
    string bestKey;

    // Initialize key with all 'a's
    string currentKey(keyLength, 'a');

    // Generate all combinations of letters for the key
    generateCombinations(currentKey, 0, keyLength, ciphertext, plaintext, bestScore, bestKey);

    cout << "Best key: " << bestKey << "\n";

    return plaintext;
}


int main() {
	string str = "Hello this is my full long message to encrypt using vigenere cipher";
	string keyword = "key";

	string key = generateKey(str, keyword);
	string ciphertext = cipherText(str, key);
    int keyLength = getKeyLength(ciphertext);

    cout << "Key: " << key << "\n";

	cout << "Ciphertext: " << ciphertext << "\n";

	cout << "Original Text: " << originalText(ciphertext, key) << "\n";

    cout << "Found Possible Key length: " << keyLength << "\n";

    string brokenText = breakVigenere(ciphertext, keyLength/7);

    cout << "Broken Text: " << brokenText << "\n";
	return 0;
}
