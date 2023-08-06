import datetime
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QTableWidget, QAbstractItemView, QHeaderView, QTableWidgetItem, QAbstractScrollArea

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