from Crypto.Cipher import AES

with open("key.bin", "rb") as f:
    aes_key = f.read(16)
    file_type = f.read().decode()

file_extension = ''
for letter in range(len(file_type)):
    file_extension += chr(ord(file_type[letter]) ^ aes_key[letter])

with open("encrypted.bin", "rb") as f:
    tag = f.read(16)
    nonce = f.read(15)
    ciphertext = f.read()

cipher = AES.new(aes_key, AES.MODE_OCB, nonce=nonce)
try:
    message = cipher.decrypt_and_verify(ciphertext, tag)
    with open(f"decrypted_file{file_extension}", "wb") as f:
        f.write(message)
except ValueError:
    print("The message was modified!")
    exit(1)