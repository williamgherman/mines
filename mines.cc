/*
 * Minesweeper
 * Based on minesweeper for windows xp
 *
 * William Gherman
 * 2020-03-16
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <random>

int copy_field(std::map<std::pair<int, int>, int> &f1,
                  std::map<std::pair<int, int>, int> &f2, const int &x,
                  const int &y)
{

    return f2.find(std::make_pair(y, x))->second =
        f1.find(std::make_pair(y, x))->second;

}

void open_adjacent(std::map<std::pair<int, int>, int> &f1,
                   std::map<std::pair<int, int>, int> &f2, const int &x,
                   const int &y, const int &size)
{
    int selected, tempx, tempy;

    if (x > 0) {
        if (y > 0) {
            tempx = x - 1; tempy = y - 1;
            if (f2[std::make_pair(tempy,tempx)] == 10) {
                selected = copy_field(f1, f2, tempx, tempy);
                if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
            }
        }
        tempx = x - 1; tempy = y;
        if (f2[std::make_pair(tempy,tempx)] == 10) {
            selected = copy_field(f1, f2, tempx, tempy);
            if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
        }
        if (y < size) {
            tempx = x - 1; tempy = y + 1;
            if (f2[std::make_pair(tempy,tempx)] == 10) {
                selected = copy_field(f1, f2, tempx, tempy);
                if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
            }
        }
    }
    if (y > 0) {
        tempx = x; tempy = y - 1;
        if (f2[std::make_pair(tempy,tempx)] == 10) {
            selected = copy_field(f1, f2, tempx, tempy);
            if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
        }
    }
    if (y < size) {
        tempx = x; tempy = y + 1;
        if (f2[std::make_pair(tempy,tempx)] == 10) {
            selected = copy_field(f1, f2, tempx, tempy);
            if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
        }
    }
    if (x < size) {
        if (y > 0) {
            tempx = x + 1; tempy = y - 1;
            if (f2[std::make_pair(tempy,tempx)] == 10) {
                selected = copy_field(f1, f2, tempx, tempy);
                if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
            }
        }
        tempx = x + 1; tempy = y;
        if (f2[std::make_pair(tempy,tempx)] == 10) {
            selected = copy_field(f1, f2, tempx, tempy);
            if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
        }
        if (y < size) {
            tempx = x + 1; tempy = y + 1;
            if (f2[std::make_pair(tempy,tempx)] == 10) {
                selected = copy_field(f1, f2, tempx, tempy);
                if (selected == 0) open_adjacent(f1, f2, tempx, tempy, size);
            }
        }
    }
}

void print_field(std::map<std::pair<int, int>, int> &field, const int &size)
{

    char curr;
    char x_axis = 'a';
    int y_axis = size;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            curr = '0' + (field[std::make_pair(i,j)]);
            std::string result;
            switch (curr) {
                case '9':
                    result = "\033[31;5mX\033[0m";
                    break;
                case '0':
                    result = " ";
                    break;
                case '1':
                    result = "\033[94m1\033[0m";
                    break;
                case '2':
                    result = "\033[92m2\033[0m";
                    break;
                case '3':
                    result = "\033[91m3\033[0m";
                    break;
                case '4':
                    result = "\033[34m4\033[0m";
                    break;
                case '5':
                    result = "\033[31m5\033[0m";
                    break;
                case '6':
                    result = "\033[36m6\033[0m";
                    break;
                case '7':
                    result = "\033[35m7\033[0m";
                    break;
                case '8':
                    result = "\033[33m8\033[0m";
                    break;
                case ':':
                    result = ".";
                    break;
                default:
                    break;
            }
            std::cout << result;
        }
        std::cout << "  " << y_axis-- << std::endl;
    }
    std::cout << std::endl;
    while (x_axis < 'a' + size)
        std::cout << x_axis++;
    std::cout << "\n" << std::endl;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<std::pair<int, int>, int> field, visible_field;
    int difficulty, size, num_mines, mines_nearby;

    std::cout << "Enter difficulty:\n\n\t[1] easy\n\t[2] medium\n\t[3] hard"
              << std::endl;
    std::cin >> difficulty;
    if (difficulty < 0 || difficulty > 3) {
        std::cerr << "difficulty must be between 0 and 3" << std::endl;
        return -1;
    }

    if (difficulty == 1) {
        size = 9;
        num_mines = 10;
    }
    if (difficulty == 2) {
        size = 13;
        num_mines = 25;
    }
    if (difficulty == 3) {
        size = 26;
        num_mines = 99;
    }
    std::uniform_int_distribution<> dis(0, size -1);

    while (num_mines > 0) {
        field.insert(std::make_pair(std::make_pair(dis(gen), dis(gen)), 9));
        --num_mines;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j, mines_nearby = 0) {
            if (field[std::make_pair(i, j)] == 9) continue;

            if (i < size) {
                if (field[std::make_pair(i+1, j)] == 9)
                    ++mines_nearby;
                if (j < size && field[std::make_pair(i+1, j+1)] == 9)
                    ++mines_nearby;
                if (j > 0 && field[std::make_pair(i+1, j-1)] == 9)
                    ++mines_nearby;
            }

            if (j < size && field[std::make_pair(i, j+1)] == 9) ++mines_nearby;
            if (j > 0 && field[std::make_pair(i, j-1)] == 9) ++mines_nearby;

            if (i > 0) {
                if (field[std::make_pair(i-1, j)] == 9) ++mines_nearby;
                if (j < size && field[std::make_pair(i-1, j+1)] == 9)
                    ++mines_nearby;
                if (j > 0 && field[std::make_pair(i-1, j-1)] == 9)
                    ++mines_nearby;
            }
            auto it = field.find(std::make_pair(i,j));
            if (it != field.end())
                it->second = mines_nearby;
            else
                field.insert(std::make_pair(std::make_pair(i,j), mines_nearby));
        }
    }

    // setup visible_field
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            visible_field.insert(std::make_pair(std::make_pair(i,j), 10));

    char x_char;
    int x_coord, y_coord, selected_coord;

    while (true) {
        print_field(visible_field, size);
        std::cout << "Enter coordinate (ex. g6): " << std::flush;
        std::cin >> x_char >> y_coord;
        x_coord = x_char - 'a';
        y_coord = size - y_coord;
        std::cout << x_coord << ", " << y_coord << std::endl;
        if (x_coord > size-1 || x_coord < 0 || y_coord > size-1 || y_coord < 0) {
            std::cerr << "out of bounds" << std::endl;
            continue;
        }
        selected_coord = copy_field(field, visible_field, x_coord, y_coord);
        if (selected_coord == 9) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    if (field.find(std::make_pair(i,j))->second == 9)
                        visible_field[std::make_pair(i,j)] = 9;
                }
            }
            print_field(visible_field, size);
            std::cout << "You Lose!" << std::endl;
            break;
        }
        if (selected_coord == 0)
            open_adjacent(field, visible_field, x_coord, y_coord, size-1);
    }
}
