import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QLabel, QFileDialog

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("PyQt 主窗口")
        self.setGeometry(100, 100, 400, 200)

        # 创建一个按钮用于选择文件
        self.button = QPushButton("选择文件", self)
        self.button.clicked.connect(self.select_file)  # 绑定按钮点击事件

        # 创建一个标签用于显示文件路径
        self.label = QLabel("选择的文件路径将显示在这里", self)

        # 设置布局
        layout = QVBoxLayout()
        layout.addWidget(self.button)
        layout.addWidget(self.label)

        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

    def select_file(self):
        # 弹出文件选择对话框
        file_path, _ = QFileDialog.getOpenFileName(self, "选择文件", "", "All Files (*)")
        if file_path:  # 如果用户选择了文件
            self.label.setText(f"选择的文件路径: {file_path}")
            # 你也可以在这里将文件路径传递给其他函数或处理逻辑
            self.process_selected_file(file_path)

    def process_selected_file(self, file_path):
        # 这里可以处理选择的文件路径
        print(f"主函数接收到的文件路径: {file_path}")
        # 例如，你可以在这里调用其他模块的函数，将文件路径传递过去

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
