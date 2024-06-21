import sys
from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QTextEdit, QLabel, QSizePolicy

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        grid = QGridLayout()
        self.setLayout(grid)

        # Create the widgets
        log_window = QTextEdit("Log window")
        right_pane = QLabel("Right Pane (Fixed Width)")
        bottom_pane = QLabel("Bottom Pane (Fixed Height)")
        other_window = QLabel("Other Window")

        # Set fixed size for right and bottom panes
        right_pane.setFixedWidth(200)
        bottom_pane.setFixedHeight(150)

        # Set size policy for the log window and other window to expand
        log_window.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        #other_window.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        # Add widgets to the grid layout
        grid.addWidget(log_window, 0, 0)
        grid.addWidget(right_pane, 0, 1)
        grid.addWidget(bottom_pane, 1, 0)
        grid.addWidget(other_window, 1, 1)

        self.setWindowTitle('PyQt Layout Example')
        self.show()

def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
