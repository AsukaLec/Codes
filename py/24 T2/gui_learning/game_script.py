import sys
import pygame
import random

# 初始化 Pygame
pygame.init()

# 设置屏幕大小
screen_width, screen_height = 800, 600
screen = pygame.display.set_mode((screen_width, screen_height))

# 设置标题
pygame.display.set_caption("简单小游戏")

# 定义颜色
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# 游戏变量
game_over = False
result = 0

# 游戏主循环
while not game_over:
    # 处理事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            game_over = True
            
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                # 按下空格键时结束游戏
                game_over = True
                result = random.randint(1, 100)  # 随机生成一个结果
            elif event.key == pygame.K_q:
                # 按下 ESC 键时退出游戏
                game_over = True
                result = 111# 可以设置为特定的退出码，例如 0 表示正常退出

    # 填充屏幕
    screen.fill(WHITE)

    # 绘制文本
    font = pygame.font.Font(None, 36)
    text = font.render("按空格键结束游戏，按 ESC 退出游戏", True, BLACK)
    text_rect = text.get_rect(center=(screen_width // 2, screen_height // 2))
    screen.blit(text, text_rect)

    # 更新屏幕
    pygame.display.flip()

# 游戏结束
print(f"游戏结束，得分: {result}")
pygame.quit()
sys.exit(result)