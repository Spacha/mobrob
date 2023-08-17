import datetime
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import (QTableWidget, QAbstractItemView, QHeaderView, QTableWidgetItem,
                             QDialog, QGridLayout, QLabel, QLineEdit, QTextEdit)

class MessagePopup(QDialog):
    def __init__(self, log_time, log_source, log_type, log_content, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Log message")
        self.setModal(True)

        self.resize(480, 120)

        layout = QGridLayout()

        self.time_label = QLabel(self)
        self.time_label.setText("Time")
        self.time_field = QLineEdit(self)
        self.time_field.setText(log_time)
        self.time_field.setReadOnly(True)

        self.source_label = QLabel(self)
        self.source_label.setText("Source")
        self.source_field = QLineEdit(self)
        self.source_field.setText(log_source)
        self.source_field.setReadOnly(True)

        self.type_label = QLabel(self)
        self.type_label.setText("Type")
        self.type_field = QLineEdit(self)
        self.type_field.setText(log_type)
        self.type_field.setReadOnly(True)

        self.content_label = QLabel(self)
        self.content_label.setText("Content")
        self.content_field = QTextEdit(self)
        self.content_field.setText(log_content)
        self.content_field.setReadOnly(True)

        # Lay out the grid
        layout.addWidget(self.time_label,    0, 0)
        layout.addWidget(self.time_field,    0, 1)
        layout.addWidget(self.source_label,  1, 0)
        layout.addWidget(self.source_field,  1, 1)
        layout.addWidget(self.type_label,    2, 0)
        layout.addWidget(self.type_field,    2, 1)
        layout.addWidget(self.content_label, 3, 0)
        layout.addWidget(self.content_field, 3, 1)
        self.setLayout(layout)


class LogWidget(QTableWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
    
        # Create the table widget
        self.setColumnCount(4)  # Columns: time, source, type, content
        self.setHorizontalHeaderLabels(["Time", "Source", "Type", "Content"])
        self.setEditTriggers(QAbstractItemView.NoEditTriggers)

        # Make the table have a list view aesthetic
        self.verticalHeader().setDefaultSectionSize(18)
        self.verticalHeader().setVisible(False)
        self.horizontalScrollBar().setVisible(False)
        self.setShowGrid(False)
        self.setSelectionBehavior(QTableWidget.SelectRows)

        # Style the table view
        self.horizontalHeader().setDefaultAlignment(Qt.AlignLeft)
        self.setColumnWidth(0, 60)                                              # fixed size (resizable)
        self.setColumnWidth(1, 60)                                              # fixed size (resizable)
        self.setColumnWidth(2, 60)                                              # fixed size (resizable)
        self.setColumnWidth(3, 1000)
        self.horizontalHeader().setSectionResizeMode(0, QHeaderView.Fixed)
        self.horizontalHeader().setSectionResizeMode(1, QHeaderView.Fixed)
        self.horizontalHeader().setSectionResizeMode(2, QHeaderView.Fixed)
        self.horizontalHeader().setSectionResizeMode(3, QHeaderView.Stretch)    # fill the rest
        self.setAlternatingRowColors(True)
        self.setMinimumWidth(240)

        # Disable selection for column headers
        self.horizontalHeader().setSectionsClickable(False)
        self.horizontalHeader().setSectionsMovable(False)

        # Connect double-click event to open message pop-up
        self.doubleClicked.connect(self.show_log_message_popup)
    
    def add_row(self, source, log_type, content):
        # Add a new row to the table and insert the log data
        row_count = self.rowCount()
        self.insertRow(row_count)

        #log_time = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-5]
        log_time = datetime.datetime.now().strftime("%H:%M:%S")
        self.setItem(row_count, 0, QTableWidgetItem(log_time))
        self.setItem(row_count, 1, QTableWidgetItem(source))
        self.setItem(row_count, 2, QTableWidgetItem(log_type))
        self.setItem(row_count, 3, QTableWidgetItem(content))
        self.resizeRowsToContents()

        # Scroll to the newly added row
        new_item = self.item(row_count, 0)
        if new_item:
            self.scrollToItem(new_item)

    def show_log_message_popup(self, index):
        time_item = self.item(index.row(), 0)
        source_item = self.item(index.row(), 1)
        type_item = self.item(index.row(), 2)
        content_item = self.item(index.row(), 3)

        if time_item and type_item and content_item:
            log_time = time_item.text()
            log_source = source_item.text()
            log_type = type_item.text()
            log_content = content_item.text()

            # Create and show the message pop-up
            popup = MessagePopup(log_time, log_source, log_type, log_content, self)
            popup.exec_()
