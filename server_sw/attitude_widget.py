from PyQt5.QtCore import Qt, QRectF, QPointF
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QColor, QImage, QFont, QTransform

class AttitudeWidget(QWidget):
    def __init__(self, parent=None, pitch=0.0, roll=0.0):
        super().__init__(parent)
        self.roll = roll
        self.pitch = pitch

        # safe limits for showing warnings
        self.roll_limits = (-30, 30)
        self.pitch_limits = (-40, 40)

        self.font = QFont("Arial", 12)
        self.large_font = QFont("Arial", 14, QFont.Bold)
        self.image_rear_normal = QImage("resources/view_rear.png")
        self.image_left_normal = QImage("resources/view_left.png")
        self.image_rear_warn = QImage("resources/view_rear_warn.png")
        self.image_left_warn = QImage("resources/view_left_warn.png")

        self.update_data(pitch, roll)

    def update_data(self, pitch: float=None, roll: float=None) -> None:
        if pitch is not None:
            self.pitch = pitch
        if roll is not None:
            self.roll = roll
        self.repaint()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        # select images based on the safety limits
        self.image_rear = self.image_rear_warn if self.roll < self.roll_limits[0] or self.roll > self.roll_limits[1] else self.image_rear_normal
        self.image_left = self.image_left_warn if self.pitch < self.pitch_limits[0] or self.pitch > self.pitch_limits[1] else self.image_left_normal

        #painter.fillRect(self.rect(), QColor(240, 240, 240))
        painter.fillRect(self.rect(), QColor(255, 255, 255))

        x_center = self.width() // 2
        y_center = self.height() // 2
        line_x_offset = self.width() // 10
        left_pane_x = self.width() // 4
        right_pane_x = self.width() * 3 // 4
        image_y = self.height() // 2
        image_size = self.width() // 2 - 2 * line_x_offset
        #image_height = self.height() // 3
        line_y = y_center + image_size // 3
        top_text_y_offset = 20
        bottom_text_y_offset = 20

        image_rear_scaled = self.image_rear.scaled(image_size, image_size, Qt.KeepAspectRatio, Qt.SmoothTransformation)
        image_left_scaled = self.image_left.scaled(image_size, image_size, Qt.KeepAspectRatio, Qt.SmoothTransformation)

        # Draw pitch image
        transform = QTransform()
        transform.translate(left_pane_x, image_y)
        transform.rotate(self.pitch, Qt.ZAxis)
        painter.setTransform(transform)
        painter.drawImage(-image_left_scaled.width() // 2, -image_left_scaled.height() // 2, image_left_scaled)

        # Draw roll image
        transform = QTransform()
        transform.translate(right_pane_x, image_y)
        transform.rotate(self.roll, Qt.ZAxis)
        painter.setTransform(transform)
        painter.drawImage(-image_rear_scaled.width() // 2, -image_rear_scaled.height() // 2, image_rear_scaled)

        painter.resetTransform()

        # Draw label texts
        painter.setFont(self.font)
        painter.drawText(QRectF(0, 0, x_center, 2 * top_text_y_offset), Qt.AlignCenter, "Pitch")
        painter.drawText(QRectF(x_center, 0, self.width() // 2, 2 * top_text_y_offset), Qt.AlignCenter, "Roll")

        # Draw value texts
        painter.setFont(self.large_font)
        painter.drawText(QRectF(0, self.height() - 2 * bottom_text_y_offset, x_center, 2 * bottom_text_y_offset), Qt.AlignCenter,
                         f"{round(self.pitch, 1)}°")
        painter.drawText(QRectF(x_center, self.height() - 2 * bottom_text_y_offset, x_center, 2 * bottom_text_y_offset), Qt.AlignCenter,
                         f"{round(self.roll, 1)}°")

        # Draw horizon lines
        painter.setPen(QColor(75, 75, 75))
        painter.drawLine(line_x_offset, line_y, x_center - line_x_offset, line_y)
        painter.drawLine(x_center + line_x_offset, line_y, self.width() - line_x_offset, line_y)

        # Draw boundary
        painter.drawRect(0, 0, self.width(), self.height())
