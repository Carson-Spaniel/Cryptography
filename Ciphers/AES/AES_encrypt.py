from Crypto.Cipher import AES
import os
import sys

def pkcs_7(plaintext, blocksize):
    blocks = [plaintext[i:i+blocksize] for i in range(0, len(plaintext), blocksize)]
    last_block = blocks[-1]

    if len(last_block) < blocksize:
        pad = blocksize - len(last_block)
        blocks[-1] += bytes([pad] * pad)

    return b"".join(blocks)

def encrypt_file(file_path, encrypt_dir, key_path):
    with open(key_path, 'rb') as f:
        aes_key = f.read()

    with open(file_path, 'rb') as f:
        data = f.read()

    file_info = os.path.splitext(file_path)
    file_name = file_info[0].split('\\')[-1]
    file_extension = file_info[1]
    file_extension_xor = ''.join(chr(ord(file_extension[i]) ^ aes_key[i % 16]) for i in range(len(file_extension)))

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
    if len(sys.argv) != 3:
        print("Usage: py AES_encrypt.py <file_or_folder_path> <key_file>")
        sys.exit(1)

    path = sys.argv[1]
    key_path = sys.argv[2]
    encrypt_dir = './Encrypted/'

    if os.path.isfile(path):
        # Encrypt a single file
        encrypt_file(path, encrypt_dir, key_path)
        print(f"File '{path}' encrypted.")
    elif os.path.isdir(path):
        # Encrypt all files in a folder
        encrypt_folder(path, encrypt_dir, key_path)
        print(f"All files in folder '{path}' encrypted and saved in '{encrypt_dir}'.")
    else:
        print(f"Error: '{path}' is not a valid file or folder.")
        sys.exit(1)

if __name__ == "__main__":
    main()
