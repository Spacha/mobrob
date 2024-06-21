from PyQt5.QtCore import Qt, QRectF
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QColor, QPen, QImage, QPainterPath, QTransform, QFont


class AttitudeWidget(QWidget):
    def __init__(self, parent=None, roll=0.0, pitch=0.0):
        super().__init__(parent)
        self.roll = roll
        self.pitch = pitch

        self.font = QFont("Arial", 10)
        self.update_data(roll, pitch)

    def update_data(self, roll: float=None, pitch: float=None) -> None:
        if roll is not None:
            self.roll = roll
        if pitch is not None:
            self.pitch = pitch
        self.repaint()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        painter.fillRect(self.rect(), QColor(180, 180, 180))

        painter.setFont(self.font)
        painter.drawText(QRectF(0, self.height() - 40, self.width(), 20), Qt.AlignCenter,
                         f"Roll: {round(self.roll, 1)} °.")
        painter.drawText(QRectF(0, self.height() - 20, self.width(), 20), Qt.AlignCenter,
                         f"Pitch: {round(self.pitch, 1)} °.")

        # draw the boundaries
        painter.setPen(QColor(75, 75, 75))
        painter.drawRect(0, 0, self.width(), self.height())
