#面向对象 用类来写
from PyQt5.Qt import *

class Window(QWidget) :
    def __init__ (self):
        super().__init__() #调用父类方法
        self.setWindowTitle("damn")
        self.resize(1145,900)
        self.set_ui()

    def set_ui(self):
        #self.Qobject继承结构测试()
        #self.QObject对象名称和属性的操作()
        self.QObject对象名称和属性的操作案例()

    def Qobject继承结构测试(self):
        mros = QObject.mro()
        for mro in mros :
            print(mro) 

    def QObject对象名称和属性的操作(self) :
        obj = QObject()
        obj.setObjectName("notice")
        print (obj.objectName())
    
    def QObject对象名称和属性的操作案例(self) : 
        label = QLabel(self)
        label.setText("小组作业")
        label.setStyleSheet("font-size: 60px; color: red;")#qss 存储字体样式
        
        label1 = QLabel(self)
        label1.setText("114514")
        label1.move(100,100)
        label1.setStyleSheet("font-size: 60px; color: red;")
        
        button1 = QPushButton(self)
        button1.move(200,200)
        # button1.setText("good game")
        icon = QIcon('py\gui_learning\小鸟.png')
        button1.setIcon(icon)
        button1.resize(400,320)
        button1.setIconSize(button1.size())


if __name__ == '__main__':
    import sys 

    app = QApplication(sys.argv)

    window1 = Window()
    window1.set_ui()
    window1.show()

    sys.exit(app.exec())
