import socket
import time
from math import ceil

# client (robot) information
UDP_IP = "192.168.1.166"
UDP_PORT = 3333
BUFSIZE = 64

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("192.168.1.168", UDP_PORT)) # server's address
sock.settimeout(1)

print("Waiting for client to connect...")

connected = False
client_addr = None
while not connected:
    try:
        data, addr = sock.recvfrom(BUFSIZE)
        print(f"received message [from client {addr}]: {data}")

        if data == b'Hello Server!':
            client_addr = addr
            connected = True
            sock.sendto(bytes("Hello, client!", 'ascii'), client_addr)

    except IOError as msg:
        pass  # timed out, try again...
    except KeyboardInterrupt:
        break

print(f"\nClient connected! Starting communication with  {client_addr[0]}:{client_addr[1]}...")

while True:
    try:
        message = input(f"Message to the robot (max {BUFSIZE} characters): ")
        if len(message) > BUFSIZE:
            print("Too long message, try again!")
            continue
        print(f"Sending message: {message}")
        # ascii input mode
        #sock.sendto(bytes(message, 'ascii'), (UDP_IP, UDP_PORT))
        # binary input mode
        sock.sendto(int(message, 2).to_bytes(ceil(len(message) / 8), 'little'), client_addr)
    except IOError as msg:
        pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
