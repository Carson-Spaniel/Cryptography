#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

std::string hexToBase64(const std::string &hex) {
    // Hex to binary
    std::string binary;
    for (char c : hex) {
        int value;
        if (c >= '0' && c <= '9') {
            value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            value = c - 'A' + 10;
        } else {
            std::cerr << "Invalid hex character: " << c << std::endl;
            return "";
        }
        binary += std::bitset<4>(value).to_string();
    }

    // Binary to base64
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string base64;
    size_t padding = 0;
    for (size_t i = 0; i < binary.length(); i += 6) {
        std::string chunk = binary.substr(i, 6);
        while (chunk.length() < 6) {
            chunk += "0"; // Padding with zeros if necessary
            padding++;
        }
        int index = std::stoi(chunk, nullptr, 2);
        base64 += base64_chars[index];
    }

    // Add padding '=' characters
    for (size_t i = 0; i < padding; ++i) {
        base64 += "=";
    }

    return base64;
}

int main() {
    std::string hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string base64_output = hexToBase64(hex_input);
    
    std::cout << "Input (Hex): " << hex_input << std::endl;
    std::cout << "Output (Base64): " << base64_output << std::endl;

    return 0;
}
