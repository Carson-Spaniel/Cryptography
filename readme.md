# Cryptopals Set 1: Cryptography Challenges

This repository contains my solutions to the Cryptopals Set 1 cryptography challenges, implemented in both C++ and Python. Additionally, I have included implementations of various ciphers, along with tools for breaking them, as well as an XOR game and a simple VPN.

## Cryptopals Set 1

The Cryptopals Set 1 Challenges are designed to introduce and reinforce fundamental concepts in cryptography, such as bitwise operations, encoding schemes, and basic ciphers. This repository provides my solutions to each challenge, along with explanations and documentation.

### Challenge 1: Convert hex to base64

This challenge involves converting a hex-encoded string to a base64-encoded string.

### Challenge 2: Fixed XOR

In this challenge, we perform a fixed XOR operation on two equal-length buffers.

### Challenge 3: Single-byte XOR cipher

This challenge requires us to break a single-byte XOR cipher and recover the plaintext message.

### Challenge 4: Detect single-character XOR

Here, we need to detect a single-character XOR encrypted string from a set of strings, and decrypt it.

### Challenge 5: Implement repeating-key XOR

In this challenge, we implement a repeating-key XOR cipher.

### Challenge 6: Break repeating-key XOR

Building on the previous challenge, we now need to break a repeating-key XOR cipher and recover the plaintext message.

### Challenge 7: AES in ECB mode

This challenge involves decrypting data encrypted using AES in ECB mode.

### Challenge 8: Detect AES in ECB mode

Here, we need to detect encrypted data that was encrypted using AES in ECB mode.

## Cryptopals Set 2

The Cryptopals Set 2 challenges build upon the concepts introduced in Set 1 and delve deeper into more advanced cryptographic topics, such as byte-level operations, block cipher modes, and padding schemes. This repository includes my solutions to these challenges, along with detailed explanations and documentation.

### Challenge 9: Implement PKCS#7 padding

Implementing the PKCS#7 padding scheme, which is used to ensure that the plaintext data is a multiple of the block size for block cipher operations.

## Additional Ciphers and Tools

### AES Cipher with SHA256 Hashed Key

This section includes an implementation of the Advanced Encryption Standard (AES) cipher, using a key derived from a SHA256 hash.

### Vigenère Cipher

The Vigenère cipher is a polyalphabetic substitution cipher that encrypts text by using a keyword to shift the letters of the plaintext. The code implements this while also trying to break it. Breaking the code uses brute force.

### Caesar Cipher

A simple substitution cipher where each letter in the plaintext is replaced by a letter a fixed number of positions down the alphabet.

### XOR Game

An interactive game where you need to "decrypt" a quote by performing XOR operations on the ciphertext. Similar to cryptograms, this exercise reinforces the concepts of XOR operations and bitwise manipulation.

### Simple VPN

This section includes a simple implementation of a Virtual Private Network (VPN), demonstrating basic networking and encryption concepts.