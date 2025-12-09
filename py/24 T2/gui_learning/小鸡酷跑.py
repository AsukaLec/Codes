import pygame
import random
import sys
import os

# 初始化pygame
pygame.init()

# 游戏窗口设置
WIDTH = 800
HEIGHT = 400
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("天天酷跑 - 鸡版")

# 颜色定义
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
SKY_BLUE = (135, 206, 235)
YELLOW = (255, 255, 0)

# 游戏参数
clock = pygame.time.Clock()
FPS = 60
GRAVITY = 1
GAME_SPEED = 5
SCORE = 0
FONT = pygame.font.SysFont('Arial', 30)

# 加载最高分
if os.path.exists('high_score.txt'):
    with open('high_score.txt', 'r') as file:
        HIGH_SCORE = int(file.read())
else:
    HIGH_SCORE = 0

# 创建鸡的图像（改进版像素艺术）
def create_chicken_image():
    chicken = pygame.Surface((50, 50), pygame.SRCALPHA)
    # 鸡身体（黄色）
    pygame.draw.ellipse(chicken, (255, 255, 0), (10, 15, 30, 25))
    # 鸡头（黄色）
    pygame.draw.circle(chicken, (255, 255, 0), (35, 15), 10)
    # 鸡冠（红色）
    pygame.draw.polygon(chicken, (255, 0, 0), [(35, 5), (40, 2), (45, 5)])
    # 鸡嘴（橙色）
    pygame.draw.polygon(chicken, (255, 165, 0), [(45, 15), (50, 15), (45, 18)])
    # 鸡眼睛（黑色）
    pygame.draw.circle(chicken, (0, 0, 0), (38, 13), 2)
    # 鸡翅膀（深黄色）
    pygame.draw.ellipse(chicken, (200, 200, 0), (5, 20, 15, 10))
    return chicken

# 玩家类（鸡）- 添加二连跳功能
class Chicken(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = create_chicken_image()
        self.rect = self.image.get_rect()
        self.rect.x = 100
        self.rect.y = HEIGHT - 100
        self.velocity = 0
        self.jump_count = 0
        self.max_jumps = 2  # 允许二连跳

    def update(self):
        # 重力效果
        self.velocity += GRAVITY
        self.rect.y += self.velocity

        # 确保鸡不会掉出屏幕底部
        if self.rect.bottom > HEIGHT - 20:
            self.rect.bottom = HEIGHT - 20
            self.velocity = 0
            self.jump_count = 0  # 落地后重置跳跃计数

    def jump(self):
        if self.jump_count < self.max_jumps:
            self.velocity = -18
            self.jump_count += 1

# 障碍物类（变细版本）
class Obstacle(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.height = random.randint(40, 80)
        self.width = 15  # 比原来更细的障碍物
        self.image = pygame.Surface((self.width, self.height))
        self.image.fill(RED)
        self.rect = self.image.get_rect()
        self.rect.x = WIDTH
        self.rect.bottom = HEIGHT - 20

    def update(self):
        self.rect.x -= GAME_SPEED
        if self.rect.right < 0:
            self.kill()

# 金币类
class Coin(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((20, 20))
        self.image.fill((255, 215, 0))  # 金色
        self.rect = self.image.get_rect()
        self.rect.x = WIDTH
        self.rect.y = random.randint(HEIGHT - 200, HEIGHT - 50)

    def update(self):
        self.rect.x -= GAME_SPEED
        if self.rect.right < 0:
            self.kill()

# 云朵背景装饰
class Cloud(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = pygame.Surface((100, 50), pygame.SRCALPHA)
        pygame.draw.ellipse(self.image, (255, 255, 255, 200), (0, 0, 100, 50))
        self.rect = self.image.get_rect()
        self.rect.x = WIDTH
        self.rect.y = random.randint(50, 150)
        self.speed = random.uniform(1, 3)

    def update(self):
        self.rect.x -= self.speed
        if self.rect.right < 0:
            self.rect.x = WIDTH
            self.rect.y = random.randint(50, 150)

# 绘制按钮
def draw_button(text, x, y, width, height, inactive_color, active_color):
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()

    if x < mouse[0] < x + width and y < mouse[1] < y + height:
        pygame.draw.rect(screen, active_color, (x, y, width, height))
        if click[0] == 1:
            return True
    else:
        pygame.draw.rect(screen, inactive_color, (x, y, width, height))

    text_surf = FONT.render(text, True, BLACK)
    text_rect = text_surf.get_rect()
    text_rect.center = ((x + (width / 2)), (y + (height / 2)))
    screen.blit(text_surf, text_rect)
    return False

# 开始界面
def start_screen():
    global HIGH_SCORE
    intro = True
    while intro:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        screen.fill(SKY_BLUE)
        title_text = FONT.render("keep running !", True, BLACK)
        high_score_text = FONT.render(f'highest score EVER: {HIGH_SCORE}', True, BLACK)
        screen.blit(title_text, (WIDTH // 2 - title_text.get_width() // 2, 50))
        screen.blit(high_score_text, (WIDTH // 2 - high_score_text.get_width() // 2, 100))

        if draw_button("start", WIDTH // 2 - 100, 200, 200, 50, YELLOW, WHITE):
            intro = False
        if draw_button("out", WIDTH // 2 - 100, 300, 200, 50, YELLOW, WHITE):
            pygame.quit()
            sys.exit()

        pygame.display.flip()
        clock.tick(FPS)

# 创建精灵组
all_sprites = pygame.sprite.Group()
obstacles = pygame.sprite.Group()
coins = pygame.sprite.Group()
clouds = pygame.sprite.Group()

# 创建玩家（鸡）
chicken = Chicken()
all_sprites.add(chicken)

# 创建背景云朵
for i in range(5):
    cloud = Cloud()
    clouds.add(cloud)
    all_sprites.add(cloud)

# 障碍物生成计时器
obstacle_timer = 0
coin_timer = 0

# 游戏状态
game_over = False

# 显示开始界面
start_screen()

# 游戏主循环
running = True
while running:
    # 事件处理
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE and not game_over:
                chicken.jump()
            if event.key == pygame.K_r and game_over:
                # 重置游戏
                game_over = False
                SCORE = 0
                GAME_SPEED = 5
                all_sprites.empty()
                obstacles.empty()
                coins.empty()
                clouds.empty()
                chicken = Chicken()
                all_sprites.add(chicken)
                for i in range(5):
                    cloud = Cloud()
                    clouds.add(cloud)
                    all_sprites.add(cloud)
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
               # 退出游戏
                pygame.quit()
                result = random.randint(1,1000)  # 随机生成一个结果

                target_score = int(SCORE)

                print(target_score)  # 将结果输出到标准输出
                print(f"设置退出码为 {target_score}")

                sys.exit(target_score)

    if not game_over:
        # 更新
        all_sprites.update()

        # 生成障碍物
        obstacle_timer += 1
        if obstacle_timer > random.randint(60, 120):
            obstacle = Obstacle()
            obstacles.add(obstacle)
            all_sprites.add(obstacle)
            obstacle_timer = 0

        # 生成金币
        coin_timer += 1
        if coin_timer > random.randint(30, 90):
            coin = Coin()
            coins.add(coin)
            all_sprites.add(coin)
            coin_timer = 0

        # 碰撞检测 - 障碍物
        if pygame.sprite.spritecollide(chicken, obstacles, False):
            game_over = True

        # 碰撞检测 - 金币
        coin_hits = pygame.sprite.spritecollide(chicken, coins, True)
        for coin in coin_hits:
            SCORE += 10

        # 增加分数和难度
        SCORE += 0.2
        if int(SCORE) % 4 == 1:
            GAME_SPEED += 0.03
        if GAME_SPEED > 40:
            GAME_SPEED = 40

    # 绘制
    screen.fill(SKY_BLUE)

    # 绘制地面
    pygame.draw.rect(screen, GREEN, (0, HEIGHT - 20, WIDTH, 20))

    # 先绘制背景元素（云朵）
    for cloud in clouds:
        screen.blit(cloud.image, cloud.rect)

    # 绘制其他精灵
    for sprite in all_sprites:
        if sprite not in clouds:
            screen.blit(sprite.image, sprite.rect)

    # 显示分数
    score_text = FONT.render(f'score: {int(SCORE)}', True, BLACK)
    screen.blit(score_text, (10, 10))

    # 显示跳跃次数（调试用）
    jump_text = FONT.render(f'jump times: {chicken.jump_count}/2', True, BLACK)
    screen.blit(jump_text, (10, 50))

    SPEED_text = FONT.render(f'GAME_SPEED: {int(GAME_SPEED)}', True, BLACK)
    screen.blit(SPEED_text, (10, 90))

    # 游戏结束显示
    if game_over:
        if SCORE > HIGH_SCORE:
            HIGH_SCORE = int(SCORE)
            with open('high_score.txt', 'w') as file:
                file.write(str(HIGH_SCORE))
        game_over_text = FONT.render('push“ ERC ” to EXIT', True, BLACK)
        screen.blit(game_over_text, (WIDTH // 2 - 150, HEIGHT // 2 - 15))

    # 更新显示
    pygame.display.flip()

    # 控制帧率
    clock.tick(FPS)

    

