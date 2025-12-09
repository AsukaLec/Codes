import pygame
import sys
import random

# 初始化pygame
pygame.init()

# 设置中文字体
pygame.font.init()
font_names = ["SimHei", "WenQuanYi Micro Hei", "Heiti TC", "Arial Unicode MS"]
font = pygame.font.SysFont(font_names, 30)
small_font = pygame.font.SysFont(font_names, 20)

# 游戏窗口设置
WIDTH, HEIGHT = 800, 450
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("冰火人冒险")

# 颜色定义
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)
FIRE_COLOR = (255, 69, 0)
ICE_COLOR = (30, 144, 255)
PLATFORM_COLOR = (34, 139, 34)
FIRE_PLATFORM_COLOR = (255, 69, 0)
ICE_PLATFORM_COLOR = (30, 144, 255)
OBSTACLE_COLOR = (139, 69, 19)
GOAL_COLOR = (255, 255, 0)
INVINCIBLE_COLOR = (255, 215, 0)  # 金色表示无敌状态

# 游戏常量
INVINCIBLE_TIME = 180  # 无敌时间（帧）
SPAWN_ANIMATION_TIME = 60  # 出生动画时间（帧）

# 玩家类
class Player:
    def __init__(self, x, y, width, height, color, platform_color, goal_color, controls):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
        self.platform_color = platform_color
        self.goal_color = goal_color
        self.controls = controls
        self.speed = 5
        self.jump_power = 15
        self.velocity_y = 0
        self.is_jumping = False
        self.score = 0
        self.is_invincible = False  # 是否处于无敌状态
        self.invincible_timer = 0  # 无敌计时器
        self.is_spawning = True  # 是否正在出生动画中
        self.spawn_timer = 0  # 出生动画计时器
        
    def update(self, platforms, obstacles, goals):
        if self.is_spawning:
            self.spawn_timer += 1
            if self.spawn_timer >= SPAWN_ANIMATION_TIME:
                self.is_spawning = False
            return  # 出生动画期间不更新位置
        
        # 无敌状态计时
        if self.is_invincible:
            self.invincible_timer -= 1
            if self.invincible_timer <= 0:
                self.is_invincible = False
        
        # 应用重力
        self.velocity_y += 0.7
        
        # 处理输入
        keys = pygame.key.get_pressed()
        if keys[self.controls["left"]]:
            self.x -= self.speed
        if keys[self.controls["right"]]:
            self.x += self.speed
        if keys[self.controls["up"]] and not self.is_jumping:
            self.velocity_y = -self.jump_power
            self.is_jumping = True
        
        # 应用垂直速度
        old_y = self.y
        self.y += self.velocity_y
        
        # 检查平台碰撞
        self.is_jumping = True
        on_platform = False
        
        for platform in platforms:
            # 检查玩家是否站在平台上
            if (self.x + self.width > platform.x and
                self.x < platform.x + platform.width and
                old_y + self.height <= platform.y and
                self.y + self.height >= platform.y and
                self.velocity_y > 0 and
                (platform.color == self.platform_color or platform.color == PLATFORM_COLOR)):
                
                self.y = platform.y - self.height
                self.velocity_y = 0
                self.is_jumping = False
                on_platform = True
                
            # 检查玩家是否碰到平台底部
            if (self.x + self.width > platform.x and
                self.x < platform.x + platform.width and
                old_y <= platform.y + platform.height and
                self.y >= platform.y + platform.height and
                self.velocity_y < 0):
                
                self.y = platform.y + platform.height
                self.velocity_y = 0
                
            # 检查玩家是否碰到平台左侧
            if (self.y + self.height > platform.y and
                self.y < platform.y + platform.height and
                self.x + self.width >= platform.x and
                self.x + self.width <= platform.x + 10 and
                self.velocity_y >= 0):
                
                self.x = platform.x - self.width
                
            # 检查玩家是否碰到平台右侧
            if (self.y + self.height > platform.y and
                self.y < platform.y + platform.height and
                self.x <= platform.x + platform.width and
                self.x >= platform.x + platform.width - 10 and
                self.velocity_y >= 0):
                
                self.x = platform.x + platform.width
        
        # 如果不在任何平台上，确保is_jumping为True
        if not on_platform:
            self.is_jumping = True
        
        # 边界检查
        if self.x < 0:
            self.x = 0
        if self.x + self.width > WIDTH:
            self.x = WIDTH - self.width
        if self.y < 0:
            self.y = 0
        if self.y + self.height > HEIGHT:
            # 玩家掉出屏幕，重置位置
            self.reset_position()
        
        # 检查障碍物碰撞（无敌状态下忽略碰撞）
        if not self.is_invincible:
            for obstacle in obstacles:
                if (self.x < obstacle.x + obstacle.width and
                    self.x + self.width > obstacle.x and
                    self.y < obstacle.y + obstacle.height and
                    self.y + self.height > obstacle.y):
                    self.reset_position()
        
        # 检查目标点碰撞
        for goal in goals:
            if goal.player == self and pygame.Rect(self.x, self.y, self.width, self.height).colliderect(
                pygame.Rect(goal.x, goal.y, goal.width, goal.height)):
                self.score = 1
                goal.reached = True  # 只设置已达成标志，不修改颜色
    
    def reset_position(self):
        # 重置为随机出生点
        spawn_points = [
            (50, 350),   # 火人默认出生点
            (200, 350),  # 冰人默认出生点
            (350, 300),  # 中间平台
            (500, 250)   # 高处平台
        ]
        
        if self.color == FIRE_COLOR:
            self.x, self.y = random.choice(spawn_points)
        else:
            # 确保冰人和火人不出生在同一位置
            possible_points = [p for p in spawn_points if p[0] != self.x or p[1] != self.y]
            self.x, self.y = random.choice(possible_points)
            
        self.velocity_y = 0
        self.is_jumping = False
        self.is_invincible = True  # 重置后获得无敌状态
        self.invincible_timer = INVINCIBLE_TIME
        self.is_spawning = True
        self.spawn_timer = 0
    
    def draw(self, screen):
        # 出生动画效果
        if self.is_spawning:
            scale = 1.0 - (self.spawn_timer / SPAWN_ANIMATION_TIME) * 0.3
            spawn_width = int(self.width * scale)
            spawn_height = int(self.height * scale)
            spawn_x = self.x + (self.width - spawn_width) // 2
            spawn_y = self.y + (self.height - spawn_height) // 2
            
            # 闪烁效果
            if self.spawn_timer % 10 < 5:
                draw_color = self.color
            else:
                draw_color = WHITE
                
            # 绘制缩小的玩家
            pygame.draw.rect(screen, draw_color, (spawn_x, spawn_y, spawn_width, spawn_height))
            pygame.draw.rect(screen, BLACK, (spawn_x, spawn_y, spawn_width, spawn_height), 2)
            
            # 绘制出生光圈 - 确保透明度值在有效范围内
            glow_radius = int(spawn_width * 1.5)
            glow_surface = pygame.Surface((glow_radius * 2, glow_radius * 2), pygame.SRCALPHA)
            alpha = max(0, min(255, int(100 * (1 - self.spawn_timer / SPAWN_ANIMATION_TIME))))
            pygame.draw.circle(
                glow_surface, 
                (*self.color, alpha), 
                (glow_radius, glow_radius), 
                glow_radius
            )
            screen.blit(glow_surface, (spawn_x + spawn_width//2 - glow_radius, spawn_y + spawn_height//2 - glow_radius), special_flags=pygame.BLEND_ADD)
            
            return
        
        # 无敌状态闪烁效果
        if self.is_invincible and self.invincible_timer % 10 < 5:
            draw_color = INVINCIBLE_COLOR
        else:
            draw_color = self.color
        
        # 绘制玩家身体
        pygame.draw.rect(screen, draw_color, (self.x, self.y, self.width, self.height))
        
        # 绘制玩家头部
        head_color = (255, 99, 71) if draw_color == FIRE_COLOR else (65, 105, 225)
        pygame.draw.rect(screen, head_color, (self.x + 5, self.y - 10, 20, 10))
        
        # 添加玩家边框
        pygame.draw.rect(screen, BLACK, (self.x, self.y, self.width, self.height), 2)
        pygame.draw.rect(screen, BLACK, (self.x + 5, self.y - 10, 20, 10), 2)
        
        # 添加玩家眼睛
        pygame.draw.rect(screen, WHITE, (self.x + 10, self.y - 7, 3, 3))
        pygame.draw.rect(screen, WHITE, (self.x + 17, self.y - 7, 3, 3))
        
        # 显示无敌状态剩余时间
        if self.is_invincible:
            invincible_text = small_font.render(f"无敌: {self.invincible_timer//60 + 1}", True, INVINCIBLE_COLOR)
            screen.blit(invincible_text, (self.x, self.y - 25))

# 平台类
class Platform:
    def __init__(self, x, y, width, height, color):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
    
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))
        pygame.draw.rect(screen, BLACK, (self.x, self.y, self.width, self.height), 2)

# 障碍物类
class Obstacle:
    def __init__(self, x, y, width, height, color):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
    
    def draw(self, screen):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))
        pygame.draw.rect(screen, BLACK, (self.x, self.y, self.width, self.height), 2)

# 目标点类 - 修复分数增加时的颜色设置问题
class Goal:
    def __init__(self, x, y, width, height, color, player):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.base_color = color  # 存储原始颜色(RGB)
        self.color = color       # 当前颜色
        self.player = player
        self.reached = False     # 是否已达成
    
    def draw(self, screen):
        # 绘制圆形目标点
        draw_color = self.color
        
        # 如果已达成，使用特殊的半透明效果
        if self.reached:
            # 创建半透明表面绘制已达成的目标
            goal_surface = pygame.Surface((self.width, self.height), pygame.SRCALPHA)
            pygame.draw.circle(goal_surface, (*draw_color, 128), (self.width//2, self.height//2), self.width//2)
            pygame.draw.circle(goal_surface, (*BLACK, 255), (self.width//2, self.height//2), self.width//2, 2)
            screen.blit(goal_surface, (self.x, self.y))
        else:
            # 正常绘制
            pygame.draw.circle(screen, draw_color, (self.x + self.width//2, self.y + self.height//2), self.width//2)
            pygame.draw.circle(screen, BLACK, (self.x + self.width//2, self.y + self.height//2), self.width//2, 2)
        
        # 目标点发光效果
        glow_surface = pygame.Surface((self.width * 2, self.height * 2), pygame.SRCALPHA)
        pygame.draw.circle(
            glow_surface, 
            (*draw_color, 128),  # 使用固定的半透明度值
            (self.width, self.height), 
            self.width
        )
        screen.blit(glow_surface, (self.x - self.width//2, self.y - self.height//2), special_flags=pygame.BLEND_ADD)

# 创建玩家 - 调整出生点位置，增加间距
fire_player = Player(
    x=50, y=350, width=30, height=40, 
    color=FIRE_COLOR, 
    platform_color=FIRE_PLATFORM_COLOR,
    goal_color=FIRE_COLOR,
    controls={"up": pygame.K_w, "left": pygame.K_a, "right": pygame.K_d}
)

ice_player = Player(
    x=200, y=350, width=30, height=40, 
    color=ICE_COLOR, 
    platform_color=ICE_PLATFORM_COLOR,
    goal_color=ICE_COLOR,
    controls={"up": pygame.K_UP, "left": pygame.K_LEFT, "right": pygame.K_RIGHT}
)

# 创建平台
platforms = [
    Platform(0, 400, 800, 50, PLATFORM_COLOR),  # 地面
    Platform(150, 350, 100, 10, FIRE_PLATFORM_COLOR),  # 火人平台
    Platform(300, 300, 100, 10, ICE_PLATFORM_COLOR),  # 冰人平台
    Platform(450, 250, 100, 10, FIRE_PLATFORM_COLOR),  # 火人平台
    Platform(600, 200, 100, 10, ICE_PLATFORM_COLOR),  # 冰人平台
    
    # 出生平台提示
    Platform(30, 360, 70, 5, FIRE_PLATFORM_COLOR),  # 火人出生提示
    Platform(180, 360, 70, 5, ICE_PLATFORM_COLOR),  # 冰人出生提示
]

# 创建障碍物
obstacles = [
    Obstacle(200, 380, 20, 20, OBSTACLE_COLOR),
    Obstacle(350, 330, 20, 20, OBSTACLE_COLOR),
    Obstacle(500, 280, 20, 20, OBSTACLE_COLOR),
    Obstacle(650, 230, 20, 20, OBSTACLE_COLOR),
]

# 创建目标点
goals = [
    Goal(700, 180, 30, 30, FIRE_COLOR, fire_player),
    Goal(740, 180, 30, 30, ICE_COLOR, ice_player)
]

# 游戏状态
game_state = "ready"  # ready, running, paused, gameover

# 游戏主循环
clock = pygame.time.Clock()
running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
            if event.key == pygame.K_SPACE and game_state == "ready":
                game_state = "running"
            elif event.key == pygame.K_p and game_state == "running":
                game_state = "paused"
            elif event.key == pygame.K_r and (game_state == "paused" or game_state == "gameover"):
                # 重置游戏
                fire_player.reset_position()
                ice_player.reset_position()
                fire_player.score = 0
                ice_player.score = 0
                for goal in goals:
                    goal.color = goal.base_color
                    goal.reached = False
                game_state = "running"
    
    # 填充背景 - 添加渐变效果
    gradient_surface = pygame.Surface((WIDTH, HEIGHT))
    for y in range(HEIGHT):
        color_value = max(0, 10 - y // 45)  # 渐变效果
        pygame.draw.line(gradient_surface, (color_value, color_value, 40), (0, y), (WIDTH, y))
    screen.blit(gradient_surface, (0, 0))
    
    # 绘制游戏元素
    for platform in platforms:
        platform.draw(screen)
    
    for obstacle in obstacles:
        obstacle.draw(screen)
    
    for goal in goals:
        goal.draw(screen)
    
    # 更新和绘制玩家
    if game_state == "running":
        fire_player.update(platforms, obstacles, goals)
        ice_player.update(platforms, obstacles, goals)
    
    fire_player.draw(screen)
    ice_player.draw(screen)
    
    # 显示分数
    fire_score_text = font.render(f"火人分数: {fire_player.score}", True, FIRE_COLOR)
    ice_score_text = font.render(f"冰人分数: {ice_player.score}", True, ICE_COLOR)
    screen.blit(fire_score_text, (10, 10))
    screen.blit(ice_score_text, (10, 50))
    
    # 显示控制提示
    controls_text = small_font.render("火人: WASD | 冰人: 方向键 | 空格: 开始 | P: 暂停 | R: 重置", True, WHITE)
    screen.blit(controls_text, (WIDTH//2 - controls_text.get_width()//2, 10))
    
    # 显示游戏状态
    if game_state == "ready":
        state_text = font.render("按空格键开始游戏", True, WHITE)
        screen.blit(state_text, (WIDTH//2 - state_text.get_width()//2, HEIGHT//2 - 50))
    elif game_state == "paused":
        state_text = font.render("游戏已暂停，按R键重新开始", True, WHITE)
        screen.blit(state_text, (WIDTH//2 - state_text.get_width()//2, HEIGHT//2 - 50))
    elif game_state == "gameover":
        if fire_player.score == 1 and ice_player.score == 1:
            state_text = font.render("恭喜！你完成了关卡！按R键重新开始", True, GOAL_COLOR)
            screen.blit(state_text, (WIDTH//2 - state_text.get_width()//2, HEIGHT//2 - 50))
    
    # 检查游戏是否结束
    if fire_player.score == 1 and ice_player.score == 1:
        game_state = "gameover"
    

    
    # 更新显示
    pygame.display.flip()
    
    # 控制帧率
    clock.tick(60)

# 退出游戏
result = random.randint(1,1000)  # 随机生成一个结果

print(result)  # 将结果输出到标准输出
print(f"设置退出码为 {result}")

sys.exit(result)



