from PyQt5.Qt import *
import sys

app = QApplication(sys.argv)
#创建
window = QWidget()
window.resize(1145,514)
window1 = QPushButton()
window2 = QLabel()
label = QLabel(window)
#设置
window.setWindowTitle("fvck u")
# window.setText("damn")
label.setText("damndamn")
#展示
window.show()
 
# window1.show()
# window2.show()

sys.exit(app.exec())

