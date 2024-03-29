from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QColor, QPen, QImage, QPainterPath, QTransform, QFont

class MapWidget(QWidget):
    def __init__(self, parent=None, robot=None):
        super().__init__(parent)
        self.robot = robot
        self.font = QFont("Arial", 16)
        self.draw_robot_sprite()

    def draw_robot_sprite(self):
        # create a QPixmap or QImage to store the pre-drawn sprite
        self.robot_sprite_buffer = QImage(64, 64, QImage.Format_ARGB32)
        self.robot_sprite_buffer.fill(Qt.transparent)

        # the chassis
        painter = QPainter(self.robot_sprite_buffer)
        painter.setRenderHint(QPainter.Antialiasing)
        painter.fillRect(20, 20, 24, 44, QColor(255, 0, 0))

        # the forward facing arrow
        path = QPainterPath()
        path.moveTo(20, 20 - 2)
        path.lineTo(32, 10 - 2)
        path.lineTo(44, 20 - 2)
        path.lineTo(20, 20 - 2)
        painter.setPen(Qt.NoPen)
        painter.fillPath(path, QColor(255, 0, 0))

        painter.end()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        painter.fillRect(self.rect(), QColor(180, 180, 180))

        # draw points
        painter.setPen(QPen(Qt.red, 5))
        points = [(50, 50), (100, 100), (200, 150), (250, 200)]
        for point in points:
            painter.drawPoint(*point)

        # rotate the robot sprite
        rotation_transform = QTransform().rotate(self.robot.angle)
        rotated_sprite = self.robot_sprite_buffer.transformed(rotation_transform)

        # draw the robot sprite
        painter.drawImage(self.width() // 2 - rotated_sprite.width() // 2, self.height() // 2 - rotated_sprite.height() // 2, rotated_sprite)

        painter.setFont(self.font)
        painter.drawText(self.width() // 2, self.height() - 30, f"Angle: {round(self.robot.angle, 1)} degrees.")

        # draw the boundaries
        painter.setPen(QColor(75, 75, 75))
        painter.drawRect(0, 0, self.width(), self.height())
