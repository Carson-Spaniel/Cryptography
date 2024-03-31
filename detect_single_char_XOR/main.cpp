#include <iostream>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <fstream>

std::unordered_map<char, double> frequencyTable = {
    {'e', 12.70}, {'t', 9.06}, {'a', 8.17}, {'o', 7.51}, {'i', 6.97},
    {'n', 6.75}, {'s', 6.33}, {'h', 6.09}, {'r', 5.99}, {'d', 4.25},
    {'l', 4.03}, {'c', 2.78}, {'u', 2.76}, {'m', 2.41}, {'w', 2.36},
    {'f', 2.23}, {'g', 2.02}, {'y', 1.97}, {'p', 1.93}, {'b', 1.29},
    {'v', 0.98}, {'k', 0.77}, {'j', 0.15}, {'x', 0.15}, {'q', 0.10},
    {'z', 0.07}
};

double scoreText(const std::string& text) {
    std::unordered_map<char, int> observedFreq;
    bool space = false;
    for (char ch : text) {
        if (int(ch) == 32){
            space = true;
        }

        if(!space && (int(ch) > 126 || int(ch) < 32)) return 1e5;

        if (isalpha(ch)) {
            observedFreq[tolower(ch)]++;
        }
    }

    if (!space) return 1e5;

    // Calculate Chi-Squared statistic
    double score = 0.0;
    for (const auto& pair : frequencyTable) {
        char letter = pair.first;
        double expectedFreq = pair.second;
        double observedFreqLetter = observedFreq[letter];
        double chi = pow(observedFreqLetter - expectedFreq, 2) / expectedFreq;
        score += chi;
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

int main() {
    std::ifstream file("file.txt");

    std::string message;
    char character;
    int overallBestScore = 1e5;
    std::string line;
    std::cout << "Searching file..." << "\n\n";
    while (getline(file, line)) {
        std::unordered_map<char, std::pair<double, std::string>> characterTable;

        char bestCharacter;
        double bestScore = 1e5;
        for (int i = 0; i < 256; i++) {
            char c = i + ' ';

            std::string xorString = XorAscii(line, c);

            double score = scoreText(xorString);
            characterTable[c] = std::make_pair(score, xorString);

            if (characterTable[c].first < bestScore) {
                bestScore = characterTable[c].first;
                bestCharacter = c;
            }

            if (characterTable[c].first < overallBestScore) {
                overallBestScore = characterTable[c].first;
                character = c;
                message = characterTable[c].second;
            }
        }
    }

    std::cout << "Found character: " << character << "\n";
    std::cout << "Message reads: " << message << "\n";

    return 0;
}

