from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QGroupBox, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QSpacerItem, QSizePolicy, QFormLayout, QButtonGroup, QRadioButton, QSlider

class ControlsWidget(QGroupBox):
    def __init__(self, send_configuration, get_configuration, parent=None, mode=None, speed=None):
        super().__init__(parent)
        self.unsent_changes = False
        self.send_configuration = send_configuration
        self.get_configuration = get_configuration

        self.setTitle("Robot controls")
        self.column_layout = QHBoxLayout(self)

        self.left_column = QWidget(self)
        self.column_layout.addWidget(self.left_column)
        main_spacer = QSpacerItem(5, 0, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.column_layout.addItem(main_spacer)
        self.right_column = QWidget(self)
        self.column_layout.addWidget(self.right_column)

        # Left pane

        # prefer expanding until 300px
        left_column_size_policy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        left_column_size_policy.setHorizontalStretch(1)
        self.left_column.setSizePolicy(left_column_size_policy)
        self.left_column.setMaximumWidth(300)

        mode_label = QLabel("Mode:")

        self.mode_radio_group = QWidget(self.left_column)
        self.manual_radio = QRadioButton("Manual", self.mode_radio_group)
        self.explore_radio = QRadioButton("Explore", self.mode_radio_group)
        mode_spacer = QSpacerItem(0, 0, QSizePolicy.Expanding, QSizePolicy.Minimum)
        mode_radio_group_layout = QHBoxLayout(self.mode_radio_group)
        mode_radio_group_layout.addWidget(self.manual_radio)
        mode_radio_group_layout.addWidget(self.explore_radio)
        mode_radio_group_layout.addItem(mode_spacer)
        mode_radio_group_layout.setContentsMargins(0, 0, 0, 0)

        left_column_layout = QFormLayout(self.left_column)
        left_column_layout.setWidget(0, QFormLayout.LabelRole, mode_label)
        left_column_layout.setWidget(0, QFormLayout.FieldRole, self.mode_radio_group)

        speed_label = QLabel("Speed:")

        speed_slider_group = QWidget(self.left_column)
        self.speed_slider = QSlider(Qt.Horizontal, speed_slider_group)
        self.speed_slider.setMinimum(1)
        self.speed_slider.setMaximum(20)
        self.speed_slider.setTickInterval(1)
        self.speed_value = QLabel(speed_slider_group)
        speed_slider_group_layout = QHBoxLayout(speed_slider_group)
        speed_slider_group_layout.addWidget(self.speed_slider)
        speed_slider_group_layout.addWidget(self.speed_value)
        speed_slider_group_layout.setContentsMargins(0, 0, 0, 0)

        left_column_layout.setWidget(1, QFormLayout.LabelRole, speed_label)
        left_column_layout.setWidget(1, QFormLayout.FieldRole, speed_slider_group)

        # Right pane

        button_size_policy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)

        self.reset_button = QPushButton(self.right_column)
        self.reset_button.setText("Reset")
        self.reset_button.setSizePolicy(button_size_policy)
        self.reset_button.setMinimumWidth(100)
        self.send_button = QPushButton(self.right_column)
        self.send_button.setText("Send to robot")
        self.send_button.setSizePolicy(button_size_policy)
        self.send_button.setMinimumWidth(100)

        right_column_layout = QVBoxLayout(self.right_column)
        right_column_layout.addWidget(self.reset_button)
        right_column_layout.addWidget(self.send_button)

        # connect form events
        self.speed_slider.valueChanged.connect(lambda: self.update_data(speed=self.speed_slider.value() / 20))
        self.manual_radio.clicked.connect(lambda: self.update_data(mode="MANUAL"))
        self.explore_radio.clicked.connect(lambda: self.update_data(mode="EXPLORE"))
        self.send_button.clicked.connect(self.send_changes)
        self.reset_button.clicked.connect(self.reset_changes)

        self.update_data(mode, speed, no_changes=True)
        self.set_enabled(False)

    def update_data(self, mode: str=None, speed: float=None, no_changes: bool=False) -> None:
        self.unsent_changes = False
        if mode is not None:
            self.mode = mode
            if self.mode == 0:
                self.manual_radio.setChecked(True)
            elif self.mode == 1:
                self.explore_radio.setChecked(True)
            self.unsent_changes = not no_changes
        if speed is not None:
            self.speed = speed
            self.speed_slider.setValue(int(self.speed * 20))
            self.speed_value.setText(f"{self.speed} m/s")
            self.unsent_changes = not no_changes

        self.reset_button.setEnabled(self.unsent_changes)
        self.send_button.setEnabled(self.unsent_changes)
    
    def set_enabled(self, is_enabled: bool=True) -> None:
        self.mode_radio_group.setEnabled(is_enabled)
        self.speed_slider.setEnabled(is_enabled)
        self.reset_button.setEnabled(is_enabled and self.unsent_changes)
        self.send_button.setEnabled(is_enabled and self.unsent_changes)

    def send_changes(self) -> None:
        print("TODO: Send configuration.")
        #self.unsent_changes = False
        self.send_configuration(self.mode, self.speed)
        self.update_data(no_changes=True)
    
    def reset_changes(self) -> None:
        print("TODO: Reset configuration.")
        configuration = self.get_configuration()
        self.update_data(
            speed=configuration["speed"],
            mode=configuration["mode"],
            no_changes=True
        )
        #self.unsent_changes = False