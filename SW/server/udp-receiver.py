import socket

# server information
UDP_IP = "192.168.1.168"
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

        # send a response (unless the message begins with 'Got' :D):
        if data == b'Hello Server!':
            sock.sendto(bytes('Hello to you too!', 'ascii'), addr)
        if data[:3] != b'Got':
            sock.sendto(bytes('Hello robo, how doink?', 'ascii'), addr)
    except IOError as msg:
        pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
