from graphics import *

win = GraphWin('Guessing Music Star',800,800)
win.setCoords(0,0,200,200)

#界面1：开始游戏界面
#主标题
title = Text(Point(100,150),'Welcome to Guessing Music Star!')
title.setFill('red')
title.setSize(36)
title.draw(win)
#作者
name = Text(Point(100,140),'人工智能1班：钟皓玮')
name.setSize(17)
name.draw(win)
#开始游戏按钮
play_button = Rectangle(Point(70,120),Point(130,80))
play_button.setFill('orange')
play_button.draw(win)
play_text = Text(Point(100,100),'PLAY')
play_text.setSize(36)
play_text.draw(win)

#循环监听：当在play里点击鼠标，到下一个界面
while True:
    click0 = win.getMouse()
    x,y = click0.getX(),click0.getY()
    if 70 <= x <= 130 and 80 <= y <= 120:
        win.close()

        #第一关：小星星
        win1 = GraphWin('Round 1',800,800)
        win1.setCoords(0, 0, 200, 200)
        title1 = Text(Point(50,190),'Round 1')
        title1.setFill('red')
        title1.setSize(36)
        title1.draw(win1)

        #5*2个横线（空格）
        def little_star(hang,lie):
            for i in range(hang):
                y = 130 - i * 30
                for j in range(lie):
                    x1 = 40 + j * 20
                    x2 = 50 + j * 20
                    line1_1 = Line(Point(x1,y),Point(x2,y)).draw(win1)
        little_star(2,7)

        #可供玩家选择点击的音符
        def little_star_button(text):
            lie = 7
            for i in range(lie):
                x1 = 20 + i * 25
                x2 = 40 + i * 25
                button1 = Rectangle(Point(x1,80),Point(x2,50))
                button1.setFill('light blue')
                button1.draw(win1)
                choice1 = Text(Point((x1 + x2) / 2,65),text_list[i])
                choice1.setSize(30)
                choice1.draw(win1)
        text_list = ['#do','re','mi','#fa','sol','la','xi']
        little_star_button(text_list)

        #生命值绘制：三个红色圆形，右上角
        hp_text = Text(Point(133,190),'HP:')
        hp_text.setSize(25)
        hp_text.draw(win1)
        def hp_circle(o):
            circle = Circle(Point(o,190),7)
            circle.setFill('red')
            circle.draw(win1)
        hp1 = hp_circle(150)
        hp2 = hp_circle(170)
        hp3 = hp_circle(190)

        #生命值减少：当点错按钮后，生命值-1
        def hp_reduce(o):
            circle = Circle(Point(o,190),7)
            circle.setFill('white')
            circle.draw(win1)

        # 横线的音符
        def music1(x, y, text):
            music = Text(Point(x, y), text)
            music.setFill('green')
            music.setSize(25)
            return music
        m1 = music1(45, 140, 'la')
        m2 = music1(65, 140, 'la')
        m3 = music1(85, 140, 'mi')
        m4 = music1(105, 140, 'mi')
        m5 = music1(125, 140, '#fa')
        m6 = music1(145, 140, '#fa')
        m7 = music1(165, 140, 'mi')
        m8 = music1(45, 110, 're')
        m9 = music1(65, 110, 're')
        m10 = music1(85, 110, '#do')
        m11 = music1(105, 110, '#do')
        m12 = music1(125, 110, 'xi')
        m13 = music1(145, 110, 'xi')
        m14 = music1(165, 110, 'la')
        music_list = [m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13,m14]

        #绘制红色叉叉，当点错音符按钮时出现
        def wrong(x1,y1,x2,y2):
            w = Line(Point(x1,y1),Point(x2,y2))
            w.setFill('red')
            w.setWidth(8)
            w.draw(win1)

        # 设置输入框
        tips1 = Text(Point(30, 20), '请输入歌曲名字：')
        tips1.setSize(17)
        tips1.draw(win1)
        name = Entry(Point(65,20),width = 10)
        name.draw(win1)

        # 猜测的按钮
        guess1 = Rectangle(Point(50,15),Point(75,5))
        guess1.setFill('orange')
        guess1.draw(win1)
        guess_text1 = Text(Point(63,10),'guess')
        guess_text1.draw(win1)

        #回答正确的提示
        winner = Text(Point(150,20),'回答正确！！！')
        winner.setFill('red')
        winner.setSize(23)

        #回答错误的提示
        loser = Text(Point(150,20),'回答错误，请退出重新作答')
        loser.setFill('blue')
        loser.setSize(23)

        #当点击按钮时，匹配音符，使音符出现；如果点错了，则出现红色叉叉，生命值-1
        while True:
            click1 = win1.getMouse()
            for i in range(7):
                x1_1 = 20 + i * 25
                x1_2 = 40 + i * 25
                if x1_1 <= click1.getX() <= x1_2 and 50 <= click1.getY() <= 80:
                    note = text_list[i]
                    if note == 'sol':
                        w1_sol = wrong(120, 80, 140, 50)
                        w1_sol = wrong(140, 80, 120, 50)
                        hp1 = hp_reduce(150)
                    for j in music_list:
                        if note == j.getText():
                            j.draw(win1)
            # 输入程序：当输入小星星时显示正确，其他显示错误
            if 50 <= click1.getX() <= 75 and 5 <= click1.getY() <= 15:
                answer = name.getText()
                if answer == '小星星':
                   winner.draw(win1)
                else:
                    loser.draw(win1)

