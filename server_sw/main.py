import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QStatusBar, QLabel, QWidget, QHBoxLayout, QVBoxLayout, QGridLayout, QPushButton, QAction, QSpacerItem, QSizePolicy
from PyQt5.QtGui import QFont
from mobrob_server import MobrobServer, ClientMessage
from log_widget import LogWidget
from obstacle_widget import ObstacleWidget
from controls_widget import ControlsWidget
from measurements_widget import MeasurementsWidget
from attitude_widget import AttitudeWidget

SERVER_VERSION = '0.0.0'

SERVER_ADDR     = "192.168.1.168"
SERVER_PORT     = 3333
SERVER_BUFSIZE  = 64
SERVER_TIMEOUT  = 1

# class Connection:
#     def __init__(self) -> None:
#         self.status = 'NOT_CONNECTED'
#         self.seq_no = 0
    
#     def handle(self, message: ClientMessage) -> None:
#         if self.status == 'NOT_CONNECTED':
#             if message.seq_no == 1 and message.type == 'ROBOT_HELLO':
#                 # TODO: check message.data['fw_version]
#                 pass
#             else:
#                 pass

#     def set_status(self, status: str) -> None:
#         self.status = status


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
            'temperature': 0.0,
            'travel_dist': 0.0,
        }

        ###################################################
        # Main layout
        ###################################################

        self.resize(900, 600)
        self.setWindowTitle("Mobrob server")

        mono_font = QFont()
        mono_font.setFamilies([u"Consolas"])

        main_grid = QGridLayout()

        self.log_widget = LogWidget(self)
        self.obstacle_widget = ObstacleWidget(self)
        self.attitude_widget = AttitudeWidget(self, self.robot_data['roll'], self.robot_data['pitch'])
        
        # Bottom pane
        self.bottom_pane = QWidget(self)
        self.bottom_pane.setFixedHeight(150)
        bottom_pane_layout = QHBoxLayout(self.bottom_pane)

        self.controls_widget = ControlsWidget(self.bottom_pane)
        bottom_pane_layout.addWidget(self.controls_widget)
        self.measurements_widget = MeasurementsWidget(self.bottom_pane, self.robot_data['temperature'], 0.0)
        #self.measurements_widget.setFixedWidth(100)
        bottom_pane_layout.addWidget(self.measurements_widget)

        # Robot data
        # self.data_roll_label = QLabel()
        # self.data_pitch_label = QLabel()
        # self.data_temp_label = QLabel()

        # Robot configuration form
        self.send_conf_btn = QPushButton("Send configuration")
        self.send_conf_btn.clicked.connect(self.send_robot_configuration)

        # Add widgets to the grid layout
        main_grid.addWidget(self.log_widget, 0, 0)
        main_grid.addWidget(self.obstacle_widget, 0, 1)
        main_grid.addWidget(self.bottom_pane, 1, 0)
        main_grid.addWidget(self.attitude_widget, 1, 1)

        central_widget = QWidget()
        central_widget.setLayout(main_grid)
        self.setCentralWidget(central_widget)

        ###################################################
        # Menubar
        ###################################################

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

        ###################################################
        # Status bar
        ###################################################

        self.statusbar = QStatusBar(self)
        self.setStatusBar(self.statusbar)
        self.statusbar.showMessage("Waiting for connection...")

        ###################################################
        # Post-init
        ###################################################

        # FIXME: Temp
        self.log_widget.add_row("TEST", "TEST_TYPE", "This is sample content")
        self.log_widget.add_row("TEST", "TEST_TYPE", "This is also some sample content")

        # in a separate post-init function?
        self.set_configuration_status('SENT')
        #self.update_robot_data()

        # Server stuff

        self.server.start(
            lambda msg: self.receive_message(msg),
            lambda s, os: self.update_server_status(s, os),
        )
    
    def update_robot_data(self, data_dict: dict) -> None:
        self.robot_data |= data_dict

        # TODO: Travel dist update here if necessary

        # update widgets if necessary
        if any(k in data_dict for k in ['roll', 'pitch']):
            self.attitude_widget.update_data(self.robot_data['pitch'], self.robot_data['roll'])
        if any(k in data_dict for k in ['temperature', 'travel_dist']):
            self.measurements_widget.update_data(self.robot_data['temperature'], self.robot_data['travel_dist'])
        if any(k in data_dict for k in ['object_dist']):
            self.obstacle_widget.update_data(self.robot_data['object_dist'])

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
            #self.robot_data |= message.data
            self.update_robot_data(message.data)
            self.log_widget.add_row("Robot", "Robot Update", message.data)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardApplication()
    window.show()
    sys.exit(app.exec_())
