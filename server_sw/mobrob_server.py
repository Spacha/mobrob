from __future__ import annotations
import socket, select
from typing import Optional, Callable
from dataclasses import dataclass, field
from PyQt5.QtCore import QTimer

# TODO: Consider using truly asynchronous UDP server:
# https://docs.python.org/3/library/socketserver.html#asynchronous-mixins

DEFAULT_OPTIONS = {
    # How long the server is allowed to wait for operations to complete (s)
    'timeout':          1.0,

    # How often to check the incoming messages (s)
    'poll_interval':    0.1,

    # The size of the receive buffer (B)
    'buffer_size':      64
}

@dataclass
class Message:
    """ . """
    sender: str
    seq_no: int
    msg_type: str
    data: dict

@dataclass
class ClientMessage(Message):
    sender: str = field(default='client', init=False)

    @staticmethod
    def from_bytes(message: bytes) -> ClientMessage:
        message_decoded = message.decode('utf-8')
        return ClientMessage(666, 'debug', message_decoded)

@dataclass
class ServerMessage(Message):
    sender: str = field(default='server', init=False)

    @staticmethod
    def to_bytes() -> ServerMessage:
        pass

class Protocol:
    def __init__(self) -> None:
        self.state = 'NOT_CONNECTED'
        self.seq_no = 0


class MobrobServer:
    def __init__(self, addr: str, port: int, options: Optional[dict]=None) -> None:
        self.addr = addr
        self.port = port
        self.options = DEFAULT_OPTIONS | (options or {})

        self.current_seq_no = 0
        self.current_state = 'NOT_CONNECTED'

    def start(self, message_callback: Callable[[Message], None]) -> bool:
        """ . """
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.bind((self.addr, self.port))
        self.sock.settimeout(self.options['timeout'])

        self.client_connected = False
        self.client_addr = None

        # register callback for receiving client messages
        self.message_callback = message_callback

        # create a QTimer to periodically check for incoming messages
        self.timer = QTimer()
        self.timer.timeout.connect(self._check_messages)
        self.timer.start(int(self.options['poll_interval'] * 1000))

    def stop(self) -> bool:
        pass

    def _check_messages(self) -> None:
        # check for incoming messages using select
        ready_sockets, _, _ = select.select([self.sock], [], [], 0)

        for socket in ready_sockets:
            # only care about our own socket
            if socket != self.sock:
                continue

            data, addr = self.sock.recvfrom(self.options['buffer_size'])

            #message = data.decode('utf-8')
            #print(f'Received message from {addr}: {message}')
            message = ClientMessage.from_bytes(data)
            self.message_callback(message)
