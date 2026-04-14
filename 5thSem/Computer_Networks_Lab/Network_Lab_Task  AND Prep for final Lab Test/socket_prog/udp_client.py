import socket, time
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('localhost', 5005)

sock.settimeout(1.0)
message = 'Hello Sadman'

sock.sendto(message.encode(), server_address)

try:
    data, addr = sock.recvfrom(1024)
    print(f'Received response from server: {data.decode()}')
except socket.timeout:
    print('No response from server, timed out.')