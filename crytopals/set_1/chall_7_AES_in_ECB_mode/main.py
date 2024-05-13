import requests
import base64
from Crypto.Cipher import AES

def base64_decode(data):
    return base64.b64decode(data)

def aes_ecb_decrypt(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted = cipher.decrypt(ciphertext)
    return decrypted

URL = 'https://cryptopals.com/static/challenge-data/7.txt'
ciphertext_b64 = requests.get(URL).text
ciphertext = base64_decode(ciphertext_b64)

# Key for AES ECB mode (16 bytes for AES-128)
key = b'YELLOW SUBMARINE'

# AES ECB decryption
plaintext = aes_ecb_decrypt(ciphertext, key)

# Remove PKCS7 padding (assuming it's there)
pad_length = plaintext[-1]
plaintext = plaintext[:-pad_length]

print(plaintext.decode('utf-8'))
