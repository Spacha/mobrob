import socket
import time

# server information
UDP_IP = "192.168.1.168"
UDP_PORT = 3333
BUFSIZE = 64

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Cool sender huh?")

while True:
    print()
    try:
        destination = input(f"Destination (IP:PORT) (leave empty for default): ")
        dest_ip = UDP_IP
        dest_port = UDP_PORT
        if len(destination) > 0:
            try:
                dest_ip, dest_port = destination.split(':')
                dest_port = int(dest_port)
            except ValueError:
                print("Invalid destination! Example destination: '192.168.1.123:3333'.")
                continue

        while True:
            print(f"Sending message to {dest_ip}:{dest_port}...")
            message = input(f"Message (max {BUFSIZE - 1} characters): ")

            if len(message) >= BUFSIZE:
                print("Too long message, try again!")
                continue

            print(f"Sending message (ascii): {message}")
            #sock.sendto(bytes(message, 'ascii'), (dest_ip, dest_port))
            break

    #except IOError as msg:
    #    pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
