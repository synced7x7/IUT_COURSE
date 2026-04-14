import socket
import threading
import sys
import os

def receive_messages(client_socket):
    """Thread function to receive and print messages from the server."""
    while True:
        try:
            data = client_socket.recv(1024)
            if not data:
                print("\nDisconnected from server.")
                break
            
            
            sys.stdout.write("\r\033[K") 
            print(data.decode('utf-8'), end="")
            print("> ", end="", flush=True)
        except Exception as e:
            
            if client_socket.fileno() != -1:
                print(f"\nError receiving message: {e}")
            break
    
    
    os._exit(0)

def main():
    if len(sys.argv) != 3:
        print("Usage: python3 tcp_chat_client.py <server_ip> <port>")
        sys.exit(1)
        
    server_ip = sys.argv[1]
    
    try:
        port = int(sys.argv[2])
    except ValueError:
        print("Port must be an integer.")
        sys.exit(1)
        
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client_socket.connect((server_ip, port))
        print(f"Connected to {server_ip}:{port}")
    except Exception as e:
        print(f"Failed to connect to server: {e}")
        sys.exit(1)
        
    
    recv_thread = threading.Thread(target=receive_messages, args=(client_socket,), daemon=True)
    recv_thread.start()
    
    try:
        while True:
            message = input("> ")
            if message.strip() == '/quit':
                break
            
            if message.strip():
                try:
                    client_socket.send(message.encode('utf-8'))
                except Exception as e:
                    print(f"\nFailed to send message: {e}")
                    break
    except KeyboardInterrupt:
        
        print("\nExiting...")
    except EOFError:
        print("\nExiting...")
    finally:
        client_socket.close()

if __name__ == "__main__":
    main()
