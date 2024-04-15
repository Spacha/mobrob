import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QStatusBar, QLabel, QWidget, QVBoxLayout, QPushButton
from mobrob_server import MobrobServer, ClientMessage

SERVER_VERSION = '0.0.0'

SERVER_ADDR     = "192.168.1.168"
SERVER_PORT     = 3333
SERVER_BUFSIZE  = 64
SERVER_TIMEOUT  = 1

class LogWidget:
    pass


class MapWidget:
    pass

class Connection:
    def __init__(self) -> None:
        self.status = 'NOT_CONNECTED'
        self.seq_no = 0
    
    def handle(self, message: ClientMessage) -> None:
        if self.status == 'NOT_CONNECTED':
            if message.seq_no == 1 and message.type == 'ROBOT_HELLO':
                # TODO: check message.data['fw_version]
                pass
            else:
                pass

    def set_status(self, status: str) -> None:
        self.status = status


class DashboardApplication(QMainWindow):
    def __init__(self) -> None:
        super(DashboardApplication, self).__init__()

        self.server = MobrobServer(SERVER_ADDR, SERVER_PORT)

        self.configuration_status = None
        self.robot_configuration = {
            'track_speed': 666,
            'mode': 'manual',
        }
        self.robot_data = {
            'roll': 0.0,
            'pitch': 0.0,
            'temperature': 0.0
        }

        self.resize(300, 200)
        self.setWindowTitle("Mobrob server")

        # Robot data
        self.data_roll_label = QLabel()
        self.data_pitch_label = QLabel()
        self.data_temp_label = QLabel()

        # Robot configuration form
        self.send_conf_btn = QPushButton("Send configuration")
        self.send_conf_btn.clicked.connect(self.send_robot_configuration)

        # Main layout
        layout = QVBoxLayout()
        layout.addWidget(self.data_roll_label)
        layout.addWidget(self.data_pitch_label)
        layout.addWidget(self.data_temp_label)
        layout.addWidget(self.send_conf_btn)
        layout.addStretch()

        central_widget = QWidget()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

        # Status bar
        self.statusbar = QStatusBar(self)
        self.setStatusBar(self.statusbar)
        self.statusbar.showMessage("Waiting for connection...")

        # Post-init
        # in a separate post-init function?
        self.set_configuration_status('SENT')
        self.update_data_widget()

        # Server stuff

        self.server.start(
            lambda msg: self.receive_message(msg),
            lambda s, os: self.update_server_status(s, os),
        )
    
    def send_robot_configuration(self) -> None:
        if not self.server._status == 'CONNECTED':
            return

        self.set_configuration_status('PENDING')
        self.server.send_message(
            'CONFIGURATION',
            self.robot_configuration,
            lambda: self.set_configuration_status('SENT')
        )

    def set_configuration_status(self, status: str) -> None:
        # status == 'PENDING'   -> disable form
        # status == 'SEND'      -> enable form
        #print(f"[GUI] Configuration status changed to: {status}")
        print('confstat', status)
        self.configuration_status = status
        self.send_conf_btn.setEnabled(status == 'SENT' and self.server._status == 'CONNECTED')

    def update_server_status(self, status: str, old_status: str) -> None:
        #self.statusbar.set_text(f"Connection status: {self.server.status}")
        print(f"[GUI] Server status updated to: {status}")

        if status == 'CONNECTED' and old_status == 'DISCONNECTED':
            self.send_robot_configuration()
            self.statusbar.showMessage("Connected!")
        elif status == 'DISCONNECTED' and old_status == 'CONNECTED':
            self.statusbar.showMessage("Not connected.")
            self.set_configuration_status(self.configuration_status) # HAX
    
    def receive_message(self, message: ClientMessage) -> None:
        print(f"[GUI] Received message: {message}")

        if message.type == 'ROBOT_UPDATE':
            #self.update_robot_data(message.data)
            self.robot_data |= message.data
            self.update_data_widget()
    
    def update_data_widget(self) -> None:
        self.data_roll_label.setText(f"Roll: {self.robot_data['roll']}")
        self.data_pitch_label.setText(f"Pitch: {self.robot_data['pitch']}")
        self.data_temp_label.setText(f"Temperature: {self.robot_data['temperature']}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardApplication()
    window.show()
    sys.exit(app.exec_())
