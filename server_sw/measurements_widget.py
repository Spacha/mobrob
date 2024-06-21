from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QGroupBox, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QSpacerItem, QSizePolicy, QFormLayout

class MeasurementsWidget(QGroupBox):
    def __init__(self, parent=None, temperature=0.0, travel_dist=0.0):
        super().__init__(parent)

        self.setTitle("Measurements")
        self.form_layout = QFormLayout(self)
        self.setMinimumWidth(200)

        self.temp_label = QLabel(self, text="Temperature:")
        self.dist_label = QLabel(self, text="Distance traveled:")
        self.temp_value = QLabel(self)
        self.dist_value = QLabel(self)
        self.update_data(temperature, travel_dist)

        self.form_layout.setWidget(0, QFormLayout.LabelRole, self.temp_label)
        self.form_layout.setWidget(0, QFormLayout.FieldRole, self.temp_value)

        self.form_layout.setWidget(1, QFormLayout.LabelRole, self.dist_label)
        self.form_layout.setWidget(1, QFormLayout.FieldRole, self.dist_value)

    def update_data(self, temperature: float=None, travel_dist: float=None) -> None:
        if temperature is not None:
            self.temperature = temperature
            self.temp_value.setText(f"{round(self.temperature, 1)} °C")
        if travel_dist is not None:
            self.travel_dist = travel_dist
            self.dist_value.setText(f"{self.travel_dist} m")
