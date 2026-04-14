import socket
import struct

# Listen on all network interfaces
HOST = '10.170.232.240'
PORT = 7007


def recv_all(sock, n):
    """
    Receive exactly n bytes from the socket.
    TCP does not guarantee that recv(n) returns n bytes,
    so we must loop until all bytes are received.
    """
    data = b''
    while len(data) < n:
        chunk = sock.recv(n - len(data))
        if not chunk:  # Connection closed
            return None
        data += chunk
    return data


# Create TCP socket (IPv4, Stream-based)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Allow quick reuse of the port after restart
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# Bind to address and port
server.bind((HOST, PORT))

# Listen for incoming connections (queue size 5)
server.listen(5)
print("Length-prefixed TCP server on", PORT)

# Accept one client connection
conn, addr = server.accept()
print("Connected by", addr)

try:
    while True:
        # Step 1: Read the 4-byte length header
        hdr = recv_all(conn, 4)
        if not hdr:
            break  # Client disconnected

        # '!I' = Network byte order (big-endian) unsigned int
        (length,) = struct.unpack('!I', hdr)

        # Step 2: Read exactly 'length' bytes of payload
        payload = recv_all(conn, length)
        if payload is None:
            break

        print("Got message:", payload.decode())

        # Step 3: Echo back using same framing format
        # First pack length, then append payload
        conn.sendall(struct.pack('!I', len(payload)) + payload)

finally:
    conn.close()
    server.close()