#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <iomanip>

std::unordered_map<char, double> frequencyTable = {
    {'e', 12.70}, {'t', 9.06}, {'a', 8.17}, {'o', 7.51}, {'i', 6.97},
    {'n', 6.75}, {'s', 6.33}, {'h', 6.09}, {'r', 5.99}, {'d', 4.25},
    {'l', 4.03}, {'c', 2.78}, {'u', 2.76}, {'m', 2.41}, {'w', 2.36},
    {'f', 2.23}, {'g', 2.02}, {'y', 1.97}, {'p', 1.93}, {'b', 1.29},
    {'v', 0.98}, {'k', 0.77}, {'j', 0.15}, {'x', 0.15}, {'q', 0.10},
    {'z', 0.07}
};

double scoreText(const std::string& text) {
    double score = 0;
    for (char ch : text) {
        if (!isalpha(ch) && !isspace(ch)) {
            return 1e6;
        }
        else{
            score++;
        }
    }

    return score;
}

std::string XorAscii(std::string str, unsigned char ans) {
    std::string message;

    // Loop through the string two characters at a time
    for (size_t i = 0; i < str.length(); i += 2) {
        // Extract two characters from the string
        std::string hexByte = str.substr(i, 2);

        // Convert hexByte to integer
        std::stringstream ss;
        ss << std::hex << hexByte;
        int intValue;
        ss >> intValue;

        // XOR the integer value with 'ans'
        char xorResult = ans ^ static_cast<unsigned char>(intValue);

        // Append the XOR result to the message
        message += xorResult;
    }

    return message;
}

std::vector<int> getKeyLength() {
    std::vector<int> lengths;
    for (int i = 2; i < 41; i++) {
        lengths.push_back(i);
    }
    return lengths;
}

std::string ascii_to_binary(const std::string& text) {
    std::string binary_result = "";
    for (char c : text) {
        // Convert each character to its ASCII value
        int ascii_value = static_cast<int>(c);
        // Convert ASCII value to binary, format with 8 bits
        std::string binary_value = std::bitset<8>(ascii_value).to_string();
        // Append binary value to the result
        binary_result += binary_value;
    }
    return binary_result;
}

int calculateHammingDistance(const std::string& block1, const std::string& block2) {
    int total = 0;
    // Assuming block1 and block2 are of equal length
    for (size_t j = 0; j < block1.length(); j++) {
        if (block1[j] != block2[j]) {
            total++;
        }
    }
    return total;
}

std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

// Function to convert binary to hex
std::string bin2hex(const std::string &bin) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (unsigned char c : bin) {
        oss << std::setw(2) << (int)c;
    }
    return oss.str();
}

// Function to convert Base64 to hex
std::string base64_to_hex(const std::string &base64_str) {
    std::string decoded = base64_decode(base64_str);
    return bin2hex(decoded);
}

int main() {
    std::ifstream file("file.txt");
    std::string line;
    std::cout << "Searching file..." << "\n\n";
    std::vector<int> lengths = getKeyLength();
    std::vector<std::vector<std::string>> blocks(lengths.back());

    std::string ciphertext;
    while (getline(file, line)) {
        ciphertext += line;
    }

    ciphertext = base64_to_hex(ciphertext);

    // std::cout << "Ciphertext: " << ciphertext << "\n\n";

    int keyLenCandidate;
    double minNormalized = 1e6;
    for (int keyLength : lengths) {
        // std::cout << "Key length: " << keyLength << "\n";

        // Initialize variables for averaging
        double totalHammingDistance = 0;
        double totalNormalizedDistance = 0;

        int numBlocks = ciphertext.length() / keyLength; // Number of complete blocks
        for (int i = 0; i < numBlocks - 1; i++) {
            std::string block1 = ciphertext.substr(i * keyLength, keyLength);
            std::string block2 = ciphertext.substr((i + 1) * keyLength, keyLength);

            std::string blockBinary = ascii_to_binary(block1);
            std::string blockBinary2 = ascii_to_binary(block2);

            int hammingDistance = calculateHammingDistance(blockBinary, blockBinary2);
            double normalizedDistance = static_cast<double>(hammingDistance) / keyLength;

            totalHammingDistance += hammingDistance;
            totalNormalizedDistance += normalizedDistance;

            // std::cout << "Block " << i + 1 << " - Hamming distance: " << hammingDistance << "\n";
            // std::cout << "Block " << i + 1 << " - Normalized distance: " << normalizedDistance << "\n";
        }

        // Average the distances
        double averageHammingDistance = totalHammingDistance / (numBlocks - 1);
        double averageNormalizedDistance = totalNormalizedDistance / (numBlocks - 1);

        // std::cout << "Average Hamming distance: " << averageHammingDistance << "\n";
        // std::cout << "Average Normalized distance: " << averageNormalizedDistance << "\n\n";

        if (averageNormalizedDistance < minNormalized){
            keyLenCandidate = keyLength;
            minNormalized = averageNormalizedDistance;
        }
    }

    std::cout << "Found Key length: " << keyLenCandidate << "\n";
    std::cout << "Minimum Normalized distance: " << minNormalized << "\n\n";

    blocks.resize(keyLenCandidate); // Resize blocks to the correct size

    for (int index = 0; index < ciphertext.length(); index += keyLenCandidate) {
        std::string block = ciphertext.substr(index, keyLenCandidate);

        for (int i = 0; i < keyLenCandidate; i+=2) {
            char hex1 = block[i];
            char hex2 = block[i+1];

            std::string hex;
            hex += hex1;
            hex += hex2;
            
            blocks[i].push_back(hex); // Append character to each block
        }
    }

    std::string key;
    for (int i = 0; i < blocks.size(); i++) {
        std::cout << "Block " << i << ": ";
        std::string block;
        for (int j = 0; j < blocks[i].size(); j++) {
            block += blocks[i][j];
        }
        std::cout << block << "\n\n";

        std::unordered_map<char, std::pair<double, std::string>> characterTable;

        char bestCharacter;
        double bestScore = 0;
        for (int i = 0; i < 95; i++) {
            char c = i + ' ';

            std::string xorString = XorAscii(block, c);

            double score = scoreText(xorString);
            characterTable[c] = std::make_pair(score, xorString);

            if (characterTable[c].first > bestScore) {
                bestScore = characterTable[c].first;
                bestCharacter = c;
            }
        }
        std::cout << bestScore << "\n";

        key += bestCharacter;
    }

    // key = "Terminator X: Bring the noise";

    std::cout << "Key: " << key << "\n";

    // Decrypt the ciphertext using the key
    std::string decryptedMessage;
    for (int i = 0; i < ciphertext.length(); ++i) {
        char decryptedChar = ciphertext[i] ^ key[i % key.length()];
        decryptedMessage += decryptedChar;
    }

    // Print the final decrypted message
    std::cout << "Decrypted Message: " << decryptedMessage << "\n";

    return 0;
}