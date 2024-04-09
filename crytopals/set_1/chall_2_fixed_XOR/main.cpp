#include <iostream>
#include <string>
#include <bitset>
#include <sstream>

std::string toBinary(std::string hex){
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

    return binary;
}

char XOR(bool a, bool b){
    return !a != !b;
}

std::string binaryToHex(std::string binary) {
    // Pad the binary string to ensure its length is a multiple of 4
    size_t len = binary.length();
    size_t pad_len = (4 - len % 4) % 4;
    binary.insert(0, pad_len, '0');

    // Create a stringstream to store the result
    std::stringstream hex_ss;

    // Convert each group of 4 binary digits to hexadecimal
    for (size_t i = 0; i < len + pad_len; i += 4) {
        std::string group = binary.substr(i, 4);
        int decimal = std::bitset<4>(group).to_ulong();
        if (decimal < 10)
            hex_ss << static_cast<char>('0' + decimal);
        else
            hex_ss << static_cast<char>('a' + decimal - 10);
    }

    return hex_ss.str();
}

std::string hexXOR(std::string a, std::string b){
    std::string binA = toBinary(a);
    std::string binB = toBinary(b);

    std::string binary;
    for (int i=0; i<binA.length(); i++) {
        char c = XOR(binA[i]=='1',binB[i]=='1');
        binary += std::bitset<1>(c).to_string();
    }

    std::cout << binary << "\n";

    std::string hex = binaryToHex(binary);

    return hex;
}


int main() {
    std::string input = "1c0111001f010100061a024b53535009181c";
    std::string xorInput = "686974207468652062756c6c277320657965";

    std::cout << input.length() << " " << xorInput.length() << "\n";
    std::string output = hexXOR(input, xorInput);
    
    std::cout << "Output: " << output << std::endl;

    return 0;
}

