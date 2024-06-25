import socket
import json

# Replace with the server's IP address and port
SERVER_IP = "192.168.1.168"
SERVER_PORT = 3333

def start_udp_server(ip, port):
    # Create a UDP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((ip, port))

    print(f"Server listening on {ip}:{port}")

    buffer = bytearray()  # Use a bytearray to accumulate incoming bytes

    while True:
        # Receive data from the client
        data, addr = sock.recvfrom(1)  # Read one byte at a time
        buffer.extend(data)

        # Check for newline character
        if b'\n' in buffer:
            # Split the buffer on newline to handle multiple lines
            lines = buffer.split(b'\n')

            for line in lines[:-1]:  # Process all complete lines
                process_data(line)

            # Keep the remaining part in the buffer (incomplete line)
            buffer = lines[-1]

def process_data(data):
    try:
        # Decode the data to a string
        data_str = data.decode('utf-8')
        
        # Parse the JSON data
        json_data = json.loads(data_str)
        print("Parsed JSON data:", json_data)
        
        # Process the JSON data as needed
        process_json_data(json_data)
    except json.JSONDecodeError:
        print("Received data is not valid JSON")

def process_json_data(json_data):
    # Process the JSON data as needed
    print("Processing JSON data:", json_data)
    msg_type = json_data.get("msg_type", "")
    fw_version = json_data.get("data", {}).get("fw_version", "")

    print(f"Message Type: {msg_type}")
    print(f"Firmware Version: {fw_version}")

if __name__ == "__main__":
    start_udp_server(SERVER_IP, SERVER_PORT)
