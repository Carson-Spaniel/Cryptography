import requests

def hex_decode(data):
    return bytes.fromhex(data)

URL = 'https://cryptopals.com/static/challenge-data/8.txt'
ciphertext_b64 = requests.get(URL).text.split("\n")

for num, ciphertext in enumerate(ciphertext_b64):
    data = hex_decode(ciphertext)
    chunks = [data[i:i+16] for i in range(0, len(data), 16)]
    for i, ch in enumerate(chunks):
        count = chunks.count(ch)
        if count != 1:
            print(num, i, count)