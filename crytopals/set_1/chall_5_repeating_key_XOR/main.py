def repeating_key_xor(plaintext, key):
    ciphertext = b''
    for i in range(len(plaintext)):
        char = plaintext[i] ^ key[i % len(key)]
        ciphertext += bytes([char])

    return ciphertext

plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
key = "ICE"

plaintext_bytes = bytearray(plaintext, 'utf-8')  # Convert plaintext to bytes
key_bytes = bytearray(key, 'utf-8')  # Convert key to bytes

ciphertext = repeating_key_xor(plaintext_bytes, key_bytes)
print("Plaintext:", plaintext)
print("Key:", key)
print("Ciphertext:", ciphertext.hex())