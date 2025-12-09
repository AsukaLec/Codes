import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLabel, QFileDialog, QMessageBox, QMainWindow, QDialog,QApplication, QPushButton, QLabel, QFileDialog, QMessageBox,QVBoxLayout, QHBoxLayout, QLineEdit, QTableWidget, QTableWidgetItem,QAbstractItemView, QDialog, QFormLayout
from PyQt5.QtGui import QPixmap, QPalette
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QBrush
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QLabel, QFileDialog, QMessageBox, QMainWindow, QDialog, QComboBox
import time
import json
import generat
import merge
import visualization_history
import visualization_predict

class VisualizeDialog(QDialog):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Visualization')
        self.resize(400, 300)
        
        # 创建一个垂直布局
        layout = QVBoxLayout()
        
        # 创建第一个按钮
        self.button1 = QPushButton('历史数据集可视化')
        self.button1.clicked.connect(self.on_button1_clicked)  # 绑定点击事
        # 将按钮添加到布局中
        layout.addWidget(self.button1)
        
        # 创建第二个按钮
        self.button2 = QPushButton('预测数据集可视化')
        self.button2.clicked.connect(self.on_button2_clicked)  # 绑定点击事件
        # 将按钮添加到布局中
        layout.addWidget(self.button2)
        
        # 设置窗口的布局
        self.setLayout(layout)

    def on_button1_clicked(self):
        # 调用历史数据集可视化的子程序
        visualization_history.generate_pic()
    
    def on_button2_clicked(self):
        # 调用预测数据集可视化的子程序
        visualization_predict.generate_pic()
        

class CreateUserWindow(QDialog):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("创建用户")
        self.resize(400, 200)

        layout = QVBoxLayout()

        self.username_input = QLineEdit()
        layout.addWidget(QLabel("用户名:"))
        layout.addWidget(self.username_input)

        create_button = QPushButton("创建")
        create_button.clicked.connect(self.create_user)
        layout.addWidget(create_button)

        self.setLayout(layout)

    def create_user(self):
        username = self.username_input.text()

        if not username:
            QMessageBox.warning(self, "警告", "用户名不能为空！")
            return

        if username in self.main_window.users:
            QMessageBox.warning(self, "警告", "用户已存在！")
            return

        self.main_window.users[username] = {"history": []}
        self.main_window.save_users()
        QMessageBox.information(self, "成功", "用户创建成功！")
        self.close()

class ChooseUserWindow(QDialog):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("选择当前用户")
        self.resize(400, 200)

        layout = QVBoxLayout()

        self.user_combo = QComboBox()
        self.user_combo.addItems(self.main_window.users.keys())
        layout.addWidget(self.user_combo)

        select_button = QPushButton("选择")
        select_button.clicked.connect(self.choose_user)
        layout.addWidget(select_button)

        self.setLayout(layout)

    def choose_user(self):
        selected_user = self.user_combo.currentText()
        if selected_user:
            self.main_window.set_current_user(selected_user)
            QMessageBox.information(self, "成功", f"当前用户已设置为: {selected_user}")
            self.close()
        else:
            QMessageBox.warning(self, "警告", "请选择一个用户！")

class ShowUserRecordsWindow(QDialog):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("用户记录")
        self.resize(600, 400)

        layout = QVBoxLayout()

        self.user_combo = QComboBox()
        self.user_combo.addItems(self.main_window.users.keys())
        self.user_combo.currentTextChanged.connect(self.update_table)
        layout.addWidget(self.user_combo)

        self.table = QTableWidget()
        self.table.setColumnCount(2)
        self.table.setHorizontalHeaderLabels(["时间", "操作"])
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        layout.addWidget(self.table)

        self.setLayout(layout)

        # 初始加载当前用户的历史记录
        if self.main_window.current_user:
            self.user_combo.setCurrentText(self.main_window.current_user)
            self.update_table()

    def update_table(self):
        selected_user = self.user_combo.currentText()
        user_data = self.main_window.users.get(selected_user, {})
        history = user_data.get("history", [])

        self.table.setRowCount(len(history))
        for row, record in enumerate(history):
            self.table.setItem(row, 0, QTableWidgetItem(record["time"]))
            self.table.setItem(row, 1, QTableWidgetItem(record["action"]))

        self.table.resizeColumnsToContents()

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('PyQt Application')
        self.setGeometry(100, 100, 1328, 830)
    
        self.initUI()
        self.set_background_image('background.png')  # 设置背景图
        self.users = self.load_users()  # 加载用户信息
        self.current_user = None  # 当前用户初始化为 None
        
    def initUI(self):
        self.history_button = QPushButton('选择 历史文件', self)
        self.history_button.move(60, 220)  # 设置按钮位置
        self.history_button.resize(300, 50)  # 设置按钮大小
        self.history_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.history_button.clicked.connect(self.open_history_file_dialog)
        self.history_button.show()

        self.prediction_button = QPushButton('选择 预测文件', self)
        self.prediction_button.move(60, 290)  # 设置按钮位置
        self.prediction_button.resize(300, 50)  # 设置按钮大小
        self.prediction_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.prediction_button.clicked.connect(self.open_prediction_file_dialog)
        self.prediction_button.show()

        self.save_button = QPushButton('选择 保存路径', self)
        self.save_button.move(900, 220)  # 设置按钮位置
        self.save_button.resize(300, 50)  # 设置按钮大小
        self.save_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.save_button.clicked.connect(self.open_save_file_dialog)
        self.save_button.show()

        self.file1_label = QLabel('当前历史文件路径: None', self)
        self.file1_label.move(20, 360)  # 设置标签位置
        self.file1_label.resize(600, 50)  # 设置标签大小
        self.file1_label.show()

        self.file2_label = QLabel('当前预测文件路径: None', self)
        self.file2_label.move(20, 410)  # 设置标签位置
        self.file2_label.resize(600, 50)  # 设置标签大小
        self.file2_label.show()

        self.file3_label = QLabel('当前保存文件路径: None', self)
        self.file3_label.move(770, 290)  # 设置标签位置
        self.file3_label.resize(600, 50)  # 设置标签大小
        self.file3_label.show()

        self.global_button = QPushButton('全局', self)
        self.global_button.move(60, 480)
        self.global_button.resize(100, 50)
        self.global_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.global_button.clicked.connect(self.select_global)
        self.global_button.show()

        self.recent_button = QPushButton('最近', self)
        self.recent_button.move(200, 480)
        self.recent_button.resize(100, 50)
        self.recent_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.recent_button.clicked.connect(self.select_recent)
        self.recent_button.show()

        self.generate_mode_label = QLabel('当前生成方式: None', self)
        self.generate_mode_label.move(20, 550)  # 设置标签位置
        self.generate_mode_label.resize(600, 50)  # 设置标签大小
        self.generate_mode_label.show()

        self.generate_button = QPushButton('生成', self)
        self.generate_button.move(60, 650)  # 设置按钮位置
        self.generate_button.resize(300, 50)  # 设置按钮大小
        self.generate_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.generate_button.clicked.connect(self.generate_files)
        self.generate_button.show()

        self.merge_button = QPushButton('混合更新历史文件', self)
        self.merge_button.move(900, 360)  # 设置按钮位置
        self.merge_button.resize(300, 50)  # 设置按钮大小
        self.merge_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.merge_button.clicked.connect(self.merge_files)
        self.merge_button.show()

        self.visualize_button = QPushButton('可视化', self)
        self.visualize_button.move(60, 720)  # 设置按钮位置
        self.visualize_button.resize(300, 50)  # 设置按钮大小
        self.visualize_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.visualize_button.clicked.connect(self.open_visualize_dialog)
        self.visualize_button.show()

        self.create_user_button = QPushButton('创建用户', self)
        self.create_user_button.move(900, 550)  # 设置按钮位置
        self.create_user_button.resize(300, 50)  # 设置按钮大小
        self.create_user_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.create_user_button.clicked.connect(self.open_create_user_window)
        self.create_user_button.show()

        self.choose_user_button = QPushButton('选择当前用户', self)
        self.choose_user_button.move(900, 620)  # 设置按钮位置
        self.choose_user_button.resize(300, 50)  # 设置按钮大小
        self.choose_user_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.choose_user_button.clicked.connect(self.open_choose_user_window)
        self.choose_user_button.show()

        # 新增选择用户和查看历史记录按钮
        self.select_user_button = QPushButton('选择用户和查看历史记录', self)
        self.select_user_button.move(900, 700)  # 设置按钮位置
        self.select_user_button.resize(300, 50)  # 设置按钮大小
        self.select_user_button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.3); }")
        self.select_user_button.clicked.connect(self.open_show_records_window)
        self.select_user_button.show()

         # 显示当前用户
        self.current_user_label = QLabel('当前用户: 未选择', self)
        self.current_user_label.move(900, 480)  # 设置标签位置
        self.current_user_label.resize(300, 50)  # 设置标签大小
        self.current_user_label.show()

    def open_history_file_dialog(self):
        self.history_file_path, _ = QFileDialog.getOpenFileName(self, 'Open File', '', 'CSV Files (*.csv)')
        if self.history_file_path:
            self.file1_label.setText(f'当前历史文件路径: {self.history_file_path}')
            
    def open_prediction_file_dialog(self):
        self.prediction_file_path, _ = QFileDialog.getOpenFileName(self, 'Open File', '', 'CSV Files (*.csv)')
        if self.prediction_file_path:
            self.file2_label.setText(f'当前预测文件路径: {self.prediction_file_path}')
    
    def open_save_file_dialog(self):
        self.save_file_path, _ = QFileDialog.getOpenFileName(self, 'Open File', '', 'CSV Files (*.csv)')
        if self.save_file_path:
            self.file3_label.setText(f'当前保存文件路径: {self.save_file_path}')

    def select_global(self):
        self.generate_method = 'global'
        QMessageBox.information(self, '选择', '已选择全局生成方式')
        self.generate_mode_label.setText(f'当前生成方式: {self.generate_method}')
    
    def select_recent(self):
        self.generate_method = 'recent'
        QMessageBox.information(self, '选择', '已选择最近生成方式')
        self.generate_mode_label.setText(f'当前生成方式: {self.generate_method}')

    def write_path_and_method(self):
        params = {
            "history_file_path": self.history_file_path,
            "prediction_file_path": self.prediction_file_path,
            "save_file_path": self.save_file_path,
            "generate_method": self.generate_method
        }
        with open("params.json", "w") as f:
            json.dump(params, f)

        if self.current_user:
            if "history" not in self.users[self.current_user]:
                self.users[self.current_user]["history"] = []
            self.users[self.current_user]["history"].append({
                "time": time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()),
                "action": f"Updated params: {params}"
            })
        self.save_users()

        QMessageBox.information(self, '成功', '参数已成功写入 params.json 文件')

    def generate_files(self):
        # 这里调用另一个程序
        print("生成文件...")
        self.write_path_and_method()
        generat.set_path_and_method()

        generat.generate_prediction()
        
        QMessageBox.information(self, '成功', '生成成功')

    def merge_files(self):
        # 这里调用另一个程序
        print("混合文件...")
        self.write_path_and_method()
        merge.set_path_and_method()
        merge.merge_file()
        
        QMessageBox.information(self, '成功', '混合成功')
    
    def open_visualize_dialog(self):
        self.visualize_dialog = VisualizeDialog()
        self.visualize_dialog.exec_()
    
    def set_background_image(self, image_path):
        pixmap = QPixmap(image_path)
        brush = QBrush(pixmap)
        palette = QPalette()
        palette.setBrush(QPalette.Window, brush)
        self.setPalette(palette)

    def open_create_user_window(self):
        self.create_user_window = CreateUserWindow(self)
        self.create_user_window.show()

    def open_choose_user_window(self):
        self.choose_user_window = ChooseUserWindow(self)
        self.choose_user_window.show()

    def open_show_records_window(self):
        self.show_records_window = ShowUserRecordsWindow(self)
        self.show_records_window.show()

    def load_users(self):
        try:
            with open("users.json", "r") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def save_users(self):
        with open("users.json", "w") as f:
            json.dump(self.users, f, indent=4)

    def set_current_user(self, username):
        self.current_user = username
        self.current_user_label.setText(f'当前用户: {username}')
        # 如果用户记录窗口已打开，更新其内容
        if hasattr(self, 'show_records_window') and self.show_records_window:
            self.show_records_window.user_combo.setCurrentText(username)
            self.show_records_window.update_table()

    def update_user_records(self):
        if self.current_user:
            user_data = self.users.get(self.current_user, {})
            history = user_data.get("history", [])
            # 如果有显示用户记录的窗口，可以在这里更新表格
            # 例如：self.show_records_window.update_table()


def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
