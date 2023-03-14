import socket

# server information
UDP_IP = "192.168.1.154"
UDP_PORT = 3333

BUFSIZE = 1024
TIMEOUT = 1

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

# looks like timeout is needed in order to receive input from the keyboard (e.g. KeyboardInterrupt)
sock.settimeout(TIMEOUT)

print(f"Listening at {UDP_PORT}...")

while True:
    try:
        data, addr = sock.recvfrom(BUFSIZE)
        print(f"received message [from client {addr}]: {data}")
    except IOError as msg:
        pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
