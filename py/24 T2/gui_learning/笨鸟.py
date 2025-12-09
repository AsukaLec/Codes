from turtle import *
from random import randrange
from time import sleep
import random
import sys

def square(x,y,size,color_name):
    up()
    goto(x,y)
    down()
    color(color_name)
    begin_fill()
    
    forward(size)
    left(90)
    forward(size)
    left(90)
    forward(size)
    left(90)
    forward(size)
    left(90)

    end_fill()

def line(x,y,a,b,line_width = 1,color_name = "black"):
    up()
    goto(x,y)
    down()
    color(color_name)
    width(line_width)
    goto(a,b)

bird = [-30,80]
ball = [[240,0]]
bird_size = 50
ball_size = 80

def change():
    bird[1] = bird[1]+bird_size
def distance(x,y,a,b):
    return ((a-x)**2+(b-y)**2)**0.5
def hit():
    for n in range(len(ball)):
        if distance(ball[n][0],ball[n][1],bird[0],bird[1])<(bird_size+ball_size)/2:
            return True
    return False
def inside():
    if bird[1] < -300+bird_size/2 or bird[1] > 300-bird_size/2:
        return False
    else :
        return True
def draw():
    clear()
    for n in range(len(ball)):
        up()
        goto(ball[n][0],ball[n][1])
        dot(ball_size,"dark green")
        ball[n][0] = ball[n][0]-3
    up()
    goto(bird[0],bird[1])
    dot(bird_size,"yellow")
    bird[1] = bird[1]-5
    update()
def gameLoop():
    global bird,ball,bird_size,ball_size

    if randrange(40) == 1:
        x=240
        y=randrange(-300,300)
        ball.append([x,y])
    if len(ball) != 0:
        if ball[0][0]<-220:
            ball.pop(0)
    draw()
    if(not inside()) or hit():
        sleep(2)
        bird = [-30,80]
        ball = [[240,0]]
        bird_size = 50
        ball_size = 80

    ontimer(gameLoop,30)


setup(420,620,0,0)
hideturtle()
tracer(False)
bgcolor("light blue")
listen()
onkey(lambda:change()," ")
gameLoop()
done()

result = random.randint(1,1000)  # 随机生成一个结果

print(result)  # 将结果输出到标准输出
print(f"设置退出码为 {result}")

sys.exit(result)