import socket

def run_client():
    host = '127.0.0.1'
    port = 12345

    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((host, port))

    message = "Hello, VPN Server!"
    client.sendall(message.encode())

    response = client.recv(1024)
    print("Received from server:", response)

    client.close()

if __name__ == "__main__":
    run_client()
