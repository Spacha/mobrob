from __future__ import annotations
import socket, select, json, time
from typing import Optional, Callable
from dataclasses import dataclass, field
from PyQt5.QtCore import QTimer
from __init__ import __version__ # FIXME: not like this...

""" Protocol

direction  sno  msg_type            data
--------------------------------------------------------------------

RECEIVE     1   robot hello         fw_version (str)
SEND        2   server hello        server_version (str)
RECEIVE     3   ack                 seq_no (int)

SEND        4   configuration       track_speed (int)
                                    mode (str)
RECEIVE     5   ack                 seq_no (int)

"""

# TODO: Consider using truly asynchronous UDP server:
# https://docs.python.org/3/library/socketserver.html#asynchronous-mixins

DEFAULT_OPTIONS = {
    # How long the server is allowed to wait for operations to complete (s)
    'timeout':              1.0,

    # ???
    'connection_timeout':   5.0,

    # How often to check the incoming messages (s)
    'poll_interval':        0.1,

    # The size of the receive buffer (B)
    'buffer_size':          1024
}

@dataclass
class Message:
    """ . """
    sender: str
    seq_no: int
    type: str
    data: dict

@dataclass
class ClientMessage(Message):
    sender: str = field(default='client', init=False)

    @staticmethod
    def from_bytes(message: bytes) -> ClientMessage:
        # TODO: Is .decode even necessary? json.loads can load bytes as well
        message_decoded = json.loads(message.decode('ascii'))
        return ClientMessage(**message_decoded)

@dataclass
class ServerMessage(Message):
    sender: str = field(default='server', init=False)

    def to_bytes(self) -> bytes:
        return bytes(json.dumps({
            'seq_no': self.seq_no,
            'type': self.type,
            'data': self.data,
        }), encoding='ascii')

class Protocol:
    def __init__(self) -> None:
        self.state = 'NOT_CONNECTED'
        self.seq_no = 0


class MobrobServer:
    def __init__(self, addr: str, port: int, options: Optional[dict]=None) -> None:
        self.addr = addr
        self.port = port
        self.options = DEFAULT_OPTIONS | (options or {})

        self.seq_no = 0
        #self.last_message_received = 0
        self.client_addr = None
        self._status = 'DISCONNECTED'

        self.message_callback = None
        self.status_update_callback = None
        self.receive_timer = None
        self.connection_alive_timer = None

        self._ack_callbacks = {}

    def start(self, message_callback: Callable[[Message], None], status_update_callback: Callable[[str, str], None]) -> bool:
        """ . """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.addr, self.port))
        self.sock.settimeout(self.options['timeout'])

        # register callbacks
        self.message_callback = message_callback
        self.status_update_callback = status_update_callback

        #self.last_message_received = time.time()
        # create a QTimer to periodically check for connection
        #self.check_connection_timer.timeout.connect(self._check_messages)
        #self.check_connection_timer.start(int(self.options['poll_interval'] * 1000))
        self.connection_alive_timer = QTimer()
        self.connection_alive_timer.timeout.connect(self.disconnect)
        self.connection_alive_timer.setInterval(int(self.options['connection_timeout'] * 1000))

        # create a QTimer to periodically check for incoming messages
        self.receive_timer = QTimer()
        self.receive_timer.timeout.connect(self._check_messages)
        self.receive_timer.start(int(self.options['poll_interval'] * 1000))

    def stop(self) -> bool:
        self.disconnect()

        self.receive_timer.stop()
        self.receive_timer = None

        self.sock.shutdown(socket.SHUT_RDWR)
        self.sock.close()

    def next_seq_no(self) -> int:
        self.seq_no += 1
        return self.seq_no

    def send_message(self, msg_type: str, data: dict, callback: Optional[Callable[[], None]]=None) -> None:
        self._send_message(ServerMessage(0, msg_type, data), callback)

    def _check_messages(self) -> None:
        # check for incoming messages using select
        ready_sockets, _, _ = select.select([self.sock], [], [], 0)

        for socket in ready_sockets:
            # only care about our own socket
            if socket != self.sock:
                continue

            try:
                data, addr = self.sock.recvfrom(self.options['buffer_size'])
                message = ClientMessage.from_bytes(data)
            except ConnectionResetError:
                if self._status == 'CONNECTED':
                    self.disconnect()
                    continue

            # only the connected client has the right for communication
            if self._status == 'CONNECTED' and addr != self.client_addr:
                continue

            print(f"[SRV] Raw: Received message: {message}")

            #self.last_message_received = time.time()
            if self._status == 'CONNECTED':
                print('Remaining time:', self.connection_alive_timer.remainingTime())
                # reset timer
                self.connection_alive_timer.start()

            # if the message is ACK, check if there are any callback waiting
            # if so, call them and remove from the list
            if message.type == 'ACK':
                self._call_ack_callback(message.data['seq_no'])

            # if already connected, forward the message to the callback
            elif self._status == 'CONNECTED':
                self.connection_alive_timer.start()

                if message.type == 'ROBOT_UPDATE':
                    self.send_message('ACK', {'seq_no': message.seq_no})

                self.message_callback(message)

            # if not connected, only allow ROBOT_HELLO message
            if message.type == 'ROBOT_HELLO':
                if self._status == 'CONNECTED':
                    self.disconnect()

                # TODO: check fw_version
                self.client_addr = addr
                self.send_message('SERVER_HELLO', {
                    'server_version': __version__
                }, lambda: self._robot_connected())
    
    def _send_message(self, message: ServerMessage, callback: Optional[Callable[[], None]]=None) -> None:
        if not self.client_addr:
            raise Exception("No known client address!")

        message.seq_no = self.next_seq_no()
        if callback:
            self._ack_callbacks[message.seq_no] = callback
        self.sock.sendto(message.to_bytes(), self.client_addr)
    
    def disconnect(self) -> None:
        print("CONNECTION LOST!")
        self.connection_alive_timer.stop()
        self._update_status('DISCONNECTED')

    def _robot_connected(self) -> None:
        """ Called, when ACK is received from robot during connection. """
        print("Good! Robot connected!")
        self._update_status('CONNECTED')
    
    def _call_ack_callback(self, seq_no: int) -> bool:
        """ Returns True if a callback was called. """
        
        # if there is a callback, call it and delete it
        if seq_no in self._ack_callbacks:
            self._ack_callbacks[seq_no]()
            del self._ack_callbacks[seq_no]

            return True
        return False

    # @property
    # def status(self) -> None:
    #     return self._status
    
    #@status.setter
    #def status(self, status: str) -> None:
    def _update_status(self, status: str) -> None:
        """ Called, when the server status changes. """
        old_status = self._status
        self._status = status
        self.status_update_callback(status, old_status)
