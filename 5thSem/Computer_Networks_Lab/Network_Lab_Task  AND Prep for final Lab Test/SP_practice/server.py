import socket
import threading 
import logging

logging.basicConfig(
    filename='server.log',
    level=logging.INFO,
    format='%(asctime)s - %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)

# Create TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind server
server.bind(('0.0.0.0', 6006))

# Listen for connections
server.listen(5)

print("TCP server listening on port 6006...")
logging.info("TCP server listening on port 6006...")

clients = []

def broadcast(message, sender):
    for client in clients:
        if sender != client:
            try:
                client.sendall(message)
            except:
                client.remove(client)

def handle_client(client_socket, addr):
    while True:
        try:
            msg = client_socket.recv(1024)
            if not msg:
                break;
            print(f"{addr} says: {msg.decode('utf-8')}")
            logging.info(f"Forwarded message from {addr}: {msg.decode('utf-8')}")
            broadcast(msg, client_socket)
        except:
            break
    #disconnet
    logging.info(f"{addr} disconnected")
    clients.remove(client_socket)
    client_socket.close()
    print(f"{addr} disconnected")
   
# main
try:
    while True:
        client_sock, addr = server.accept()
        clients.append(client_sock)
        thread = threading.Thread(target=handle_client, args=(client_sock, addr), daemon=True)
        thread.start()
except KeyboardInterrupt:
    print("\nServer shutting down...")
    logging.info("Server stopped")
finally:
    server.close();
    server.close();