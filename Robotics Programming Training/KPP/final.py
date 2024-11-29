class Robot:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.time = 0
        self.speed = 1
        self.can_break_wall = False
    
    def move(self, direction, map_obj):
        dx, dy = 0, 0
        if direction == 'D':
            dx = 1
        elif direction == 'U':
            dx = -1
        elif direction == 'R':
            dy = 1
        elif direction == 'L':
            dy = -1
        
        new_x, new_y = self.x + dx, self.y + dy
        
        if 0 <= new_x < map_obj.rows and 0 <= new_y < map_obj.cols:
            cell = map_obj.grid[new_x][new_y]
            if cell != 'x' or self.can_break_wall:
                result = self.handle_cell(cell)
                
                # Update posisi robot
                self.x, self.y = new_x, new_y
                
                # Update waktu berdasarkan kecepatan
                if self.speed == 1:
                    self.time += 2 # 2 menit per pindahan untuk speed = 1
                else:
                    self.time += 1
                
                if cell == 'O':
                    self.time *= 2
                elif cell == 'E':
                    self.speed = 2
                elif cell == 'M':
                    self.can_break_wall = True
                map_obj.update_cell(new_x, new_y, '.')

                return result
            else:
                return "Robot nabrak, silahkan diperbaiki"
        
        return "Robot mencoba keluar dari peta"

    def handle_cell(self, cell):
        if cell == 'M':
            return "Bertemu dengan mekanik, siap membasmi rintangan"
        elif cell == 'E':
            return "Bertemu dengan electrical, kecepatan roda naik menjadi 200%"
        elif cell == 'P':
            return "Hi programmer bau bawang :3"
        elif cell == 'O':
            return "Bertemu dengan official, diajak ngonten bareng"
        elif cell == 'F':
            return "Robot berhasil mencapai tujuan"
        return ""

class Map:
    def __init__(self, grid):
        self.grid = [list(row) for row in grid]
        self.rows = len(grid)
        self.cols = len(grid[0])

    def get_start(self):
        for i in range(self.rows):
            for j in range(self.cols):
                if self.grid[i][j] == 'S':
                    return (i, j)
        return None

    def update_cell(self, x, y, value):
        self.grid[x][y] = value

def simulate_robot(map_obj, movements):
    start = map_obj.get_start()
    robot = Robot(start[0], start[1])
    reached_goal = False
    for move in movements:
       if move in ['D', 'R', 'U', 'L']:
            result = robot.move(move, map_obj)
            if result:
                print(result)
            if result == "Robot berhasil mencapai tujuan":
                reached_goal = True
                break
    if not reached_goal:
        print("Robot gagal dalam mencapai tujuan :(")
    
    print(f"Robot telah berjalan selama {int(robot.time)} menit")

# Main execution
M, N = map(int, input().split())
grid = [input().strip() for _ in range(M)]
map_obj = Map(grid)
P = int(input())
movements = input().strip()
simulate_robot(map_obj, movements)

    # ... (rest of the Robot class remains the same)

# ... (rest of the code remains the same)
