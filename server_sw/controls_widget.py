from PyQt5.QtWidgets import QGroupBox, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QSpacerItem, QSizePolicy, QFormLayout, QButtonGroup, QRadioButton

class ControlsWidget(QGroupBox):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setTitle("Robot controls")
        self.column_layout = QHBoxLayout(self)

        self.left_column = QWidget(self)
        self.column_layout.addWidget(self.left_column)
        #self.middle_column = QWidget(self)
        #self.column_layout.addWidget(self.middle_column)
        spacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.column_layout.addItem(spacer)
        self.right_column = QWidget(self)
        self.column_layout.addWidget(self.right_column)

        #self.label_1 = QLabel(self.left_column, text="Label 1")
        #self.label_2 = QLabel(self.middle_column, text="Label 2")
        self.label_3 = QLabel(self.right_column, text="Label 3")

        # Left pane

        left_column_layout = QFormLayout(self.left_column)

        mode_label = QLabel("Mode:")

        mode_radio_group = QWidget(self.left_column)
        test1 = QRadioButton("Test 1", mode_radio_group)
        test2 = QRadioButton("Test 2", mode_radio_group)
        mode_radio_group_layout = QHBoxLayout(mode_radio_group)
        mode_radio_group_layout.addWidget(test1)
        mode_radio_group_layout.addWidget(test2)
        mode_radio_group_layout.setContentsMargins(0, 0, 0, 0)

        left_column_layout.setWidget(0, QFormLayout.LabelRole, mode_label)
        left_column_layout.setWidget(0, QFormLayout.FieldRole, mode_radio_group)

        #left_column_layout = QVBoxLayout(self.left_column)
        # left_column_layout = QFormLayout(self.left_column)
        # left_column_layout.addWidget(self.label_1)
        # radio_layout = QButtonGroup()
        # mode_manual_radio = QRadioButton("Manual", left)
        # mode_explore_radio = QRadioButton("Explore", mode_group)
        # radio_layout.addWidget(mode_manual_radio)
        # radio_layout.addWidget(mode_explore_radio)

        # self.left_column_layout.setWidget(0, QFormLayout.LabelRole, self.mode_label)
        # self.left_column_layout.setWidget(0, QFormLayout.FieldRole, self.mode_)

        # Middle pane

        # middle_column_layout = QVBoxLayout(self.middle_column)
        # middle_column_layout.addWidget(self.label_2)

        # Right pane

        right_column_layout = QVBoxLayout(self.right_column)
        right_column_layout.addWidget(self.label_3)
