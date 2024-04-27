import socket
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes

def run_server():
    host = '127.0.0.1'
    port = 12345

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen(1)

    print("Server is running...")

    aes_key = get_random_bytes(32)

    while True:
        conn, addr = server.accept()
        print(f"Connected to {addr}")

        data = conn.recv(1024)
        if not data:
            break

        cipher = AES.new(aes_key, AES.MODE_OCB)
        ciphertext, tag = cipher.encrypt_and_digest(data)

        conn.sendall(ciphertext)

        conn.close()

if __name__ == "__main__":
    run_server()
