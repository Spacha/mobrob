import socket
import time
import json

# client (robot) information
UDP_IP = "192.168.1.168"
UDP_PORT = 3333

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(f"Sending messages to {UDP_IP}:{UDP_PORT}...")

seq_no = 1
state = 'DISCONNECTED'

def send_message(msg_type, data):
    global seq_no
    print(f"Sending message: type: {msg_type}, data: {data}")

    sock.sendto(bytes(json.dumps({
        'seq_no': seq_no,
        'type': msg_type,
        'data': data,
    }), 'ascii'), (UDP_IP, UDP_PORT))

    seq_no += 1

while True:
    try:
        #message = f"Current time is: {time.time()} seconds."
        #print(f"Sending message: {message}")
        #sock.sendto(bytes(message, 'ascii'), (UDP_IP, UDP_PORT))
        time.sleep(1)

        if state == 'DISCONNECTED':
            send_message('ROBOT_HELLO', {
                'fw_version': '1.2.3'
            })

    #except IOError as msg:
    #    pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
