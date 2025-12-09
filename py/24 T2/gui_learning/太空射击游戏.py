import pygame
import random
import sys

# 初始化pygame
pygame.init()

# 确保中文正常显示
pygame.font.init()
font_names = ["SimHei", "WenQuanYi Micro Hei", "Heiti TC", "Arial"]
font = pygame.font.SysFont(font_names, 36)
small_font = pygame.font.SysFont(font_names, 24)

# 游戏窗口设置
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("太空射击游戏")

# 颜色定义
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)


# 加载图像
def load_image(name, width=50, height=50):
    image = pygame.Surface((width, height))
    if name == "player":
        image.fill(BLUE)
    elif name == "enemy":
        image.fill(RED)
    elif name == "bullet":
        image.fill(YELLOW)
    elif name == "powerup":
        image.fill(GREEN)
    return image


# 玩家类
class Player(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image = load_image("player", 50, 40)
        self.rect = self.image.get_rect()
        self.rect.centerx = WIDTH // 2
        self.rect.bottom = HEIGHT - 10
        self.speedx = 0
        self.health = 100
        self.shoot_delay = 250
        self.last_shot = pygame.time.get_ticks()
        self.lives = 3
        self.hidden = False
        self.hide_timer = pygame.time.get_ticks()
        self.power = 1
        self.power_time = pygame.time.get_ticks()

    def update(self):
        # 检查是否隐藏
        if self.hidden and pygame.time.get_ticks() - self.hide_timer > 1000:
            self.hidden = False
            self.rect.centerx = WIDTH // 2
            self.rect.bottom = HEIGHT - 10

        # 检查是否有能量增强时间限制
        if self.power >= 2 and pygame.time.get_ticks() - self.power_time > 5000:
            self.power -= 1
            self.power_time = pygame.time.get_ticks()

        self.speedx = 0
        keystate = pygame.key.get_pressed()
        if keystate[pygame.K_LEFT]:
            self.speedx = -5
        if keystate[pygame.K_RIGHT]:
            self.speedx = 5
        if keystate[pygame.K_SPACE]:
            self.shoot()

        # 边界限制
        self.rect.x += self.speedx
        if self.rect.right > WIDTH:
            self.rect.right = WIDTH
        if self.rect.left < 0:
            self.rect.left = 0

    def shoot(self):
        now = pygame.time.get_ticks()
        if now - self.last_shot > self.shoot_delay:
            self.last_shot = now
            if self.power == 1:
                bullet = Bullet(self.rect.centerx, self.rect.top)
                all_sprites.add(bullet)
                bullets.add(bullet)
            elif self.power >= 2:
                bullet1 = Bullet(self.rect.left, self.rect.centery)
                bullet2 = Bullet(self.rect.right, self.rect.centery)
                all_sprites.add(bullet1)
                all_sprites.add(bullet2)
                bullets.add(bullet1)
                bullets.add(bullet2)
            # 播放射击音效

    def powerup(self):
        self.power += 1
        self.power_time = pygame.time.get_ticks()

    def hide(self):
        self.hidden = True
        self.hide_timer = pygame.time.get_ticks()
        self.rect.center = (WIDTH // 2, HEIGHT + 200)


# 敌人类
class Enemy(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.image_orig = load_image("enemy", random.randrange(30, 70), random.randrange(20, 40))
        self.image = self.image_orig.copy()
        self.rect = self.image.get_rect()
        self.radius = int(self.rect.width * 0.85 / 2)
        self.rect.x = random.randrange(WIDTH - self.rect.width)
        self.rect.y = random.randrange(-100, -40)
        self.speedy = random.randrange(1, 4)
        self.speedx = random.randrange(-3, 3)
        self.rot = 0
        self.rot_speed = random.randrange(-8, 8)
        self.last_update = pygame.time.get_ticks()

    def rotate(self):
        now = pygame.time.get_ticks()
        if now - self.last_update > 50:
            self.last_update = now
            self.rot = (self.rot + self.rot_speed) % 360
            new_image = pygame.transform.rotate(self.image_orig, self.rot)
            old_center = self.rect.center
            self.image = new_image
            self.rect = self.image.get_rect()
            self.rect.center = old_center

    def update(self):
        self.rotate()
        self.rect.y += self.speedy
        self.rect.x += self.speedx
        if (self.rect.top > HEIGHT + 10 or
                self.rect.left < -25 or
                self.rect.right > WIDTH + 25):
            self.rect.x = random.randrange(WIDTH - self.rect.width)
            self.rect.y = random.randrange(-100, -40)
            self.speedy = random.randrange(1, 4)
            self.speedx = random.randrange(-3, 3)


# 子弹类
class Bullet(pygame.sprite.Sprite):
    def __init__(self, x, y):
        super().__init__()
        self.image = load_image("bullet", 10, 20)
        self.rect = self.image.get_rect()
        self.rect.centerx = x
        self.rect.bottom = y
        self.speedy = -10

    def update(self):
        self.rect.y += self.speedy
        # 如果子弹超出屏幕顶部，删除它
        if self.rect.bottom < 0:
            self.kill()


# 爆炸类
class Explosion(pygame.sprite.Sprite):
    def __init__(self, center, size=50):
        super().__init__()
        self.size = size
        self.image = pygame.Surface((self.size, self.size))
        self.image.fill(YELLOW)
        self.rect = self.image.get_rect()
        self.rect.center = center
        self.frame = 0
        self.last_update = pygame.time.get_ticks()
        self.frame_rate = 50  # 帧率控制

    def update(self):
        now = pygame.time.get_ticks()
        if now - self.last_update > self.frame_rate:
            self.last_update = now
            self.frame += 1
            if self.frame == 9:  # 9帧后爆炸消失
                self.kill()
            else:
                # 更新爆炸颜色，模拟动画效果
                colors = [YELLOW, (255, 165, 0), RED, (139, 0, 0)]
                color_idx = min(self.frame // 2, len(colors) - 1)
                self.image.fill(colors[color_idx])


# 能量补给类
class Pow(pygame.sprite.Sprite):
    def __init__(self, center):
        super().__init__()
        self.type = random.choice(['shield', 'gun'])
        self.image = load_image("powerup", 20, 20)
        self.rect = self.image.get_rect()
        self.rect.center = center
        self.speedy = 2

    def update(self):
        self.rect.y += self.speedy
        # 如果补给超出屏幕底部，删除它
        if self.rect.top > HEIGHT:
            self.kill()


# 绘制生命值条
def draw_health(surf, x, y, pct):
    if pct < 0:
        pct = 0
    BAR_LENGTH = 100
    BAR_HEIGHT = 10
    fill = (pct / 100) * BAR_LENGTH
    outline_rect = pygame.Rect(x, y, BAR_LENGTH, BAR_HEIGHT)
    fill_rect = pygame.Rect(x, y, fill, BAR_HEIGHT)
    pygame.draw.rect(surf, GREEN, fill_rect)
    pygame.draw.rect(surf, WHITE, outline_rect, 2)


# 绘制剩余生命数
def draw_lives(surf, x, y, lives, img):
    for i in range(lives):
        img_rect = img.get_rect()
        img_rect.x = x + 30 * i
        img_rect.y = y
        surf.blit(img, img_rect)


# 显示开始界面
def show_go_screen():
    screen.fill(BLACK)
    title = font.render("太空射击游戏", True, WHITE)
    title_rect = title.get_rect(center=(WIDTH // 2, HEIGHT // 4))
    screen.blit(title, title_rect)

    instructions = small_font.render("使用左右箭头移动，空格键射击", True, WHITE)
    instructions_rect = instructions.get_rect(center=(WIDTH // 2, HEIGHT // 2))
    screen.blit(instructions, instructions_rect)

    start_text = small_font.render("按任意键开始游戏", True, WHITE)
    start_rect = start_text.get_rect(center=(WIDTH // 2, HEIGHT * 3 // 4))
    screen.blit(start_text, start_rect)

    pygame.display.flip()
    waiting = True
    while waiting:
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYUP:
                waiting = False
def show_end_screnn():
    screen.fill(BLACK)
    title = font.render("游戏结束", True, WHITE)
    title_rect = title.get_rect(center=(WIDTH // 2, HEIGHT // 4))
    screen.blit(title, title_rect)

    scorerect = small_font.render(f"你的得分是{score}", True, WHITE)
    scorerect_rect = scorerect.get_rect(center=(WIDTH // 2, HEIGHT // 2))
    screen.blit(scorerect, scorerect_rect)
    
    pygame.display.flip()
    waiting = True

    while waiting:
        clock.tick(60)
        for event in pygame.event.get():
            if event.type == pygame.K_ESCAPE:
                waiting = False
                running = False
                pygame.quit()
                sys.exit()
                print(score)  # 将结果输出到标准输出
                print(f"设置退出码为 {score}")
                sys.exit(score)


            if event.type == pygame.KEYUP:
                waiting = False
                running = False
                print(score)  # 将结果输出到标准输出
                print(f"设置退出码为 {score}")
                sys.exit(score)


# 创建玩家缩略图
player_mini_img = pygame.transform.scale(load_image("player", 25, 20), (25, 20))

# 游戏主循环
running = True
game_over = True
clock = pygame.time.Clock()
click_times = 60

while running:
    if game_over:
        show_go_screen()
        game_over = False

        # 初始化/重置游戏
        all_sprites = pygame.sprite.Group()
        enemies = pygame.sprite.Group()
        bullets = pygame.sprite.Group()
        powerups = pygame.sprite.Group()

        player = Player()
        all_sprites.add(player)

        # 创建敌人
        for i in range(8):
            enemy = Enemy()
            all_sprites.add(enemy)
            enemies.add(enemy)

        score = 0

    # 保持游戏运行速度
    clock.tick(click_times)
    if ((score % 2) == 1):
        click_times += 0.5
        click_times = min(150, click_times)

    # 处理输入事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 更新游戏
    all_sprites.update()

    # 检测子弹与敌人的碰撞
    hits = pygame.sprite.groupcollide(enemies, bullets, True, True)
    for hit in hits:
        score += 50 - hit.radius  # 敌人越小，得分越高
        # 爆炸效果
        explosion = Explosion(hit.rect.center)
        all_sprites.add(explosion)
        # 随机生成能量补给
        if random.random() < 0.1:
            pow = Pow(hit.rect.center)
            all_sprites.add(pow)
            powerups.add(pow)
        # 生成新敌人
        enemy = Enemy()
        all_sprites.add(enemy)
        enemies.add(enemy)

    # 检测玩家与敌人的碰撞
    hits = pygame.sprite.spritecollide(player, enemies, True, pygame.sprite.collide_circle)
    for hit in hits:
        player.health -= hit.radius * 2
        explosion = Explosion(hit.rect.center)
        all_sprites.add(explosion)
        enemy = Enemy()
        all_sprites.add(enemy)
        enemies.add(enemy)
        if player.health <= 0:
            death_explosion = Explosion(player.rect.center, 100)
            all_sprites.add(death_explosion)
            player.hide()
            player.lives -= 1
            player.health = 100

    # 检测玩家与能量补给的碰撞
    hits = pygame.sprite.spritecollide(player, powerups, True)
    for hit in hits:
        if hit.type == 'shield':
            player.health += random.randrange(10, 30)
            if player.health > 100:
                player.health = 100
        if hit.type == 'gun':
            player.powerup()

    # 如果玩家生命耗尽且爆炸动画结束
    if player.lives == 0 and not death_explosion.alive():
        show_end_screnn()

    # 渲染游戏
    screen.fill(BLACK)
    all_sprites.draw(screen)

    # 绘制分数
    score_text = font.render(f"分数: {score}", True, WHITE)
    screen.blit(score_text, (10, 10))

    # 绘制生命值
    draw_health(screen, 10, 50, player.health)

    # 绘制剩余生命
    draw_lives(screen, WIDTH - 100, 15, player.lives, player_mini_img)

    # 刷新屏幕
    pygame.display.flip()

pygame.quit()
sys.exit()