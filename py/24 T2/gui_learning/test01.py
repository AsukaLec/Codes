import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel, QVBoxLayout, QWidget
from PyQt5.QtCore import QProcess
from PyQt5.QtCore import pyqtSlot

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("小游戏主界面")
        self.setGeometry(100, 100, 400, 200)

        # 创建一个按钮，用于启动小游戏
        self.start_button = QPushButton("开始小游戏", self)
        self.start_button.clicked.connect(self.start_mini_game)

        # 创建一个标签，用于显示小游戏的结果
        self.result_label = QLabel("小游戏结果：", self)

        # 布局
        layout = QVBoxLayout()
        layout.addWidget(self.start_button)
        layout.addWidget(self.result_label)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

        # 初始化 QProcess
        self.game_process = QProcess(self)
        self.game_process.finished.connect(self.game_finished)
        self.game_process.readyReadStandardOutput.connect(self.read_output)

    @pyqtSlot(int, QProcess.ExitStatus)
    def game_finished(self, exit_code, exit_status):
        # 游戏结束后的逻辑封装
        self.result_label.setText(f"小游戏结果：退出码 {exit_code}")
        print(f"游戏结束，退出码: {exit_code}")

    def read_output(self):
        # 读取小游戏的标准输出
        output = self.game_process.readAllStandardOutput().data()
        try:
            output_text = output.decode('utf-8').strip()
        except UnicodeDecodeError:
            output_text = output.decode('utf-8', errors='ignore').strip()
        self.result_label.setText(f"小游戏输出：{output_text}")

    def start_mini_game(self):
        # 启动小游戏脚本
        self.game_process.start("python", [r"py\gui_learning\game_script.py"])

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
