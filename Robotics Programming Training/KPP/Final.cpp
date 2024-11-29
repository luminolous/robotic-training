#include <iostream>
#include <vector>
#include <string>

class Map {
private:
    std::vector<std::vector<char>> grid;
    int rows, cols;

public:
    Map(const std::vector<std::string>& input_grid) 
        : rows(input_grid.size()), cols(input_grid[0].length()) {
        grid.resize(rows, std::vector<char>(cols));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                grid[i][j] = input_grid[i][j];
            }
        }
    }

    std::pair<int, int> get_start() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 'S') {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    void update_cell(int x, int y, char value) {
        grid[x][y] = value;
    }

    int get_rows() const { return rows; }
    int get_cols() const { return cols; }
    char get_cell(int x, int y) const { return grid[x][y]; }
};

class Robot {
private:
    int x, y;
    int time;
    int speed;
    bool can_break_wall;

public:
    Robot(int start_x, int start_y) 
        : x(start_x), y(start_y), time(0), speed(1), can_break_wall(false) {}

    std::string move(char direction, Map& map_obj) {
        int dx = 0, dy = 0;
        if (direction == 'D') dx = 1;
        else if (direction == 'U') dx = -1;
        else if (direction == 'R') dy = 1;
        else if (direction == 'L') dy = -1;

        int new_x = x + dx, new_y = y + dy;

        if (0 <= new_x && new_x < map_obj.get_rows() && 0 <= new_y && new_y < map_obj.get_cols()) {
            char cell = map_obj.get_cell(new_x, new_y);
            if (cell != 'x' || can_break_wall) {
                std::string result = handle_cell(cell);

                x = new_x;
                y = new_y;

                time += (speed == 1) ? 2 : 1;

                if (cell == 'O') time *= 2;
                else if (cell == 'E') speed = 2;
                else if (cell == 'M') can_break_wall = true;
                map_obj.update_cell(new_x, new_y, '.');

                return result;
            } else {
                return "Robot nabrak, silahkan diperbaiki";
            }
        }
        return "Robot mencoba keluar dari peta";
    }

    std::string handle_cell(char cell) {
        switch (cell) {
            case 'M': return "Bertemu dengan mekanik, siap membasmi rintangan";
            case 'E': return "Bertemu dengan electrical, kecepatan roda naik menjadi 200%";
            case 'P': return "Hi programmer bau bawang :3";
            case 'O': return "Bertemu dengan official, diajak ngonten bareng";
            case 'F': return "Robot berhasil mencapai tujuan";
            default: return "";
        }
    }

    int get_time() const { return time; }
};

void simulate_robot(Map& map_obj, const std::string& movements) {
    auto start = map_obj.get_start();
    Robot robot(start.first, start.second);
    bool reached_goal = false;

    for (char move : movements) {
        if (move == 'D' || move == 'R' || move == 'U' || move == 'L') {
            std::string result = robot.move(move, map_obj);
            if (!result.empty()) {
                std::cout << result << std::endl;
            }
            if (result == "Robot berhasil mencapai tujuan") {
                reached_goal = true;
                break;
            }
        }
    }

    if (!reached_goal) {
        std::cout << "Robot gagal dalam mencapai tujuan :(" << std::endl;
    }

    std::cout << "Robot telah berjalan selama " << robot.get_time() << " menit" << std::endl;
}

int main() {
    int M, N;
    std::cin >> M >> N;
    std::cin.ignore();  // Consume newline

    std::vector<std::string> grid(M);
    for (int i = 0; i < M; ++i) {
        std::getline(std::cin, grid[i]);
    }

    Map map_obj(grid);

    int P;
    std::cin >> P;
    std::cin.ignore();  // Consume newline

    std::string movements;
    std::getline(std::cin, movements);

    simulate_robot(map_obj, movements);

    return 0;
}