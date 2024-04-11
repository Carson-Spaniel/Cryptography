from Crypto.Cipher import AES
from Crypto.Hash import SHA256
import os
import sys
import getpass

def hash_string(input_string):
    sha256 = SHA256.new()
    sha256.update(input_string.encode('utf-8'))
    return sha256.digest()

def pkcs_7(plaintext, blocksize):
    blocks = [plaintext[i:i+blocksize] for i in range(0, len(plaintext), blocksize)]
    last_block = blocks[-1]

    if len(last_block) < blocksize:
        pad = blocksize - len(last_block)
        blocks[-1] += bytes([pad] * pad)

    return b"".join(blocks)

def encrypt_file(file_path, encrypt_dir, aes_key):

    with open(file_path, 'rb') as f:
        data = f.read()

    file_info = os.path.splitext(file_path)
    file_name = os.path.basename(file_path)
    file_extension = file_info[1]
    file_extension_xor = ''.join(chr(ord(file_extension[i]) ^ aes_key[i % len(aes_key)]) for i in range(len(file_extension)))
    if not file_extension_xor:
        return

    file_ext = pkcs_7(file_extension_xor.encode(), 16)
    
    cipher = AES.new(aes_key, AES.MODE_OCB)
    ciphertext, tag = cipher.encrypt_and_digest(data)

    # Ensure encrypt_dir ends with a slash
    if not encrypt_dir.endswith(os.path.sep):
        encrypt_dir += os.path.sep

    # Create encrypt_dir if it does not exist
    if not os.path.exists(encrypt_dir):
        os.makedirs(encrypt_dir)

    with open(os.path.join(encrypt_dir, f"{file_name}_encrypted.bin"), "wb") as f:
        f.write(file_ext)
        f.write(tag)
        f.write(cipher.nonce)
        f.write(ciphertext)

    print(f'Encrypted {file_info[0]}{file_info[1]}')

def encrypt_folder(folder_path, encrypt_dir, key_path):
    for root, _, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            encrypt_file(file_path, encrypt_dir, key_path)

def main():
    if len(sys.argv) == 2:
        while True:
            key_string = getpass.getpass("Enter encryption password: ")
            confirm_key_string = getpass.getpass("Confirm encryption password: ")

            if key_string == confirm_key_string:
                aes_key = hash_string(key_string)
                break
            else:
                print("Passwords do not match. Please try again.")

    elif len(sys.argv) == 3:
        with open(sys.argv[2], 'rb') as f:
            aes_key = f.read()
    else:
        print("Usage: \n\t\033[33mpy\033[0m AES_encrypt.py \033[34m<file_or_folder_path> <key_file>\033[0m or\n\t\033[33mpy\033[0m AES_encrypt.py \033[34m<file_or_folder_path> \033[32m(custom key generation)\033[0m")
        sys.exit(1)

    path = sys.argv[1]
    encrypt_dir = 'Encrypted'

    with open(f"key.bin", "wb") as f:
        f.write(aes_key)
        print(f"\n\033[31mKey created. Don't forget to save it or delete it!\nLocated at: '{os.path.abspath('key.bin')}'\033[0m\n")

    if os.path.isfile(path):
        # Encrypt a single file
        encrypt_file(path, encrypt_dir, aes_key)
        print(f"\n\033[32mFile '{path}' encrypted.\033[0m")
    elif os.path.isdir(path):
        # Encrypt all files in a folder
        encrypt_folder(path, encrypt_dir, aes_key)
        print(f"\n\033[32mAll files in folder '{path}' encrypted and saved in '{encrypt_dir}'.\033[0m")
    else:
        print(f"Error: '{path}' is not a valid file or folder.")
        sys.exit(1)

if __name__ == "__main__":
    main()
