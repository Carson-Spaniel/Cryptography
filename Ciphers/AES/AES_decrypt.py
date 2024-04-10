from Crypto.Cipher import AES
import os
import sys

def decrypt_file(file_path):
    key_file = file_path + "_key.bin"
    if not os.path.exists(key_file):
        print(f"Key file '{key_file}' not found. Skipping decryption for '{file_path}'")
        return

    with open(key_file, "rb") as f:
        aes_key = f.read(16)
        file_type_xor = f.read().decode()

    file_extension = ''.join(chr(ord(file_type_xor[i]) ^ aes_key[i % 16]) for i in range(len(file_type_xor)))

    encrypted_file = file_path + "_encrypted.bin"

    with open(encrypted_file, "rb") as f:
        tag = f.read(16)
        nonce = f.read(15)
        ciphertext = f.read()

    cipher = AES.new(aes_key, AES.MODE_OCB, nonce=nonce)
    try:
        message = cipher.decrypt_and_verify(ciphertext, tag)
        decrypted_dir = "Decrypted"
        if not os.path.exists(decrypted_dir):
            os.makedirs(decrypted_dir)
        decrypted_file_path = os.path.join(decrypted_dir, os.path.basename(file_path) + file_extension)
        with open(decrypted_file_path, "wb") as f:
            f.write(message)
        print(f"Decrypted '{file_path}_encrypted.bin'")
    except ValueError:
        print(f"Failed to decrypt '{file_path}_encrypted.bin'")
        
def decrypt_folder(folder_path):
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith("_encrypted.bin"):
                file_path = os.path.join(root, file.replace("_encrypted.bin", ""))
                decrypt_file(file_path)

def main():
    if len(sys.argv) != 2:
        print("Usage: py AES_decrypt.py <folder_path>")
        sys.exit(1)

    path = sys.argv[1]

    if os.path.isfile(path):
        # Decrypt a single file
        decrypt_file(os.path.splitext(path)[0])
    elif os.path.isdir(path):
        # Decrypt all files in a folder
        decrypt_folder(path)
    else:
        print(f"Error: '{path}' is not a valid file or folder.")
        sys.exit(1)

if __name__ == "__main__":
    main()
