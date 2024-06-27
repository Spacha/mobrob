import sys
from math import ceil
from enum import IntEnum
from PyQt5.QtCore import pyqtSignal, QEvent
from PyQt5.QtWidgets import QApplication, QMainWindow, QStatusBar, QLabel, QWidget, QHBoxLayout, QVBoxLayout, QGridLayout, QAction, QDialog
from PyQt5.QtGui import QFont
from mobrob_server import MobrobServer, ClientMessage
from log_widget import LogWidget
from obstacle_widget import ObstacleWidget
from controls_widget import ControlsWidget
from measurements_widget import MeasurementsWidget
from attitude_widget import AttitudeWidget

SERVER_VERSION = '1.0.0'

SERVER_ADDR     = "192.168.1.168"
SERVER_PORT     = 3333
SERVER_BUFSIZE  = 64
SERVER_TIMEOUT  = 1

class Mode(IntEnum):
    MANUAL  = 0
    EXPLORE = 1

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
    def __init__(self) -> None:
        super(DashboardApplication, self).__init__()

        self.server = MobrobServer(SERVER_ADDR, SERVER_PORT)

        self.configuration_status = None
        self.robot_configuration = {
            'mode': Mode.MANUAL,
            'speed': 0.6,
        }
        self.robot_data = {
            'roll': 0.0,
            'pitch': 0.0,
            'temperature': 0.0,
            'travel_dist': 0.0,
            'obstacle_dist': 999.9,
        }

        ###################################################
        # Main layout
        ###################################################

        self.resize(900, 600)
        self.setWindowTitle(f"Mobile Robot Dashboard v.{SERVER_VERSION}")

        mono_font = QFont()
        mono_font.setFamilies([u"Consolas"])

        main_grid = QGridLayout()

        self.log_widget = LogWidget(self)
        self.obstacle_widget = ObstacleWidget(self, self.robot_data['obstacle_dist'], 0.0, 0.0)
        self.attitude_widget = AttitudeWidget(self, self.robot_data['roll'], self.robot_data['pitch'])
        
        # Bottom pane
        self.bottom_pane = QWidget(self)
        self.bottom_pane.setFixedHeight(150)
        self.bottom_pane.setContentsMargins(0, 0, 0, 0)
        bottom_pane_layout = QHBoxLayout(self.bottom_pane)

        self.controls_widget = ControlsWidget(
            self.send_robot_configuration,
            lambda: self.robot_configuration,
            self.bottom_pane,
            self.robot_configuration["mode"],
            self.robot_configuration["speed"]
        )
        bottom_pane_layout.addWidget(self.controls_widget)
        self.measurements_widget = MeasurementsWidget(self.bottom_pane, self.robot_data['temperature'], 0.0)
        #self.measurements_widget.setFixedWidth(100)
        bottom_pane_layout.addWidget(self.measurements_widget)

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

        robot_menu = menubar.addMenu("Robot")

        control_robot_action = QAction("Control", self)
        control_robot_action.triggered.connect(self.show_keycap_dialog)
        robot_menu.addAction(control_robot_action)

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
        if any(k in data_dict for k in ['pitch', 'roll']):
            self.attitude_widget.update_data(self.robot_data['pitch'], self.robot_data['roll'])
        if any(k in data_dict for k in ['temperature', 'travel_dist']):
            self.measurements_widget.update_data(self.robot_data['temperature'], self.robot_data['travel_dist'])
        if any(k in data_dict for k in ['obstacle_dist']):
            self.obstacle_widget.update_data(self.robot_data['obstacle_dist'])

    def send_robot_configuration(self, mode=None, speed=None) -> None:
        if not self.server._status == 'CONNECTED':
            return

        configuration = self.robot_configuration
        if mode is not None:
            configuration["mode"] = Mode.EXPLORE if mode == 'EXPLORE' else Mode.MANUAL
        if speed is not None:
            configuration["speed"] = speed

        self.set_configuration_status('PENDING')
        self.server.send_message(
            'CONFIGURATION',
            configuration,
            lambda: self.set_configuration_status('SENT', configuration)
        )

    def set_configuration_status(self, status: str, new_configuration: dict=None) -> None:
        # status == 'PENDING'   -> disable form
        # status == 'SEND'      -> enable form
        #print(f"[GUI] Configuration status changed to: {status}")
        #print('confstat', status)
        self.configuration_status = status
        #self.send_conf_btn.setEnabled(status == 'SENT' and self.server._status == 'CONNECTED')
        self.controls_widget.set_enabled(status == 'SENT' and self.server._status == 'CONNECTED')

        if new_configuration:
            self.robot_configuration |= new_configuration
            self.controls_widget.update_data(**self.robot_configuration, no_changes=True)

    def update_server_status(self, status: str, old_status: str) -> None:
        #self.statusbar.set_text(f"Connection status: {self.server.status}")
        print(f"[GUI] Server status updated to: {status}")

        if status == 'CONNECTED' and old_status == 'DISCONNECTED':
            self.send_robot_configuration()
            self.statusbar.showMessage("Connected!")
        elif status == 'DISCONNECTED' and old_status == 'CONNECTED':
            self.statusbar.showMessage("Waiting for connection...")
            self.set_configuration_status(self.configuration_status) # HAX

    def receive_message(self, message: ClientMessage) -> None:
        print(f"[GUI] Received message: {message}")

        if message.type == 'ROBOT_UPDATE':
            #self.update_robot_data(message.data)
            #self.robot_data |= message.data
            self.update_robot_data(message.data)
            self.log_widget.add_row("Robot", "Robot Update", message.data)
    
    def drive_robot(self, left_track_dir: float=None, right_track_dir: float=None):
        self.obstacle_widget.update_data(left_track_dir=left_track_dir, right_track_dir=right_track_dir)
        self.server.send_message(
            'CONTROL',
            {"left_track": left_track_dir, "right_track": right_track_dir}
        )

    def show_keycap_dialog(self):
        # create an instance of the custom dialog
        keycap_dialog = KeycapDialog(self)
        keycap_dialog.whitelist_keys(keymap.values())

        def handle_held_keys_changed(held_keys):
            if self.robot_configuration["mode"] != Mode.MANUAL:
                return

            # slot for handling the held_keys_changes signal
            print("Keys pressed:", held_keys)

            left_track = 0
            right_track = 0

            # Control tank movement

            if keymap['forward'] in held_keys:
                if keymap['turn_right'] in held_keys:
                    # drive forward and turn right
                    left_track, right_track = 1, 0
                elif keymap['turn_left'] in held_keys:
                    # drive forward and turn left
                    left_track, right_track = 0, 1
                else:
                    # drive forward
                    left_track, right_track = 1, 1
            elif keymap['backward'] in held_keys:
                if keymap['turn_right'] in held_keys:
                    # reverse and turn right
                    left_track, right_track = 0, -1
                elif keymap['turn_left'] in held_keys:
                    # reverse and turn left
                    left_track, right_track = -1, 0
                else:
                    # drive backward
                    left_track, right_track = -1, -1
            elif keymap['turn_left'] in held_keys:
                # turn left in place
                left_track, right_track = -1, 1
            elif keymap['turn_right'] in held_keys:
                # turn right in place
                left_track, right_track = 1, -1

            self.drive_robot(left_track, right_track)

        keycap_dialog.held_keys_changed.connect(handle_held_keys_changed)
        keycap_dialog.exec_()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardApplication()
    window.show()
    sys.exit(app.exec_())
