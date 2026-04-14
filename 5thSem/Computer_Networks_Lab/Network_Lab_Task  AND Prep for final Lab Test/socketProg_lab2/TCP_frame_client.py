import socket
import struct
import sys

# Use command-line argument if provided
HOST = sys.argv[1] if len(sys.argv) > 1 else '127.0.0.1'
PORT = 7007

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect((HOST, PORT))

for msg in ["hello", "this is a longer message", "bye"]:
    # Convert string to bytes
    data = msg.encode()

    # Send: 4-byte length prefix + actual data
    client.sendall(struct.pack('!I', len(data)) + data)

    # Receive 4-byte response header
    hdr = client.recv(4)
    if not hdr:
        print("Server closed")
        break

    # Extract message length
    (length,) = struct.unpack('!I', hdr)

    # Receive full response payload
    resp = b''
    while len(resp) < length:
        chunk = client.recv(length - len(resp))
        if not chunk:
            break
        resp += chunk

    print("Echo:", resp.decode())

client.close()