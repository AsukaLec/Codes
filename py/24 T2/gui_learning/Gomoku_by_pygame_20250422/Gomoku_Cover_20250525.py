from PIL import Image, ImageDraw, ImageFont
import os

# 创建画布 (400*350)
img = Image.new('RGB', (400, 350), color=(255, 212, 100))
draw = ImageDraw.Draw(img)

# 字体路径配置（需确保Fonts文件夹存在）
font_dir = os.path.join(os.path.dirname(__file__), 'Fonts')
gothic_font = os.path.join(font_dir, 'gothice.ttf')
algerian_font = os.path.join(font_dir, 'ALGER.ttf')
edwardian_font = os.path.join(font_dir, 'ITCEDSCR.ttf')

# 棋盘参数
board_size = 240
board_pos = (80, 72)
cell_size = 16
line_color = (101, 67, 33)

# ---- 绘制棋盘 ----
# 边框
draw.rectangle([board_pos, (board_pos[0]+board_size, board_pos[1]+board_size)], 
              outline=line_color, width=3)

# 网格线
for i in range(15):
    x = board_pos[0] + i*cell_size
    y = board_pos[1] + i*cell_size
    # 行
    draw.line([(x, board_pos[1]), (x, board_pos[1]+board_size)],
             fill=line_color, width=1)
    # 列 
    draw.line([(board_pos[0], y), (board_pos[0]+board_size, y)],
             fill=line_color, width=1)

# ---- 绘制棋子 ----
stones = [
    (6,6, 'B'), (8,8, 'B'), (8,12, 'W'), (10,8, 'W'),
    (8,4, 'B'), (4,8, 'W'), (10,10, 'B'), (6,8, 'W')
]
for x,y,c in stones:
    pos = (board_pos[0]+x*cell_size, board_pos[1]+y*cell_size)
    color = (40, 20, 10) if c == 'B' else (255, 253, 241)
    shadow = (0,0,0) if c == 'B' else (200,200,200)
    # 棋子主体
    draw.ellipse([(pos[0]-12, pos[1]-12), (pos[0]+12, pos[1]+12)],
                fill=color, outline=shadow)

# ---- 文字内容 ----
# 主标题（GothicE字体）
title_font = ImageFont.truetype(gothic_font, 56)
draw.text((200, 20), 'GOMOKU', 
         fill=(55, 28, 15), font=title_font, anchor='mt')

# 作者信息（Edwardian字体）
author_font = ImageFont.truetype(edwardian_font, 20)
draw.text((200, 340), 'By Edison Leong',
         fill=(55, 28, 15), font=author_font, anchor='mb')

# 保存图片
save_path = os.path.join(os.path.dirname(__file__), 'Gomoku_Cover.png')
img.save(save_path)
print('封面已生成：Gomoku_Cover.png')