#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define ALIVE_CELL '*'
#define DEAD_CELL ' '

void initialize_field(char field[HEIGHT][WIDTH]);
void print_field(char field[HEIGHT][WIDTH]);
int count_neighbors(char field[HEIGHT][WIDTH], int row, int col);
void draw_menu(int speed);

int main() {
    char field[HEIGHT][WIDTH];
    int speed = 5;
    int running = 1;
    int paused = 0;
    int generation = 0;

    initialize_field(field);

    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    while (running == 1) {
        clear();
        mvprintw(0, 0, "Generation %d\n", generation++);
        draw_menu(speed);
        print_field(field);
        refresh();

        char input = getch();
        switch (input) {
            case 'p':
                paused = (paused + 1) % 2;
                if (paused == 1) {
                    mvprintw(HEIGHT + 10, 10, "Pause. Tap 'p' to continue.\n");
                    nodelay(stdscr, FALSE);
                } else {
                    system("clear");
                    nodelay(stdscr, TRUE);
                }
                break;
            case 's':
                if (speed > 1) {
                    speed -= 1;
                } else {
                    mvprintw(HEIGHT + 10, 10, "The speed is minimal already!\n");
                }
                break;
            case 'f':
                speed += 1;
                break;
            case 'q':
                mvprintw(HEIGHT + 10, 10, "Quitting...\n");
                running = 0;
                break;
            default:
                break;
        }
        draw_menu(speed);
        refresh();
        if (paused == 0) {
            usleep(1000000 / speed);
        }
    }
    endwin();
    mvprintw(HEIGHT + 10, 2, "Quitting...\n");
    return 0;
}

void initialize_field(char field[HEIGHT][WIDTH]) {
    printf("Заполнить поле случайным образом (r) или же согласно паттерну из файла (f)?\n");
    scanf("%c", &field[0][0]);
    if (field[0][0] == 'r' || field[0][0] == 'R') {
        srand(time(NULL));
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                field[i][j] = (rand() % 2 == 0) ? ALIVE_CELL : DEAD_CELL;
            }
        }
    } else if ((field[0][0] == 'f') || (field[0][0] == 'F')) {
        printf("Введите путь к файлу:\n");
        char path[100];
        scanf("%s", path);
        FILE *file = fopen(path, "r");
        if (file == NULL) {
            printf("Ошибка открытия файла\n");
            exit(1);
        }
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                fscanf(file, "%c", &field[i][j]);
            }
        }
    } else {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                field[i][j] = getchar();
            }
        }
        if (freopen("/dev/tty", "r", stdin) == NULL) {
            printf("Ошибка открытия файла\n");
            exit(1);
        }
    }
}
void print_field(char field[HEIGHT][WIDTH]) {
    char new_field[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbors = count_neighbors(field, i, j);
            if ((field[i][j] == ALIVE_CELL) && (neighbors == 2 || neighbors == 3)) {
                new_field[i][j] = ALIVE_CELL;
            } else if ((field[i][j] == DEAD_CELL) && (neighbors == 3)) {
                new_field[i][j] = ALIVE_CELL;
            } else {
                new_field[i][j] = DEAD_CELL;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            field[i][j] = new_field[i][j];
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            mvaddch(i + 1, j, new_field[i][j]);
        }
    }
}
int count_neighbors(char field[HEIGHT][WIDTH], int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            int r = (i + HEIGHT) % HEIGHT;
            int c = (j + WIDTH) % WIDTH;

            if (field[r][c] == ALIVE_CELL) {
                count++;
            }
        }
    }
    if (field[row][col] == ALIVE_CELL) {
        count--;
    }
    return count;
}
void draw_menu(int speed) {
    mvprintw(HEIGHT + 2, 0, "Menu:\n");
    mvprintw(HEIGHT + 3, 2, "f: Speed Up");
    mvprintw(HEIGHT + 4, 2, "s: Slow Down");
    mvprintw(HEIGHT + 5, 2, "p: Pause/Resume");
    mvprintw(HEIGHT + 6, 2, "q: Quit");
    mvprintw(HEIGHT + 8, 2, "Speed: %d", speed);
}