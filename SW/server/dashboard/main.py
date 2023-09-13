import sys, socket, select
from math import ceil
from PyQt5.QtCore import Qt, QTimer, QEvent, pyqtSignal
from PyQt5.QtWidgets import (QApplication, QMainWindow, QVBoxLayout, QHBoxLayout, QSplitter,
                             QWidget, QLineEdit, QPushButton, QLabel, QStatusBar, QMessageBox,
                             QDialog, QAction)
from PyQt5.QtGui import QFont, QKeySequence, QTextCursor
from log_widget import LogWidget
from map_widget import MapWidget

SERVER_ADDR = "192.168.1.168"
SERVER_PORT = 3333
SERVER_BUFSIZE = 64
SERVER_TIMEOUT = 1

# TODO: Bug! If the robot is already connected on bootup, the server doesn't
#       notice, even though it receives messages normally.

# Parts:
# - GUI
# - UDP server (receive asynchronously, send synchronously)
# - Key handlers (get held keys if in "held" mode)

# Commands:
# 0000 -> motor control
#   ...
# 0001 -> speed control
#   1111 -> 250
#   1100 -> 220
#   1000 -> 180
#   0110 -> 160
#   0101 -> 150
#   0100 -> 140

keymap = {
    'forward':              'w',
    'backward':             's',
    'turn_left':            'a',
    'turn_right':           'd',

    'left_fw':              't',
    'left_bw':              'g',
    'right_fw':             'y',
    'right_bw':             'h',
}
keymap_groups = {
    'movement_control': ['forward', 'backward', 'turn_left', 'turn_right', 'turn_left_tight', 'turn_right_tight'],
    'track_control':    ['left_fw', 'left_bw', 'right_fw', 'right_bw'],
}

# Consider grabKeyboard: https://doc.qt.io/qt-6/qwidget.html#grabKeyboard
class KeycapDialog(QDialog):
    held_keys_changed = pyqtSignal(set)

    def __init__(self, parent=None):
        super(KeycapDialog, self).__init__(parent)

        self.resize(140, 70)

        # set up the UI
        layout = QVBoxLayout()
        self.label = QLabel('Press a key...')
        layout.addWidget(self.label)
        self.setLayout(layout)

        self.keyPressEvent = self.key_event
        self.keyReleaseEvent = self.key_event

        self.key_whitelist = None
        self.held_keys = set()

    def key_event(self, event):
        # don't care about annoying autorep keys
        if event.isAutoRepeat():
            return

        # only care about whitelisted keys
        if self.key_whitelist is not None and event.text() not in self.key_whitelist:
            return

        if event.type() == QEvent.KeyPress:
            self.held_keys.add(event.text())
        elif event.type() == QEvent.KeyRelease:
            self.held_keys.remove(event.text())

        self.held_keys_changed.emit(self.held_keys)
        self.label.setText(', '.join([k for k in self.held_keys]))

    def whitelist_keys(self, keys):
        self.key_whitelist = keys

class DashboardApplication(QMainWindow):
    def __init__(self):
        super(DashboardApplication, self).__init__()

        self.resize(960, 640)
        self.setWindowTitle("Mobrob server")

        # monospace font
        mono_font = QFont()
        mono_font.setFamilies([u"Consolas"])

        main_layout = QHBoxLayout()
        main_splitter = QSplitter(Qt.Horizontal)

        ###################################################
        # Left pane
        ###################################################

        left_pane_layout = QVBoxLayout()
        left_pane_widget = QWidget()
        left_pane_widget.setLayout(left_pane_layout)

        # log viewer
        self.log_widget = LogWidget(self)
        self.log_widget.verticalHeader().setDefaultSectionSize(100)
        left_pane_layout.addWidget(self.log_widget)
        left_pane_layout.setStretchFactor(self.log_widget, 1)
        left_pane_layout.setContentsMargins(0, 0, 0, 0)

        # message box
        self.messagebox_widget = QWidget()
        left_pane_layout.addWidget(self.messagebox_widget)
        messagebox_layout = QHBoxLayout()
        messagebox_layout.setContentsMargins(0, -1, 0, -1)

        keycap_button = QPushButton("Key capture")
        keycap_button.clicked.connect(self.show_keycap_dialog)
        left_pane_layout.addWidget(keycap_button)

        self.message_field = QLineEdit()
        messagebox_layout.addWidget(self.message_field)
        self.message_field.setFont(mono_font)
        self.message_field.returnPressed.connect(self.handle_message_send)

        send_button = QPushButton("Send")
        send_button.clicked.connect(self.handle_message_send)
        messagebox_layout.addWidget(send_button)

        self.messagebox_widget.setLayout(messagebox_layout)

        main_splitter.addWidget(left_pane_widget)

        ###################################################
        # Right pane
        ###################################################

        # map viewer
        self.map_widget = MapWidget(self)
        main_splitter.addWidget(self.map_widget)

        ###################################################
        # Main layout
        ###################################################

        main_splitter.setSizes([400, 500])
        main_layout.addWidget(main_splitter)

        central_widget = QWidget()
        central_widget.setLayout(main_layout)
        self.setCentralWidget(central_widget)

        # menubar
        menubar = self.menuBar()
        file_menu = menubar.addMenu("File")

        exit_action = QAction("Exit", self)
        exit_action.setShortcut("Ctrl+Q")
        exit_action.triggered.connect(self.close)
        file_menu.addAction(exit_action)

        log_menu = menubar.addMenu("Log")

        save_log_action = QAction("Save Log", self)
        #save_log_action.triggered.connect(self.log_widget.open_save_log_dialog)
        save_log_action.setDisabled(True)
        log_menu.addAction(save_log_action)

        clear_log_action = QAction("Clear Log", self)
        clear_log_action.triggered.connect(self.log_widget.clear_log)
        log_menu.addAction(clear_log_action)

        # statusbar
        self.statusbar = QStatusBar(self)
        self.setStatusBar(self.statusbar)
        self.statusbar.showMessage("Waiting for connection...")

        self.log("Server", "Control", f"Server started at {SERVER_ADDR}:{SERVER_PORT}.")

        self.start_server()

    def log(self, source, log_type, content):
        self.log_widget.add_row(source, log_type, content)

    def handle_message_send(self):
        message = self.message_field.text()
        try:
            self.send_message( int(message, 2).to_bytes(ceil(len(message) / 8), 'little') )
        except ValueError:
            return self.show_error_dialog("The message must be in binary!")

        self.message_field.clear()

    def update_status_bar(self, text):
        self.statusbar.showMessage(text)

    # TODO: Move server stuff to a separate module!
    def start_server(self):
        self.server_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_sock.bind((SERVER_ADDR, SERVER_PORT)) # our own address
        self.server_sock.settimeout(SERVER_TIMEOUT)

        self.client_connected = False
        self.client_addr = None

        # create a QTimer to periodically check for incoming messages
        self.timer = QTimer()
        self.timer.timeout.connect(self.receive_messages)
        self.timer.start(100)  # Check for incoming messages every 100 milliseconds

    # TODO: Move server stuff to a separate module!
    def receive_messages(self):
        # check for incoming messages using select
        ready_sockets, _, _ = select.select([self.server_sock], [], [], 0)

        for socket in ready_sockets:
            if socket == self.server_sock:
                data, addr = self.server_sock.recvfrom(SERVER_BUFSIZE)

                message = data.decode('utf-8')
                print(f'Received message from {addr}: {message}')

                if data == b'Hello Server!':
                    self.client_addr = addr
                    self.client_connected = True
                    self.update_status_bar(f"Client connected: {self.client_addr[0]}:{self.client_addr[1]}")
                    self.log("Client", "Network", f"Client connected: {self.client_addr[0]}:{self.client_addr[1]}")

                self.log("Client", "Data", f"Received: {message}")

    # TODO: Move server stuff to a separate module!
    def send_message(self, message):
        if not self.client_connected:
            return self.show_error_dialog("Cannot send a message before a client is connected!")

        self.server_sock.sendto(bytes(message), self.client_addr)
        self.log("Server", "Data", "Sent: " + str(message))

    def show_keycap_dialog(self):
        # create an instance of the custom dialog
        keycap_dialog = KeycapDialog(self)
        keycap_dialog.whitelist_keys(keymap.values())

        def handle_held_keys_changed(held_keys):
            # slot for handling the held_keys_changes signal
            print("Keys pressed:", held_keys)

            # map keys to command byte
            cmd = 0b0000

            # Control tank movement

            if keymap['forward'] in held_keys:
                if keymap['turn_right'] in held_keys:
                    # drive forward and turn right
                    cmd = 0b0111
                elif keymap['turn_left'] in held_keys:
                    # drive forward and turn left
                    cmd = 0b1101
                else:
                    # drive forward
                    cmd = 0b0101
            elif keymap['backward'] in held_keys:
                if keymap['turn_right'] in held_keys:
                    # reverse and turn right
                    cmd = 0b1011
                elif keymap['turn_left'] in held_keys:
                    # reverse and turn left
                    cmd = 0b1110
                else:
                    # bw
                    cmd = 0b1010
            elif keymap['turn_left'] in held_keys:
                # turn left in place
                cmd = 0b1001
            elif keymap['turn_right'] in held_keys:
                # turn right in place
                cmd = 0b0110

            # Control tracks individually

            # only enable track control if none of the movement keys are not being held
            #if len(set(keymap_groups['movement_control'].values()) & set(held_keys)) == 0:
            if cmd == 0b0000:
                # if the left track isn't asked to move, stop it completely
                if keymap['left_fw'] not in held_keys and keymap['left_bw'] not in held_keys:
                    cmd |= 0b1100
                else:
                    if keymap['left_fw'] in held_keys:
                        cmd |= 0b0100
                    if keymap['left_bw'] in held_keys:
                        cmd |= 0b1000

                # if the right track isn't asked to move, stop it completely
                if keymap['right_fw'] not in held_keys and keymap['right_bw'] not in held_keys:
                    cmd |= 0b0011
                else:
                    if keymap['right_fw'] in held_keys:
                        cmd |= 0b0001
                    if keymap['right_bw'] in held_keys:
                        cmd |= 0b0010

            print(f"Command byte: 0b{cmd:04b}")
            self.send_message( cmd.to_bytes(ceil(1 / 8), 'little') )

        keycap_dialog.held_keys_changed.connect(handle_held_keys_changed)
        keycap_dialog.exec_()

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
