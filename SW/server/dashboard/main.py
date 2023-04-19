import sys, socket, select
from math import ceil
from PyQt5.QtCore import Qt, QTimer
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QHBoxLayout, QWidget, QLineEdit, QPushButton, QLabel, QTextBrowser, QStatusBar, QMessageBox
from PyQt5.QtGui import QFont

SERVER_ADDR = "192.168.1.168"
SERVER_PORT = 3333
SERVER_BUFSIZE = 64
SERVER_TIMEOUT = 1

class DashboardApplication(QMainWindow):
    def __init__(self):
        super(DashboardApplication, self).__init__()

        # Set initial size
        self.resize(640, 430)

        self.setWindowTitle("Mobrob server")

        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout()

        # monospace font
        mono_font = QFont()
        mono_font.setFamilies([u"Consolas"])

        # message viewer
        self.message_viewer = QTextBrowser()
        main_layout.addWidget(self.message_viewer)
        self.message_viewer.setFont(mono_font)

        # message box
        self.messagebox_widget = QWidget()
        main_layout.addWidget(self.messagebox_widget)
        messagebox_layout = QHBoxLayout()
        messagebox_layout.setContentsMargins(0, -1, 0, -1)

        self.message_field = QLineEdit()
        messagebox_layout.addWidget(self.message_field)
        self.message_field.setFont(mono_font)
        self.message_field.returnPressed.connect(self.send_message)

        send_button = QPushButton("Send")
        send_button.clicked.connect(self.send_message)
        messagebox_layout.addWidget(send_button)
        self.messagebox_widget.setLayout(messagebox_layout)

        central_widget.setLayout(main_layout)

        # statusbar
        self.statusbar = QStatusBar(self)
        self.setStatusBar(self.statusbar)
        self.statusbar.showMessage("Waiting for connection...")

        self.messages = []

        self.start_server()

    def send_message(self):
        # Get the message from the text edit
        message = self.message_field.text()

        if not self.client_connected:
            self.show_error_dialog("Cannot send a message before a client is connected!")
            return

        # binary mode
        self.server_sock.sendto(int(message, 2).to_bytes(ceil(len(message) / 8), 'little'), self.client_addr)

        # Append sent message to chat messages list
        self.messages.append("Sent: " + message)

        # Update text in the text browser
        self.update_message_viewer()

        # Clear the text edit
        self.message_field.clear()

    def update_message_viewer(self):
        # Clear the text browser
        self.message_viewer.clear()

        # Display all chat messages in the text browser
        for message in self.messages:
            self.message_viewer.append(message)

    def update_status_bar(self, text):
        # Update the text of the status bar
        self.statusbar.showMessage(text)

    def start_server(self):
        self.server_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_sock.bind((SERVER_ADDR, SERVER_PORT)) # our own address
        self.server_sock.settimeout(SERVER_TIMEOUT)

        self.client_connected = False
        self.client_addr = None

        # Create a QTimer to periodically check for incoming messages
        self.timer = QTimer()
        self.timer.timeout.connect(self.receive_messages)
        self.timer.start(100)  # Check for incoming messages every 100 milliseconds

    def receive_messages(self):
        # Check for incoming messages using select
        ready_sockets, _, _ = select.select([self.server_sock], [], [], 0)

        for socket in ready_sockets:
            if socket == self.server_sock:
                data, addr = self.server_sock.recvfrom(SERVER_BUFSIZE)

                message = data.decode('utf-8')
                print(f'Received message from {addr}: {message}')

                self.messages.append(f"Received message from {addr}: {message}")
                self.update_message_viewer()

                if not self.client_connected and data == b'Hello Server!':
                    self.client_addr = addr
                    self.client_connected = True
                    self.update_status_bar(f"Client connected: {self.client_addr[0]}:{self.client_addr[1]}")

    def show_error_dialog(self, message):
        error_dialog = QMessageBox()
        error_dialog.setIcon(QMessageBox.Warning)
        error_dialog.setWindowTitle("Error")
        error_dialog.setText("Error!")
        error_dialog.setInformativeText(message)
        error_dialog.setStandardButtons(QMessageBox.Ok)
        error_dialog.exec_()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardApplication()
    window.show()
    sys.exit(app.exec_())
