import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('0.0.0.0', 5005))

print('UDP server is running on port 5005...')

def handle_request(data, addr):
    print(f'Received message from {addr}: {data.decode()}')
    sock.sendto(data, addr)

try:
    while True:
        data, addr = sock.recvfrom(1024)
        print(f'Received message from {addr}: {data.decode()}')

        sock.sendto(data, addr)
except KeyboardInterrupt:
    print("Server is closing")
    sock.close()

