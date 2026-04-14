import socket
import threading

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('0.0.0.0', 6006))

clients = []

print('UDP server is running on port 6006...')

def handle_request(data, addr):
    d = data.recv(1024)
    if not d:
        return
    print (f" Received { d !r} from { addr }")
    for client in clients:
        sock.sendto(d, client)

try:
    while True:
        data, addr = sock.recvfrom(1024)
        clients.append(addr)
        threading.Thread(target=handle_request, args=(data, addr), daemon=True).start()
except KeyboardInterrupt:
    print("Server is closing")
    sock.close()

