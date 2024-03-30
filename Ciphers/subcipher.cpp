#include <iostream>
#include <string>
#include <vector>

std::string decrypt(const std::string& ciphertext, const std::string& keyword) {
    std::string decrypted = ciphertext;
    int keyLen = keyword.length();
    int textLen = decrypted.length();

    int characters[textLen];

    for (int i = 0; i < textLen; i++) {
        int keyIndex = i % keyLen; // Handle repeating keyword
        int num1 = decrypted[i];
        int num2 = keyword[keyIndex];
        characters[i] = 156 + ((int(decrypted[i]) - int(keyword[keyIndex]))); // Ensure result is in ASCII range
    }

    for (int i = 0; i < textLen; i++) {
        decrypted[i] = char(characters[i]);
    }

    return decrypted;
}

std::string encrypt(const std::string& ciphertext, const std::string& keyword){
    std::string encrypted = ciphertext;
    int keyLen = keyword.length();
    int textLen = encrypted.length();

    int characters[textLen];

    for (int i = 0; i < textLen; i++) {
        int keyIndex = i % keyLen; // Handle repeating keyword
        characters[i] = (int(encrypted[i]) + int(keyword[keyIndex])) % 94 + 32; // Ensure result is in ASCII range
    }


    for (int i=0;i<textLen;i++){
        encrypted[i] = characters[i];
    }

    return encrypted;
}

int main() {
    std::string plaintext = "This is my message to you";
    std::string keyword = "thisisapersonalkeyforyou";

    std::string encrypted = encrypt(plaintext, keyword);
    std::cout << "Encrypted message: " << encrypted << std::endl;

    std::string decrypted = decrypt(encrypted, keyword);
    std::cout << "Decrypted message: " << decrypted << std::endl;
    return 0;
}
