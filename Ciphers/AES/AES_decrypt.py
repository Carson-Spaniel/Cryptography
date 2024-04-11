from Crypto.Cipher import AES
import os
import sys

def unpkcs_7(padded_text):
    pad_byte = padded_text[-1]
    if pad_byte < 1 or pad_byte > 16:
        raise ValueError("Invalid padding byte")

    padding = padded_text[-pad_byte:]
    if not all(padding[b] == pad_byte for b in range(len(padding))):
        raise ValueError("Invalid padding bytes")

    return padded_text[:-pad_byte]

def decrypt_file(file_path, key_path):
    key_file = key_path

    if not os.path.exists(key_file):
        print(f"Key file '{key_file}' not found. Skipping decryption for '{file_path}'")
        return

    with open(key_file, "rb") as f:
        aes_key = f.read(16)

    encrypted_file = file_path + "_encrypted.bin"

    with open(encrypted_file, "rb") as f:
        file_type_xor = f.read(16)
        tag = f.read(16)
        nonce = f.read(15)
        ciphertext = f.read()

    file_type_xor = unpkcs_7(file_type_xor).decode()

    file_extension = ''.join(chr(ord(file_type_xor[i]) ^ aes_key[i % 16]) for i in range(len(file_type_xor)))
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
        
def decrypt_folder(folder_path, key_path):
    for root, _, files in os.walk(folder_path):
        for file in files:
            if file.endswith("_encrypted.bin"):
                file_path = os.path.join(root, file.replace("_encrypted.bin", ""))
                decrypt_file(file_path, key_path)

def main():
    if len(sys.argv) != 3:
        print("Usage: py AES_decrypt.py <folder_path> <key_path>")
        sys.exit(1)

    path = sys.argv[1]

    if os.path.isfile(path):
        # Decrypt a single file
        decrypt_file(os.path.splitext(path)[0], sys.argv[2])
    elif os.path.isdir(path):
        # Decrypt all files in a folder
        decrypt_folder(path, sys.argv[2])
    else:
        print(f"Error: '{path}' is not a valid file or folder.")
        sys.exit(1)

if __name__ == "__main__":
    main()
