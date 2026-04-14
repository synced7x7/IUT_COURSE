import socket, time, threading
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ('0.0.0.0', 6006)

sock.settimeout(1.0)
message = 'Hello Sadman'

def recieve_message(data, addr):
    d= data.recv(1024)
    if not d:
        return
    print (f" Received { d !r} from { addr }")

try:
    data, _ = sock.recvfrom(1024)
    threading.Thread(target=recieve_message, args=(data, ), daemon=True).start()
    print(f'Received response from server: {data.decode()}')
except socket.timeout:
    print('No response from server, timed out.')