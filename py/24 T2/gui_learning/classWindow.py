#面向对象 用类来写
from PyQt5.Qt import *

class Window(QWidget) :
    def __init__ (self):
        super().__init__() #调用父类方法
        self.setWindowTitle("damn")
        self.resize(1145,514)
    def set_ui(self):
        label = QLabel(self)
        label.setText ("damn")


if __name__ == '__main__':
    import sys 

    app = QApplication(sys.argv)

    window1 = Window()
    window1.set_ui()
    window1.show()

    sys.exit(app.exec())
