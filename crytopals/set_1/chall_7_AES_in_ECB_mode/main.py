import requests
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import base64

def base64_decode(data):
    return base64.b64decode(data)

def aes_ecb_decrypt(ciphertext, key):
    cipher = AES.new(key, AES.MODE_ECB)
    plaintext = cipher.decrypt(ciphertext)
    return plaintext

URL = 'https://cryptopals.com/static/challenge-data/7.txt'
ciphertext_b64 = requests.get(URL).text
ciphertext = base64_decode(ciphertext_b64)

# Key for AES ECB mode (16 bytes for AES-128)
key = b'YELLOW SUBMARINE'

plaintext = aes_ecb_decrypt(ciphertext, key)

# Remove padding
plaintext = plaintext.rstrip(b'\x04')

print(plaintext.decode('utf-8'))
