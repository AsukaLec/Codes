import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QTableWidget, QTableWidgetItem, QComboBox
from PyQt5.QtCore import Qt

class LeaderboardWindow(QWidget):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("排行榜")
        self.resize(1200, 800)

        self.layout = QVBoxLayout()

        # 创建下拉菜单用于选择游戏
        self.game_combo = QComboBox()
        self.game_combo.addItems(self.main_window.leaderboards.keys())  # 添加所有游戏名称
        self.game_combo.currentTextChanged.connect(self.update_leaderboard)  # 当选择的游戏改变时更新排行榜
        self.layout.addWidget(self.game_combo)

        # 创建表格用于显示排行榜
        self.table = QTableWidget()
        self.table.setColumnCount(3)  # 设置列数
        self.table.setHorizontalHeaderLabels(["排名", "用户名", "分数"])  # 设置列标题
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)  # 设置表格为只读
        self.layout.addWidget(self.table)

        self.setLayout(self.layout)

        # 初始化显示第一个游戏的排行榜
        self.update_leaderboard(self.game_combo.currentText())

    def update_leaderboard(self, game_name):
        # 更新排行榜表格
        if game_name in self.main_window.leaderboards:
            leaderboard_data = self.main_window.leaderboards[game_name]
            sorted_data = sorted(leaderboard_data.items(), key=lambda item: item[1], reverse=True)

            self.table.setRowCount(len(sorted_data))  # 设置行数
            for row, (user, score) in enumerate(sorted_data):
                self.table.setItem(row, 0, QTableWidgetItem(str(row + 1)))  # 排名
                self.table.setItem(row, 1, QTableWidgetItem(user))  # 用户名
                self.table.setItem(row, 2, QTableWidgetItem(str(score)))  # 分数

            self.table.resizeColumnsToContents()  # 自动调整列宽


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("游戏排行榜系统")
        self.setGeometry(300, 240, 1200, 800)

        # 初始化排行榜数据
        self.leaderboards = {
            "Game1": {},
            "Game2": {},
            "Game3": {},
            "Game4": {},
            "Game5": {},
            "Game6": {},
            "Game7": {},
            "Game8": {},
            "Game9": {}
        }

        # 初始化排行榜窗口
        self.leaderboard_window = LeaderboardWindow(self)

        self.initUI()

    def initUI(self):
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.open_leaderboard_button = QPushButton("查看排行榜", self.central_widget)
        self.open_leaderboard_button.resize(100, 30)
        self.open_leaderboard_button.move(250, 150)
        self.open_leaderboard_button.clicked.connect(self.leaderboard_window.show)

    def update_score(self, user, game, score):
        # 更新用户的分数
        if game in self.leaderboards:
            if user in self.leaderboards[game]:
                self.leaderboards[game][user] = max(self.leaderboards[game][user], score)
            else:
                self.leaderboards[game][user] = score

        # 如果当前显示的是这个排行榜，更新显示
        if game == self.leaderboard_window.game_combo.currentText():
            self.leaderboard_window.update_leaderboard(game)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())


    main_window.update_score("Alice", "Game1", 0)