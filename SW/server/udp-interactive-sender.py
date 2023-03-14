import socket
import time

# client (robot) information
UDP_IP = "192.168.1.166"
UDP_PORT = 3333
BUFSIZE = 64

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Sending messages to {UDP_IP}:{UDP_PORT}...")

while True:
    try:
        message = input(f"Message to the robot (max {BUFSIZE} characters): ")
        if len(message) > BUFSIZE:
            print("Too long message, try again!")
            continue
        print(f"Sending message: {message}")
        sock.sendto(bytes(message, 'ascii'), (UDP_IP, UDP_PORT))
    #except IOError as msg:
    #    pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
