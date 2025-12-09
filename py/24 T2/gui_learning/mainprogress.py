from PyQt5.Qt import *
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QVBoxLayout, QHBoxLayout, QLineEdit, QLabel, QMessageBox, QListWidget, QListWidgetItem
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget, QTableWidget, QTableWidgetItem, QComboBox, QMessageBox
from PyQt5.QtCore import Qt, QProcess
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QWidget, QTableWidget, QTableWidgetItem, QComboBox, QMessageBox, QLabel
from PyQt5.QtCore import Qt, QProcess
import os

selected_character_name = None
selected_game_name = None
score = None

script_path = ['py\gui_learning\music_guess.py',
            'py\gui_learning\笨鸟.py',
            'py\gui_learning\ice_fire.py',
            'py\gui_learning\小鸡酷跑.py',
            'py\gui_learning\Gomoku_by_pygame_20250422\Gomoku_by_pygame_20250422.py', 
            'py\gui_learning\坦克大战.py', 
            'py\gui_learning\game2048.py', 
            'py\gui_learning\太空射击游戏.py', 
            '']
picture = ['py\gui_learning\猜歌.png', 
        'py\gui_learning\小鸟.png', 
        'py\gui_learning\ice_fire.jpg', 
        'py\gui_learning\小鸡酷跑.png', 
        'py\gui_learning\go.png', 
        'py\gui_learning\坦克大战.png', 
        'py\gui_learning\game2048.png', 
        'py\gui_learning\太空射击游戏.png', 
        '']
PLAYER_photo = [
            'py\gui_learning\PLAYER_photo\P1.jpg',
            'py\gui_learning\PLAYER_photo\P2.jpg',
            'py\gui_learning\PLAYER_photo\P3.jpg',
            'py\gui_learning\PLAYER_photo\P4.jpg',
            'py\gui_learning\PLAYER_photo\P5.jpg',
            'py\gui_learning\PLAYER_photo\P6.jpg',
            'py\gui_learning\PLAYER_photo\P7.jpg',
            'py\gui_learning\PLAYER_photo\P8.jpg',
            'py\gui_learning\PLAYER_photo\P9.jpg'
        ]

class LeaderboardWindow(QWidget):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("排行榜")
        self.resize(600, 400)

        # 创建下拉菜单用于选择游戏
        self.game_combo = QComboBox(self)
        self.game_combo.addItems(self.main_window.leaderboards.keys())  # 添加所有游戏名称
        self.game_combo.move(50, 50)
        self.game_combo.currentTextChanged.connect(self.update_leaderboard)

        # 创建表格用于显示排行榜
        self.table = QTableWidget(self)
        self.table.setColumnCount(3)  # 设置列数
        self.table.setHorizontalHeaderLabels(["排名", "用户名", "分数"])  # 设置列标题
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)  # 设置表格为只读
        self.table.setGeometry(50, 100, 500, 250)  # 设置表格的位置和大小

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


class CharacterCreationWindow(QWidget):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.initUI()

    def initUI(self):
        self.setWindowTitle("角色创建")
        self.resize(1000, 800)

        # 创建姓名输入框
        self.name_label = QLabel("角色名称:", self)
        self.name_label.move(50, 50)
        self.name_input = QLineEdit(self)
        self.name_input.move(150, 50)
        self.name_input.resize(200, 25)

        # 创建头像选择区域
        self.avatar_label = QLabel("选择头像:", self)
        self.avatar_label.move(50, 100)

        # 头像图片路径列表
        self.avatar_paths = PLAYER_photo
        # 创建按钮和对应的 QLabel 用于显示图片
        self.avatar_buttons = []
        for i in range(9):
            button = QPushButton(self)
            button.resize(150, 150)
            button.move(50 + (i % 3) * 170, 150 + (i // 3) * 170)

            label = QLabel(self)
            label.resize(125, 125)
            label.move(65 + (i % 3) * 170, 165 + (i // 3) * 170)
            pixmap = QPixmap(self.avatar_paths[i])
            scaled_pixmap = pixmap.scaled(125, 125, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            label.setPixmap(scaled_pixmap)
            label.raise_()

            button.clicked.connect(lambda checked, idx=i: self.select_avatar(idx))
            self.avatar_buttons.append((button, label))

        # 创建创建角色按钮
        self.create_button = QPushButton("创建角色", self)
        self.create_button.resize(100, 30)
        self.create_button.move(750, 350)
        self.create_button.clicked.connect(self.create_character)

    def select_avatar(self, index):
        # 选中头像后，将其他按钮的样式重置，选中的按钮高亮显示
        for i, (button, label) in enumerate(self.avatar_buttons):
            if i == index:
                button.setStyleSheet("QPushButton { border: 3px solid blue; }")
            else:
                button.setStyleSheet("")
        self.selected_avatar = index

    def create_character(self):
        # 获取用户输入的角色名称
        name = self.name_input.text()

        # 检查是否选择了头像
        if not hasattr(self, 'selected_avatar'):
            QMessageBox.warning(self, "警告", "请选择一个头像！")
            return

        # 检查是否填写了角色名称
        if not name:
            QMessageBox.warning(self, "警告", "请输入角色名称！")
            return

        # 保存角色信息
        avatar_path = self.avatar_paths[self.selected_avatar]
        character_info = {
            "name": name,
            "avatar": avatar_path
        }

        # 将角色信息添加到主窗口的角色列表中
        self.main_window.add_character(character_info)

        # 弹出提示框，显示角色信息
        QMessageBox.information(self, "成功", f"角色创建成功！\n角色名称: {name}\n头像: {avatar_path}")

        # 清空表单
        self.name_input.clear()
        del self.selected_avatar

class CharacterSelectionWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.characters = []
        self.initUI()

    def initUI(self):
        self.setWindowTitle("角色选择")
        self.resize(400, 300)

        self.character_list = QListWidget(self)
        self.character_list.resize(380, 250)
        self.character_list.move(10, 10)

        self.select_button = QPushButton("选择角色", self)
        self.select_button.resize(100, 30)
        self.select_button.move(150, 270)
        self.select_button.clicked.connect(self.select_character)

    def add_character(self, character_info):
        item = QListWidgetItem(character_info["name"])
        item.setIcon(QIcon(character_info["avatar"]))
        self.character_list.addItem(item)
        self.characters.append(character_info)

    def select_character(self):
        global selected_character_name  # 使用全局变量
        selected_item = self.character_list.currentItem()
        if selected_item:
            selected_character = self.characters[self.character_list.row(selected_item)]
            selected_character_name = selected_character['name']  # 存储选中的角色名称
            QMessageBox.information(self, "选择成功", f"你选择了角色: {selected_character['name']}")
            self.close()  # 关闭窗口
        else:
            QMessageBox.warning(self, "警告", "请选择一个角色！")


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # 设置窗口标题和大小
        self.setWindowTitle("9在1起组 Python小游戏")
        self.setGeometry(300, 240, 1800, 1200)

        # 初始化角色创建和角色选择窗口
        self.character_selection_window = CharacterSelectionWindow()
        self.character_creation_window = CharacterCreationWindow(self)
        
        # 初始化排行榜数据
        self.leaderboards = {
            "music_guess": {},
            "笨鸟": {},
            "ice_fire": {},
            "小鸡酷跑": {},
            "Gomoku_by_pygame_20250422": {},
            "坦克大战": {},
            "game2048": {},
            "太空射击游戏": {},
            "Game9": {},
        }

        # 初始化排行榜窗口
        self.leaderboard_window = LeaderboardWindow(self)

        self.initUI()

    def initUI(self):
        # 设置窗口大小
        self.resize(1800, 1200)

        # 创建 QLabel 用于显示图片
        self.label = QLabel(self)
        self.label.setGeometry(0, 0, 1800, 1200)  # 设置 QLabel 的位置和大小

        # 加载图片并设置到 QLabel
        pixmap = QPixmap("py\gui_learning\生成游戏主界面图片.png")  # 替换为你的图片路径
        self.label.setPixmap(pixmap)

        # 确保 QLabel 的大小与图片一致
        self.label.setScaledContents(True)
        
        #外接创建角色
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.create_character_button = QPushButton("创建角色", self.central_widget)
        self.create_character_button.resize(200, 60)
        self.create_character_button.move(1300, 1100)
        self.create_character_button.clicked.connect(self.character_creation_window.show)

        self.select_character_button = QPushButton("选择角色", self.central_widget)
        self.select_character_button.resize(200, 60)
        self.select_character_button.move(1600, 1100)
        self.select_character_button.clicked.connect(self.character_selection_window.show)

        # 创建按钮用于打开排行榜窗口
        self.open_leaderboard_button = QPushButton("查看排行榜", self)
        self.open_leaderboard_button.resize(200, 60)
        self.open_leaderboard_button.move(1300, 100)
        self.open_leaderboard_button.clicked.connect(self.leaderboard_window.show)

        def generate_push_button(self,x,y,script_path, picutre_path):
            self.button = QPushButton(self)
            self.button.resize(400,350)
            self.button.move(x,y)
                   # 创建 QLabel 用于显示图片
            self.label = QLabel(self.button)
            self.label.resize(380, 330)  # 设置 QLabel 大小与按钮一致
            self.label.move(10, 10)  # 将 QLabel 放在按钮的左上角

            # 加载图片并设置到 QLabel
            pixmap = QPixmap(picutre_path)  # 替换为你的图片路径
            scaled_pixmap = pixmap.scaled(400, 350, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            self.label.setPixmap(scaled_pixmap)

            # 确保 QLabel 在按钮上显示
            self.label.raise_()

            self.button.setStyleSheet("QPushButton { background-color: rgba(255, 255, 255, 0.5); }")

            self.button.clicked.connect(lambda: self.start_game(script_path))

            game_name = os.path.basename(script_path).replace('.py', '')
        
        
            # 点击按钮时更新全局变量
            def update_selected_game():
                global selected_game_name
                selected_game_name = game_name
                print(f"选中的游戏名称: {selected_game_name}")

            self.button.clicked.connect(update_selected_game)


        def generate_game_button(self, script_path, picutre):
            self.button1 = generate_push_button(self, 20, 20, script_path[0], picture[0])
            self.button2 = generate_push_button(self, 440, 20, script_path[1], picture[1])
            self.button3 = generate_push_button(self, 860, 20, script_path[2], picture[2])
            self.button4 = generate_push_button(self, 20, 390, script_path[3], picture[3])
            self.button5 = generate_push_button(self, 440, 390, script_path[4], picture[4])
            self.button6 = generate_push_button(self, 860, 390, script_path[5], picture[5])
            self.button7 = generate_push_button(self, 20, 760, script_path[6], picture[6])
            self.button8 = generate_push_button(self, 440, 760, script_path[7], picture[7])
            self.button9 = generate_push_button(self, 860, 760, script_path[8], picture[8])
        


        generate_game_button(self, script_path, picture)

    def add_character(self, character_info):
        self.character_selection_window.add_character(character_info)
       
    def start_game(self, script_path):
        if not selected_character_name :
            QMessageBox.warning(self, "警告", "请先选择一个角色！")
            return
        # 启动游戏脚本
        self.game_process = QProcess(self)
        self.game_process.finished.connect(self.game_finished)
        self.game_process.readyReadStandardOutput.connect(self.read_output)
        self.game_process.start("python", [script_path])  # 使用原始字符串
    
    def read_output(self):
        # 读取小游戏的标准输出
        output = self.game_process.readAllStandardOutput().data()
        try:
            output_text = output.decode('utf-8').strip()
        except UnicodeDecodeError:
            output_text = output.decode('utf-8', errors='ignore').strip()
        
    @pyqtSlot(int, QProcess.ExitStatus)
    def game_finished(self, exit_code, exit_status):
        # 游戏结束后的逻辑封装
        user = selected_character_name  # 当前用户
        game = selected_game_name  # 当前选择的游戏
        self.score = exit_code  # 将退出码赋值给 score
        self.update_score(user, game, self.score)  #

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

        QMessageBox.information(self, "游戏结束", f"你的得分是: {score}\n排行榜已更新！")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())