import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from mobrob_server import MobrobServer, Message

SERVER_ADDR     = "192.168.1.168"
SERVER_PORT     = 3333
SERVER_BUFSIZE  = 64
SERVER_TIMEOUT  = 1

class LogWidget:
    pass


class MapWidget:
    pass


class DashboardApplication(QMainWindow):
    def __init__(self) -> None:
        super(DashboardApplication, self).__init__()

        self.server = MobrobServer(SERVER_ADDR, SERVER_PORT)

        self.server.start(lambda msg: self.receive_message(msg))
    
    def receive_message(self, message: Message):
        print(f"[GUI] Received message: {message}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DashboardApplication()
    window.show()
    sys.exit(app.exec_())
