import socket
import threading
import sys

if len(sys.argv) != 3:
    print("Usage: python3 tcp_chat_client.py <server_ip> <port>")
    sys.exit(1)

SERVER_IP = sys.argv[1]
PORT = int(sys.argv[2])

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect((SERVER_IP, PORT))
print("Connected to ChatIUT server. Type /quit to exit")

def receive_messages():
    while True:
        try:
            msg = client.recv(1024)
            if not msg:
                print('Server disconnected')
                break
            print(msg.decode('utf-8'))
        except:
            break

def send_messages():
    while True:
        msg = input()
        if msg.lower() == '/quit':
            client.close()
            print("Disconnected from server.")
            break
        try:
            client.sendall(msg.encode('utf-8'))
        except:
            print("Error sending message.")
            break

recv_thread = threading.Thread(target=receive_messages, daemon=True)
recv_thread.start()

send_thread = threading.Thread(target=send_messages, daemon=True)
send_thread.start()

recv_thread.join()
send_thread.join()




