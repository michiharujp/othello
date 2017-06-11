#include<stdio.h>
#include<stdbool.h>

void print_board(int size, int board[size][size]) {
    //左上の空白
    printf(" ");
    for (int k = 0; k < size; k++) {
        printf(" %d", k);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d", i);
        for (int j = 0; j < size; j++) {
            switch(board[i][j]) {
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("●");
                    break;
                case -1:
                    printf("〇");
                    break;
                case 2:
                    printf("　");
                    break;
            }
        }
        printf("\n");
    }
}

void initialize(int size, int board[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
    board[size / 2][size / 2]++;
    board[size / 2 - 1][size / 2]--;
    board[size / 2][size / 2 - 1]--;
    board[size / 2 - 1][size / 2 - 1]++;
}

void get_rid_of_pre(int size, int board[size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(board[i][j] == 2) {
                board[i][j] = 0;
            }
        }
    }
}

int one_line(int size, int board[size][size], int height, int width, int color, int vchg, int schg) {
    bool result = false;
    int v = height;
    int s = width;
    while(v != size && v != -1 && s != size && s != -1) {
        v += vchg;
        s += schg;
        if(board[v][s] == 0) {
            break;
        }
        if(board[v][s] == color) {
            while(true) {
                v -= vchg;
                s -= schg;
                if(v == height && s == width) {
                    break;
                }
                board[v][s] = color;
                result = true;
            }
            break;
        }
    }
    if(result) {
        return 1;
    } else {
        return 0;
    }
}

bool reverse(int size, int board[size][size], int height, int width, int color) {
    int worked = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = - 1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            worked += one_line(size, board, height, width, color, i, j);
        }
    }
    if(worked > 0) {
        board[height][width] = color;
        return true;
    }
    return false;
}

int check_one_way(int size, int board[size][size], int height, int width, int color, int vchg, int schg) {
    bool result = false;
    int v = height;
    int s = width;
    while(v != size && v != -1 && s != size && s != -1) {
        v += vchg;
        s += schg;
        if(board[v][s] == 0 || board[v][s] == 2) {
            break;
        }
        if(board[v][s] == color) {
            v -= vchg;
            s -= schg;
            if(v == height && s == width) {
                break;
            }
            result = true;
            break;
        }
    }
    if(result) {
        return 1;
    }
    return 0;
}

int check_one(int size, int board[size][size], int height, int width, int color) {
    int canPutLine = 0;
    for(int i = -1; i <= 1; i++) {
        for(int j = - 1; j <= 1; j++) {
            if(i == 0 && j == 0) continue;
            canPutLine += check_one_way(size, board, height, width, color, i, j);
        }
    }
    if(canPutLine > 0) {
        return true;
    }
    return false;
}

bool check(int size, int board[size][size], int color) {
    int canput = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(board[i][j] == 0) {
                if( check_one(size, board, i, j, color) ) {
                    board[i][j] = 2;
                    canput++;
                }
            }
        }
    }
    if(canput > 0) {
        return true;
    }
    return false;
}

int count_number(int size, int board[size][size], int color) {
    int counter = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(board[i][j] == color) {
                counter++;
            }
        }
    }
    return counter;
}

int main(void) {
    int n = 1;
    while(n % 2 != 0) {
        printf("一辺の数を偶数で入力してください:");
        scanf("%d", &n);
        if (n % 2 != 0) {
            printf("偶数を入力してください！（怒）\n");
        }
    }
    int board[n][n];
    initialize(n, board);
    int h, w;
    int color = 1;
    int pass = 0;
    bool put, pre;
    while(true) {
        if(color == 1) {
            printf("白のターンです\n");
        } else if(color == -1) {
            printf("黒のターンです\n");
        }
        pre = check(n, board, color);
        print_board(n, board);
        get_rid_of_pre(n, board);
        if(!pre) {
            printf("置く場所がありません\n");
            color = -color;
            pass++;
            if(pass == 2) {
                break;
            }
            continue;
        }
        pass = 0;
        scanf("%d %d", &h, &w);
        if(board[h][w] != 0){
            printf("既に置いてあります\n");
            continue;
        }
        put = reverse(n, board, h, w, color);
        if(!put){
            printf("そこにはおけません\n");
            continue;
        }
        color = -color;
    }
    int white = count_number(n, board, 1);
    int black = count_number(n, board, -1);
    printf("結果発表\n");
    printf("白が%d個、黒が%d個\n", white, black);
    if(white > black) {
        printf("白の勝ちです\n");
    } else if(white < black) {
        printf("黒の勝ちです\n");
    } else {
        printf("引き分けです\n");
    }
    return 0;
}
