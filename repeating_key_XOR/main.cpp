#include <iostream>
#include <sstream>

int main() {
    std::string plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    std::string key = "ICE";
    
    std::cout << "Plaintext: " << plaintext << "\n";
    std::cout << "Key: " << key << "\n";

    std::string encrypt;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char c = plaintext[i] ^ key[i % key.length()];
        std::stringstream sstream;
        sstream << std::hex << int(c);
        std::string result = sstream.str();

        // Ensure each character is two digits (e.g., 'a' becomes "0a")
        if (result.length() == 1) {
            result = "0" + result;
        }

        encrypt += result;
    }

    std::cout << "Encrypted: " << encrypt << "\n";
    return 0;
}
