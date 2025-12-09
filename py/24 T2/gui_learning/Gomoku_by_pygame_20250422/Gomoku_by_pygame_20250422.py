#Game_by_pygame_20250422.py
import sys
import os
import pygame as pg
import numpy as np
import random

#Global area.
#Pygame initializing.
pg.init()
screen=pg.display.set_mode((1280, 720))

#Set fonts.
fontPath=os.path.join(os.path.dirname(__file__), 'Fonts/')
pg.font.init()
GothicE108=pg.font.Font(fontPath+'gothice.ttf', 108)
GothicE72=pg.font.Font(fontPath+'gothice.ttf', 72)
GothicE32=pg.font.Font(fontPath+'gothice.ttf', 32)
Algerian26=pg.font.Font(fontPath+'ALGER.ttf', 26)
Algerian56=pg.font.Font(fontPath+'ALGER.ttf', 56)
Edwardian=pg.font.Font(fontPath+'ITCEDSCR.ttf', 26)

#Colors.
gridColor=(101, 67, 33)
lblColor=(55, 28, 15)
black=(40, 20, 10)
white=(255, 253, 241)

#Texts.
class Text:
    def __init__(self, font, txt, pos, color, refresh=False):
        self.__refresh=refresh
        self.__txtSurf=font.render(txt, True, color)
        self.__txtRect=self.__txtSurf.get_rect(center=pos)
        
    def get_size(self):
        return self.__txtRect.width, self.__txtRect.height

    def draw(self):
        if self.__refresh:
            pg.draw.rect(screen, (255, 212, 100), self.__txtRect)
        screen.blit(self.__txtSurf, self.__txtRect)

    def clear(self):
        pg.draw.rect(screen, (255, 212, 100), self.__txtRect)

#Show victor.
def showVic(victor=True):
    x=960
    y1=430
    y2=550
    if victor:
        line1=Text(GothicE108, 'Black', (x, y1), black)
        line2=Text(GothicE108, 'Wins', (x, y2), black)
    else:
        line1=Text(GothicE108, 'White', (x, y1), white)
        line2=Text(GothicE108, 'Wins', (x, y2), white)
    size1=line1.get_size()
    size2=line2.get_size()
    cover=pg.Rect(0, 0, max(size1[0], size2[0])+70, size1[1]+size2[1])
    cover.center=(x, (y1+y2)/2)
    pg.draw.rect(screen, (255, 212, 100), cover)
    line1.draw()
    line2.draw()
    pg.display.update()

#Check if five in a row.
def checkVictory(brd):
    #Rows.
    for col in range(15):
        bCnt=0
        wCnt=0
        for row in range(15):
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True

    #Columns.
    for row in range(15):
        bCnt=0
        wCnt=0
        for col in range(15):
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True
    
    #Foward diagonal.
    #Upper-right area.
    for colBgn in range(15):
        bCnt=0
        wCnt=0
        col=colBgn
        while col<15:
            row=col-colBgn
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True
            col+=1
    #Lower-left area.
    for rowBgn in range(1, 15):
        bCnt=0
        wCnt=0
        row=rowBgn
        while row<15:
            col=row-rowBgn
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True
            row+=1

    #Backward diagonal.
    #Upper-left area.
    for colBgn in range(15):
        bCnt=0
        wCnt=0
        col=colBgn
        while col>=0:
            row=colBgn-col
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True
            col-=1
    #Lower-right area.
    for rowBgn in range(1, 15):
        bCnt=0
        wCnt=0
        row=rowBgn
        while row<15:
            col=14+rowBgn-row
            if brd[row][col]=='B':
                bCnt+=1
                wCnt=0
            elif brd[row][col]=='W':
                wCnt+=1
                bCnt=0
            else:
                bCnt=0
                wCnt=0
            if bCnt==5:
                showVic()
                return True
            elif wCnt==5:
                showVic(False)
                return True
            row+=1

def main():
    #Set screen.
    pg.display.set_caption('Gomoku')
    screen.fill((255, 212, 100))
    
    #Print texts.
    title=Text(GothicE72, 'GOMOKU', (960, 120), lblColor)
    title.draw()
    author=Text(Edwardian, 'Exclusively Developed by Edison Leong', (960, 680), lblColor)
    author.draw()

    #Draw board with coordinates(labels).
    for i in range(15):
        width=3 if i in (0, 14) else 2
        #Grid
        pg.draw.line(screen, gridColor, (80, 80+i*40), (640, 80+i*40), width)    #Draw rows.
        pg.draw.line(screen, gridColor, (80+i*40, 80), (80+i*40, 640), width)    #Draw columns.
        #Coordinates.
        Text(Algerian26, chr(ord('A')+i), (80+i*40, 50), lblColor).draw()
        Text(Algerian26, str(15-i), (45, 80+i*40), lblColor).draw()
    pg.display.update()    #Show the labels.

    vBoard=np.full((15, 15), '', dtype=str)
    moveCnt=0
    stonePos=[]
    blackNote=Text(Algerian56, 'Black first.', (960, 460), black, True)
    whiteNote=Text(Algerian56, 'White follows.', (960, 460), white, True)
    blackNote.draw()

    #Main loop.
    running=True
    victory=False
    while running:
        for event in pg.event.get():
            #Quit.
            if event.type==pg.QUIT or event.type==pg.KEYDOWN and event.key==pg.K_ESCAPE:
                running=False
                if event.key == pg.K_ESCAPE:
                    if (moveCnt % 2 == 1) :
                        result = max(109 - (moveCnt + 1), 0)
                    else:
                        result = max(110 - moveCnt / 2, 0)

                    pg.quit()
                    # 退出 Pygame
                    # 退出游戏
                    print(result)  # 将结果输出到标准输出
                    print(f"设置退出码为 {result}")

                    sys.exit(result)
    
            #Place stones.
            if not victory and event.type==pg.MOUSEBUTTONDOWN and event.button==1 and 40<event.pos[0]<680 and 40<event.pos[1]<680:
                posOnBrd=[round((x-80)/40) if 80<=x<=640 else 0 if x<80 else 14 for x in event.pos]
                pos=[80+x*40 for x in posOnBrd]
                if pos not in stonePos:
                    moveCnt+=1
                    stonePos.append(pos)
                    #Check for black or white.
                    if moveCnt%2:
                        stone=black
                        vBoard[posOnBrd[0]][posOnBrd[1]]='B'
                        Text(GothicE32, f'Black: {moveCnt//2+1:3} stones', (960, 240), stone, True).draw()
                        if moveCnt==1:
                            blackNote.clear()
                            whiteNote.draw()
                        else:
                            Text(Algerian56, '{:^12}'.format('White turn.'), (980, 460), white, True).draw()
                    else:
                        stone=white
                        vBoard[posOnBrd[0]][posOnBrd[1]]='W'
                        Text(GothicE32, f'White: {moveCnt//2:3} stones', (960, 300), stone, True).draw()
                        if moveCnt==2:
                            whiteNote.clear()
                        Text(Algerian56, '{:^11}'.format('Black turn.'), (980, 460), black, True).draw()
                    pg.draw.circle(screen, stone, pos, 17)
                    victory=checkVictory(vBoard)

            #Update.
            pg.display.update()

if __name__=='__main__':
    main()


