#include <iostream>
#include <vector>
#include <fstream>
#include <bitset>

std::vector<int> getKeyLength() {
    std::vector<int> lengths;
    for (int i = 2; i < 41; i++) {
        lengths.push_back(i);
    }
    return lengths;
}

std::string base64_to_ascii(const std::string& base64_string) {
    // Base64 characters
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string ascii_result = "";
    size_t in_len = base64_string.size();
    int i = 0;
    int bit_count = 0;
    unsigned int bits = 0;

    for (char c : base64_string) {
        // Ignore padding '=' characters
        if (c == '=') {
            break;
        }
        
        // Find the index of the current character in the base64_chars
        size_t index = base64_chars.find(c);
        if (index != std::string::npos) {
            bits = (bits << 6) | index;
            bit_count += 6;

            // If we have 8 or more bits accumulated, convert to ASCII
            if (bit_count >= 8) {
                bit_count -= 8;
                ascii_result += static_cast<char>((bits >> bit_count) & 0xFF);
            }
        } else {
            std::cerr << "Invalid Base64 character: " << c << std::endl;
            return "";  // Return empty string on error
        }
    }

    return ascii_result;
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


int main() {
    std::ifstream file("file.txt");
    std::string line;
    std::cout << "Searching file..." << "\n\n";
    std::vector<int> lengths = getKeyLength();
    std::vector<std::vector<std::string>> blocks(lengths.back());
    while (getline(file, line)) {
        int keyLenCandidate;
        double minNormalized = 1e6;
        for (int keyLength : lengths) {
            // std::cout << "Key length: " << keyLength << "\n";

            // Initialize variables for averaging
            double totalHammingDistance = 0;
            double totalNormalizedDistance = 0;

            int numBlocks = line.length() / keyLength; // Number of complete blocks
            for (int i = 0; i < numBlocks - 1; i++) {
                std::string block1 = line.substr(i * keyLength, keyLength);
                std::string block2 = line.substr((i + 1) * keyLength, keyLength);

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

        for (int index = 0; index < line.length(); index += keyLenCandidate) {
            std::string block = line.substr(index, keyLenCandidate);

            for (int i = 0; i < keyLenCandidate; i++) {
                blocks[i].push_back(std::string(1, block[i])); // Append character to each block
            }
        }

        for (int i = 0; i < blocks.size(); i++) {
            std::cout << "Section " << i << ": ";
            for (int j = 0; j < blocks[i].size(); j++) {
                std::cout << blocks[i][j];
            }
            std::cout << "\n";
        }

        break;
    }
    return 0;
}