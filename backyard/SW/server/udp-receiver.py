import time, socket, json, random

# server information
SERVER_UDP_IP = "192.168.1.168"
SERVER_UDP_PORT = 3333

UDP_IP = "192.168.1.168"
UDP_PORT = 3030

BUFSIZE = 1024
TIMEOUT = 1.0
POLL_INTERVAL = 2.0
UPDATE_INTERVAL = 1.0
SERVER_TIMEOUT = 5.0

seq_no = 1
status = 'DISCONNECTED'

configuration = {
    'track_speed': 0.0,
    'mode': 'MANUAL',
}

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

# looks like timeout is needed in order to receive input from the keyboard (e.g. KeyboardInterrupt)
sock.settimeout(TIMEOUT)

def read_data() -> dict:
    return {
        'roll': round(random.gauss(0.0, 1.0), 3),
        'pitch': round(random.gauss(0.0, 1.0), 3),
        'temperature': round(random.gauss(23.0, 2.0), 3),
    }

def send_message(msg_type, data):
    global seq_no
    print(f"Sending message: type: {msg_type}, data: {data} (seq_no: {seq_no})")

    sock.sendto(bytes(json.dumps({
        'seq_no': seq_no,
        'type': msg_type,
        'data': data,
    }), 'ascii'), (SERVER_UDP_IP, SERVER_UDP_PORT))

    seq_no += 1

print(f"Listening at {UDP_PORT}...")

time_at_last_data_send = 0
time_at_last_ack = 0

while True:
    try:
        # if not connected, just keep sending ROBOT_HELLO
        if status != 'CONNECTED':
            send_message('ROBOT_HELLO', {
                'fw_version': '1.2.3'
            })
        elif status == 'CONNECTED':
            if time.time() - time_at_last_ack >= SERVER_TIMEOUT:
                print("SERVER LOST! Oh no!")
                status = 'DISCONNECTED'

            if time.time() - time_at_last_data_send >= UPDATE_INTERVAL:
                send_message('ROBOT_UPDATE', read_data())
                time_at_last_data_send = time.time()

        # RECEIVE DATA

        data, addr = sock.recvfrom(BUFSIZE)
        #print(f"received message [from client {addr}]: {data}")

        message = json.loads(data.decode('ascii'))
        print(f"Received:        {message}")
        time_at_last_ack = time.time()

        if status != 'CONNECTED':
            if message['type'] == 'SERVER_HELLO':
                send_message('ACK', {
                    'seq_no': message['seq_no']
                })
                status = 'CONNECTED'
        else:
            if message['type'] == 'CONFIGURATION':
                print("Wowzie! Got a configuration!")
                configuration = configuration | message['data']

                send_message('ACK', {
                    'seq_no': message['seq_no']
                })

            elif message['type'] == 'ACK':
                #time_at_last_ack = time.time()
                pass

    except IOError as msg:
        time.sleep(POLL_INTERVAL)
        pass  # timed out, try again...
    except KeyboardInterrupt:
        break

# cleanup if needed...
print("Exiting...")
