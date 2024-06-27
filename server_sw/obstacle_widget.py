from PyQt5.QtCore import Qt, QRectF
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QPainter, QColor, QPen, QImage, QPainterPath, QTransform, QFont

class ObstacleWidget(QWidget):
    MAX_OBSTACLE_DIST = 30.0
    obstacle_dist = 999.9
    left_track_dir = 0.0
    right_track_dir = 0.0

    def __init__(self, parent=None, obstacle_dist=None, left_track_dir=None, right_track_dir=None):
        super().__init__(parent)

        self.font = QFont("Arial", 14)
        self.setFixedWidth(250)
        self.setMinimumHeight(350)

        image_prefix = "resources/view_top"
        self.robot_images = {
            ( 0,  0): QImage(f"{image_prefix}.png"),
            ( 0, -1): QImage(f"{image_prefix}_rb.png"),
            ( 0,  1): QImage(f"{image_prefix}_rf.png"),
            (-1,  0): QImage(f"{image_prefix}_lb.png"),
            ( 1,  0): QImage(f"{image_prefix}_lf.png"),
            (-1, -1): QImage(f"{image_prefix}_lbrb.png"),
            ( 1,  1): QImage(f"{image_prefix}_lfrf.png"),
            (-1,  1): QImage(f"{image_prefix}_lbrf.png"),
            ( 1, -1): QImage(f"{image_prefix}_lfrb.png")
        }
        self.obstacle_image_warning = QImage("resources/obstacle_warn.png")
        self.obstacle_image_danger = QImage("resources/obstacle_danger.png")

        self.update_data(obstacle_dist, left_track_dir, right_track_dir)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        painter.fillRect(self.rect(), QColor(255, 255, 255))

        # Draw the robot
        self.robot_image = self.robot_images[(self.left_track_dir, self.right_track_dir)]
        # TODO: could be done once in constructor
        robot_image_width = self.width() // 3
        robot_image_scaled = self.robot_image.scaled(robot_image_width, robot_image_width, Qt.KeepAspectRatio, Qt.SmoothTransformation)
        robot_y = self.height() - robot_image_scaled.height() // 2 - 60
        painter.drawImage(self.width() // 2 - robot_image_scaled.width() // 2, robot_y, robot_image_scaled)

        if self.obstacle_dist <= self.MAX_OBSTACLE_DIST:
            # Draw the obstacle
            obstacle_image = self.obstacle_image_warning if self.obstacle_dist > 10.0 else self.obstacle_image_danger
            robot_front = robot_y - robot_image_scaled.height() // 2
            obstacle_image_width = self.width() // 4
            obstacle_image_scaled = obstacle_image.scaled(obstacle_image_width, obstacle_image_width, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            obstacle_y = int(robot_front - robot_front * self.obstacle_dist // self.MAX_OBSTACLE_DIST)
            painter.drawImage(
                self.width() // 2 - obstacle_image_scaled.width() // 2,
                obstacle_y - obstacle_image_scaled.height() // 2,
                obstacle_image_scaled
            )

            # Draw the distance text below the obstacle
            painter.setFont(self.font)
            painter.drawText(QRectF(
                0, obstacle_y + obstacle_image_scaled.height() // 2,
                self.width(), 20
            ), Qt.AlignCenter, f"{round(self.obstacle_dist)} cm")

        # draw the boundaries
        painter.setPen(QColor(75, 75, 75))
        painter.drawRect(0, 0, self.width(), self.height())

    def update_data(self, obstacle_dist: float=None, left_track_dir: float=None, right_track_dir: float=None) -> None:
        if obstacle_dist is not None:
            self.obstacle_dist = obstacle_dist
        if left_track_dir is not None:
            self.left_track_dir = left_track_dir
        if right_track_dir is not None:
            self.right_track_dir = right_track_dir
        self.repaint()
