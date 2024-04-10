from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import os
import sys

def encrypt_file(file_path, encrypt_dir):
    aes_key = get_random_bytes(16)

    with open(file_path, 'rb') as f:
        data = f.read()

    file_info = os.path.splitext(file_path)
    file_name = file_info[0].split('\\')[-1]
    file_extension = file_info[1]
    file_extension_xor = ''.join(chr(ord(file_extension[i]) ^ aes_key[i % 16]) for i in range(len(file_extension)))

    cipher = AES.new(aes_key, AES.MODE_OCB)
    ciphertext, tag = cipher.encrypt_and_digest(data)

    # Ensure encrypt_dir ends with a slash
    if not encrypt_dir.endswith(os.path.sep):
        encrypt_dir += os.path.sep

    # Create encrypt_dir if it does not exist
    if not os.path.exists(encrypt_dir):
        os.makedirs(encrypt_dir)

    with open(os.path.join(encrypt_dir, f"{file_name}_encrypted.bin"), "wb") as f:
        f.write(tag)
        f.write(cipher.nonce)
        f.write(ciphertext)

    with open(os.path.join(encrypt_dir, f"{file_name}_key.bin"), "wb") as f:
        f.write(aes_key)
        f.write(file_extension_xor.encode())

    print(f'Encrypted {file_info[0]}{file_info[1]}')

def encrypt_folder(folder_path, encrypt_dir):
    for root, _, files in os.walk(folder_path):
        for file in files:
            file_path = os.path.join(root, file)
            encrypt_file(file_path, encrypt_dir)

def main():
    if len(sys.argv) != 3:
        print("Usage: py AES_encrypt.py <file_or_folder_path> <encrypt_dir>")
        sys.exit(1)

    path = sys.argv[1]
    encrypt_dir = sys.argv[2]

    if os.path.isfile(path):
        # Encrypt a single file
        encrypt_file(path, encrypt_dir)
        print(f"File '{path}' encrypted.")
    elif os.path.isdir(path):
        # Encrypt all files in a folder
        encrypt_folder(path, encrypt_dir)
        print(f"All files in folder '{path}' encrypted and saved in '{encrypt_dir}'.")
    else:
        print(f"Error: '{path}' is not a valid file or folder.")
        sys.exit(1)

if __name__ == "__main__":
    main()
