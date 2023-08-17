import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLabel
from PyQt5.QtGui import QPainter, QColor, QPen
from PyQt5.QtCore import Qt


class MapWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setRenderHint(QPainter.Antialiasing)

        # Draw grid
        grid_step = 20
        painter.setPen(QColor(200, 200, 200))
        for x in range(0, self.width(), grid_step):
            painter.drawLine(x, 0, x, self.height())
        for y in range(0, self.height(), grid_step):
            painter.drawLine(0, y, self.width(), y)

        # Draw points
        painter.setPen(QPen(Qt.red, 5))
        points = [(50, 50), (100, 100), (200, 150), (250, 200)]
        for point in points:
            painter.drawPoint(*point)


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.graph_widget = MapWidget()

        layout = QVBoxLayout()
        layout.addWidget(self.graph_widget)

        label = QLabel(self)
        label.setText("Hello, World!")
        layout.addWidget(label)

        central_widget = QWidget()
        central_widget.setLayout(layout)
        self.setCentralWidget(central_widget)

        self.setWindowTitle("Graphical Content with PyQt5")
        self.setGeometry(100, 100, 800, 600)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
