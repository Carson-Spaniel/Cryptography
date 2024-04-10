from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import os
import sys

if len(sys.argv) != 2:
    print("Usage: py AES_encrypt.py <filename>")
    sys.exit(1)

file = sys.argv[1]

file_extension = os.path.splitext(file)[1]

with open(f'{file}', 'rb') as f:
    data = f.read()

aes_key = get_random_bytes(16)

file_extension_xor = ''
for letter in range(len(file_extension)):
    file_extension_xor += chr(ord(file_extension[letter]) ^ aes_key[letter])

cipher = AES.new(aes_key, AES.MODE_OCB)
ciphertext, tag = cipher.encrypt_and_digest(data)
assert len(cipher.nonce) == 15

with open("encrypted.bin", "wb") as f:
    f.write(tag)
    f.write(cipher.nonce)
    f.write(ciphertext)

with open("key.bin", "wb") as f:
    f.write(aes_key)
    f.write(file_extension_xor.encode())
