import pygame
import random
import sys

# 初始化游戏
pygame.init()
WIDTH, HEIGHT = 400, 500
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("2048")
font = pygame.font.SysFont("Arial", 24)
clock = pygame.time.Clock()

# 颜色定义
COLORS = {
    0: (205, 193, 180),
    2: (238, 228, 218),
    4: (237, 224, 200),
    8: (242, 177, 121),
    16: (245, 149, 99),
    32: (246, 124, 95),
    64: (246, 94, 59),
    128: (237, 207, 114),
    256: (237, 204, 97),
    512: (237, 200, 80),
    1024: (237, 197, 63),
    2048: (237, 194, 46)
}

# 游戏逻辑核心
class Game2048:
    def __init__(self):
        self.grid = [[0]*4 for _ in range(4)]
        self.add_new_tile()
        self.add_new_tile()
        self.score = 0

    def add_new_tile(self):
        empty_cells = [(i,j) for i in range(4) for j in range(4) if self.grid[i][j] == 0]
        if empty_cells:
            i, j = random.choice(empty_cells)
            self.grid[i][j] = 2 if random.random() < 0.9 else 4

    def move(self, direction):
        # direction: 0-left 1-up 2-right 3-down
        original = [row[:] for row in self.grid]
        
        if direction in [2,3]:
            self.grid = [row[::-1] for row in self.grid]
        
        if direction in [1,3]:
            self.grid = list(map(list, zip(*self.grid)))
        
        for i in range(4):
            self.grid[i] = self.merge_row(self.grid[i])
        
        if direction in [1,3]:
            self.grid = list(map(list, zip(*self.grid)))
        
        if direction in [2,3]:
            self.grid = [row[::-1] for row in self.grid]
        
        if original != self.grid:
            self.add_new_tile()
            return True
        return False

    def merge_row(self, row):
        # 合并行
        row = [num for num in row if num != 0]
        for i in range(len(row)-1):
            if row[i] == row[i+1]:
                row[i] *= 2
                self.score += row[i]
                row.pop(i+1)
                row.append(0)
        return row + [0]*(4 - len(row))

    def game_over(self):
        for row in self.grid:
            if 0 in row:
                return False
        for i in range(4):
            for j in range(4):
                if j < 3 and self.grid[i][j] == self.grid[i][j+1]:
                    return False
                if i < 3 and self.grid[i][j] == self.grid[i+1][j]:
                    return False
        return True

# 绘制界面
def draw_game(game):
    screen.fill((187, 173, 160))
    
    # 绘制分数
    text = font.render(f"Score: {game.score}", True, (255, 255, 255))
    screen.blit(text, (20, 20))
    
    # 绘制网格
    grid_size = 360
    cell_size = grid_size // 4
    start_x = (WIDTH - grid_size) // 2
    start_y = 100
    
    for i in range(4):
        for j in range(4):
            value = game.grid[i][j]
            color = COLORS.get(value, (60, 58, 50))
            rect = pygame.Rect(start_x + j*cell_size +5, start_y + i*cell_size +5, 
                            cell_size-10, cell_size-10)
            pygame.draw.rect(screen, color, rect)
            if value != 0:
                text = font.render(str(value), True, (0,0,0) if value < 8 else (255,255,255))
                text_rect = text.get_rect(center=rect.center)
                screen.blit(text, text_rect)
    
    # 游戏结束提示
    if game.game_over():
        text = font.render("Game Over! R-retry Q-exit", True, (255, 0, 0))
        screen.blit(text, (WIDTH//2 - 120, HEIGHT - 50))
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    # 退出 Pygame
                    # 退出游戏
                    print(game.score)  # 将结果输出到标准输出
                    print(f"设置退出码为 {game.score}")

                    sys.exit(game.score)

# 主循环
def main():
    game = Game2048()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    # 退出 Pygame
                    # 退出游戏
                    print(game.score)  # 将结果输出到标准输出
                    print(f"设置退出码为 {game.score}")

                    sys.exit(game.score)

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    pygame.quit()
                    sys.exit()
                if event.key == pygame.K_r:
                    game = Game2048()
                
                moved = False
                if event.key == pygame.K_LEFT:
                    moved = game.move(0)
                elif event.key == pygame.K_UP:
                    moved = game.move(1)
                elif event.key == pygame.K_RIGHT:
                    moved = game.move(2)
                elif event.key == pygame.K_DOWN:
                    moved = game.move(3)
                
        draw_game(game)
        pygame.display.update()
        clock.tick(30)
    
    

if __name__ == "__main__":
    main()
