from PyQt5.QtWidgets import QGroupBox, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QSpacerItem, QSizePolicy

class ControlsWidget(QGroupBox):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.setTitle("Robot controls")
        self.column_layout = QHBoxLayout(self)

        self.left_column = QWidget(self)
        self.column_layout.addWidget(self.left_column)
        self.middle_column = QWidget(self)
        self.column_layout.addWidget(self.middle_column)
        spacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)
        self.column_layout.addItem(spacer)
        self.right_column = QWidget(self)
        self.column_layout.addWidget(self.right_column)

        self.label_1 = QLabel(self.left_column, text="Label 1")
        self.label_2 = QLabel(self.middle_column, text="Label 2")
        self.label_3 = QLabel(self.right_column, text="Label 3")

        # Left pane

        left_column_layout = QVBoxLayout(self.left_column)
        left_column_layout.addWidget(self.label_1)

        # Middle pane

        middle_column_layout = QVBoxLayout(self.middle_column)
        middle_column_layout.addWidget(self.label_2)

        # Right pane

        right_column_layout = QVBoxLayout(self.right_column)
        right_column_layout.addWidget(self.label_3)
