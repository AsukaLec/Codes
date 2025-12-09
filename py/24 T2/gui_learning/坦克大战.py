import pygame
import sys

# 初始化 Pygame
pygame.init()

# 设置游戏窗口
screen = pygame.display.set_mode((800, 600))
pygame.display.set_caption("坦克大战")

# 定义颜色
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

# 坦克类
class Tank(pygame.sprite.Sprite):
    def __init__(self, color, x, y):
        super().__init__()
        self.image = pygame.Surface((50, 50))
        self.image.fill(color)
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = y
        self.health = 100
        self.direction = 'right'  # 初始方向

    def move(self, direction):
        # 边界检查，确保坦克不移出屏幕
        if direction == 'left' and self.rect.x > 0:
            self.rect.x -= 5
            self.direction = 'left'
        elif direction == 'right' and self.rect.x < 750:  # 800 - 50
            self.rect.x += 5
            self.direction = 'right'
        elif direction == 'up' and self.rect.y > 0:
            self.rect.y -= 5
            self.direction = 'up'
        elif direction == 'down' and self.rect.y < 550:  # 600 - 50
            self.rect.y += 5
            self.direction = 'down'

    def shoot(self):
        # 创建并返回一个子弹对象
        bullet = Bullet(self.rect.centerx, self.rect.centery, self.direction, self)
        return bullet

    def draw_health(self, screen):
        # 绘制生命条
        health_bar_width = 50
        health_bar_height = 5
        fill = (self.health / 100) * health_bar_width
        outline_rect = pygame.Rect(self.rect.x, self.rect.y - 10, health_bar_width, health_bar_height)
        fill_rect = pygame.Rect(self.rect.x, self.rect.y - 10, fill, health_bar_height)
        pygame.draw.rect(screen, GREEN, fill_rect)
        pygame.draw.rect(screen, WHITE, outline_rect, 2)

# 子弹类
class Bullet(pygame.sprite.Sprite):
    def __init__(self, x, y, direction, tank):
        super().__init__()
        self.image = pygame.Surface((10, 10))
        self.image.fill(RED)
        self.rect = self.image.get_rect()
        self.rect.centerx = x
        self.rect.centery = y
        self.direction = direction
        self.speed = 10
        self.tank = tank  # 记录发射子弹的坦克

    def update(self):
        # 根据方向移动子弹
        if self.direction == 'left':
            self.rect.x -= self.speed
        elif self.direction == 'right':
            self.rect.x += self.speed
        elif self.direction == 'up':
            self.rect.y -= self.speed
        elif self.direction == 'down':
            self.rect.y += self.speed

        # 如果子弹超出屏幕，移除它
        if self.rect.x < 0 or self.rect.x > 800 or self.rect.y < 0 or self.rect.y > 600:
            self.kill()

# 创建坦克实例
tank1 = Tank(GREEN, 100, 300)  # 绿色坦克在左侧
tank2 = Tank(BLUE, 700, 300)   # 蓝色坦克在右侧

# 创建精灵组
all_sprites = pygame.sprite.Group()
tanks = pygame.sprite.Group()
bullets = pygame.sprite.Group()

all_sprites.add(tank1, tank2)
tanks.add(tank1, tank2)

# 设置字体，用于显示胜利信息
font = pygame.font.Font(None, 36)

# 主游戏循环
running = True
clock = pygame.time.Clock()

while running:
    # 处理事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            # 坦克1控制：方向键移动，空格键射击
            if event.key == pygame.K_LEFT:
                tank1.move('left')
            elif event.key == pygame.K_RIGHT:
                tank1.move('right')
            elif event.key == pygame.K_UP:
                tank1.move('up')
            elif event.key == pygame.K_DOWN:
                tank1.move('down')
            elif event.key == pygame.K_SPACE:
                bullet = tank1.shoot()
                all_sprites.add(bullet)
                bullets.add(bullet)
            # 坦克2控制：WASD移动，回车键射击
            elif event.key == pygame.K_a:
                tank2.move('left')
            elif event.key == pygame.K_d:
                tank2.move('right')
            elif event.key == pygame.K_w:
                tank2.move('up')
            elif event.key == pygame.K_s:
                tank2.move('down')
            elif event.key == pygame.K_RETURN:
                bullet = tank2.shoot()
                all_sprites.add(bullet)
                bullets.add(bullet)

    # 更新子弹位置
    bullets.update()

    # 碰撞检测
    for bullet in bullets:
        hit_tanks = pygame.sprite.spritecollide(bullet, tanks, False)
        for tank in hit_tanks:
            if tank != bullet.tank:  # 子弹不会伤害自己的坦克
                tank.health -= 10
                bullet.kill()
                if tank.health <= 0:
                    tank.kill()

    # 检查胜利条件
    if not tank1.alive():
        text = font.render("TANK 2 WINS !", True, BLACK)
        screen.blit(text, (350, 300))
        pygame.display.flip()
        pygame.time.wait(2000)  # 显示胜利信息2秒
        running = False
    elif not tank2.alive():
        text = font.render("TANK 1 WINS !", True, BLACK)
        screen.blit(text, (350, 300))
        pygame.display.flip()
        pygame.time.wait(2000)  # 显示胜利信息2秒
        running = False

    # 绘制画面
    screen.fill(WHITE)  # 填充白色背景
    all_sprites.draw(screen)  # 绘制所有精灵
    for tank in tanks:
        tank.draw_health(screen)  # 绘制生命条
    pygame.display.flip()  # 更新屏幕

    # 控制帧率
    clock.tick(60)

# 退出 Pygame
pygame.quit()
# 退出游戏
result = random.randint(1,1000)  # 随机生成一个结果

print(result)  # 将结果输出到标准输出
print(f"设置退出码为 {result}")

sys.exit(result)

