import pygame as pg 

clock = pg.time.Clock()

pg.init()
#图片库
grass_image = pg.image.load('E:/code for vs code/py/platformer_project_5/data/images/grass.png')
dirt_image = pg.image.load('E:/code for vs code/py/platformer_project_5/data/images/dirt.png')
plant_image = pg.image.load('E:/code for vs code/py/platformer_project_5/data/images/plant.png')
player_image = pg.image.load('E://code for vs code//py//platformer_project_5//data//images//entities//player//idle//idle_0.png')
#设置透明色：小人的底图颜色为白 设置colourkey让它变透明
player_image.set_colorkey((255, 255, 255))

#获取图片像素大小
Tile_size = grass_image.get_width()#这几个图片长宽一样 不用处理

#制作贴图背景坐标图（地狱版 (for 贴图
game_map = [['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '0', '2', '2', '2', '2', '2', '0', '0', '0', '0', '0', '0', '0'],
            ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
            ['2', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '2'],
            ['1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '1', '1'],
            ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'],
            ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'],
            ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'],
            ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'],
            ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1']]
#实现碰撞部分
def collision_test(rect, tiles):
    hit_list = []
    for tile in tiles :
        if rect.colliderect(tile):
            hit_list.append(tile)
    return hit_list

#关于窗口缩放
WindowsSize = (600, 400)
display = pg.Surface((300, 200))

#窗口初始化
screen = pg.display.set_mode(WindowsSize)
# scr = pg.image.load('E:\code for vs code\MarkdownFile\e06\L1.png')
# screen.blit(scr,(0,0)) 插入底图

  
moving_right = False
moving_left = False 
moving_up = False
moving_down = False
# 用于判断是否移动

player_location = [100, 100]

#模拟重力
player_y_momentum = 0

# #模拟碰撞
# #玩家碰撞箱
# player_rect = pg.Rect(player_location[0], player_location[1], player_image.get_width(), player_image.get_height())
# #目标碰撞箱
# test_rect = pg.Rect(100, 100, 100, 50)


while True :
    # 未进行窗口缩放前
    # screen.fill((146,244,255)) #每一层渲染前覆盖上一层
    # screen.blit(player_image,player_location)
    # 进行窗口缩放后
    display.fill((146, 244, 255))
    display.blit(player_image,player_location)

    #窗口贴图：
    tile_rects = []
    y = 0 
    for row in game_map:
        x = 0
        for tile in row:
            if tile == '1':
                display.blit(dirt_image, (x * Tile_size, y * Tile_size))
            if tile == '2':
                display.blit(grass_image, (x * Tile_size, y * Tile_size))
            if tile != '0': #为空气设置碰撞箱
                tile_rects.append(pg.Rect(x * Tile_size, y * Tile_size, Tile_size, Tile_size))
            x += 1
        y += 1


    # #模拟碰撞
    # player_rect.x = player_location[0]
    # player_rect.y = player_location[1]#实时更新玩家碰撞箱坐标
    # if player_rect.colliderect(test_rect) :# 检测是否碰撞
    #     pg.draw.rect(screen, (255, 0, 0), test_rect)
    # else :
    #     pg.draw.rect(screen, (255, 255, 0), test_rect)


    #模拟重力
    if player_location[1] > WindowsSize[1] / 2 - 6 * Tile_size - 0.5 * player_image.get_height(): #有个小问题，窗口缩放前后判定的条件不同，如何改变？
        player_y_momentum = -player_y_momentum
    else: 
        player_y_momentum += 0.007
    player_location[1] += player_y_momentum

    #移动
    if moving_left == True:
        player_location[0] -= 1
    if moving_right == True:
        player_location[0] += 1
    if moving_up == True:
        player_location[1] -= 1.3
    if moving_down == True:
        player_location[1] += 1.3
    
    # 用于判定移动
    for event in pg.event.get() :
        if event.type == pg.KEYDOWN:
            if event.key == pg.K_RIGHT:
                moving_right = True
            if event.key == pg.K_LEFT:
                moving_left = True
            if event.key == pg.K_UP:
                moving_up = True
            if event.key == pg.K_DOWN:
                moving_down = True

        if event.type == pg.KEYUP:
            if event.key == pg.K_RIGHT:
                moving_right = False
            if event.key == pg.K_LEFT:
                moving_left = False
            if event.key == pg.K_UP:
                moving_up = False
            if event.key == pg.K_DOWN:
                moving_down = False




        if event.type == pg.KEYDOWN:
              if event.key == pg.K_ESCAPE:
                pg.quit() #检测到按下按键就退出

    #关于窗口缩放
    surf = pg.transform.scale(display, WindowsSize)
    screen.blit(surf, (0, 0))
    clock.tick(300)
    pg.display.update()


                

        
            

