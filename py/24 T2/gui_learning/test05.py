#面向对象 用类来写
from PyQt5.Qt import *
import sys
from classWindow import Window

app = QApplication(sys.argv)

# class Window(QWidget) :
#     def __init__ (self):
#         super().__init__() #调用父类方法
#         self.setWindowTitle("damn")
#         self.resize(1145,514)
#     def set_ui(self):
#         label = QLabel(self)
#         label.setText ("damn")

window1 = Window()
window1.set_ui()
window1.show()

sys.exit(app.exec())

# print(QAbstractButton.__subclasses__())
