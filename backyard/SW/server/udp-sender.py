import socket
import time

# client (robot) information
UDP_IP = "192.168.1.166"
UDP_PORT = 3333

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Sending messages to {UDP_IP}:{UDP_PORT}...")

while True:
    try:
        message = f"Current time is: {time.time()} seconds."
        print(f"Sending message: {message}")
        sock.sendto(bytes(message, 'ascii'), (UDP_IP, UDP_PORT))
        time.sleep(1)
    #except IOError as msg:
    #    pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
