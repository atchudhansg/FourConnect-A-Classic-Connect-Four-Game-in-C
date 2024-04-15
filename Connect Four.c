/*
 * Connect Four Game
 * Author: Atchudhan Sreekanth 
 * Date: 25/11/2023
 *
 * Description:
 * This program implements a simple Connect Four game in C. Players take turns dropping colored discs
 * into a vertically suspended grid. The first player to connect four discs of the same color vertically,
 * horizontally, or diagonally wins the game.
 *
 * Usage:
 * Compile the program using a C compiler and run the executable.
 * Follow the on-screen instructions to play the game.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char name[20];
    char colour[6];
};

struct scoreboard {
    int player1;
    int player2;
    int tie;
};

struct Board {
    int board[7][9];
    int topindex[9];
};

int checkifgameisover(struct Board* b, int coln) {
    int c = 0;
    for(int i = 0; i < 9; i++) {
        if(b->topindex[i] < 0) {
            c++;
        }
    }
    if(c == 9) {
        return 0;
    } else {
        return 1;
    }
}

int play(int coln, struct user u, struct Board* b) {
    if(coln > 8 && coln < 0) {
        printf("valid input, enter a new one\n");
        printf("Enter the column :");
        scanf("%d", &coln);
        play(coln, u, b);
        return 0;
    }
    if(b->topindex[coln - 1] < 0) {
        int flag = checkifgameisover(b, coln);
        if(flag == 0) {
            printf("Game over. Tie\n");
        } else {
            printf("Column is full, enter new number\n");
            printf("Enter the column :");
            scanf("%d", &coln);
            play(coln, u, b);
            return 0;
        }
    }
    if(!strcmp(u.colour, "red")) {
        b->board[b->topindex[coln - 1]][coln - 1] = 1;
        b->topindex[coln - 1] = b->topindex[coln - 1] - 1;
        return 1;
    }
    if(!strcmp(u.colour, "blue")) {
        b->board[b->topindex[coln - 1]][coln - 1] = 2;
        b->topindex[coln - 1] = b->topindex[coln - 1] - 1;
        return 1;
    }
}

int checkleft(struct user u, struct Board b, int row, int coln, int count) {
    int countl = 0;
    for(int i = coln - 1; i > coln - 4; i--) {
        if(i > -1) {
            if(!strcmp(u.colour, "red")) {
                if(b.board[row][i] == 1) {
                    countl++;
                } else {
                    break;
                }
            } else if(!strcmp(u.colour, "blue")) {
                if(b.board[row][i] == 2) {
                    countl++;
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
    return countl;
}

int checkright(struct user u, struct Board b, int row, int coln, int count) {
    int countr = 0;
    for(int i = coln + 1; i < coln + 4; i++) {
        if(i < 9) {
            if(!strcmp(u.colour, "red")) {
                if(b.board[row][i] == 1) {
                    countr++;
                } else {
                    break;
                }
            } else if(!strcmp(u.colour, "blue")) {
                if(b.board[row][i] == 2) {
                    countr++;
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }

    count = countr;
    if(count < 3) {
        count = count + checkleft(u, b, row, coln, count);
    }
    if(count == 3) {
        return 1;
    } else {
        return 0;
    }
}

int checktop(struct user u, struct Board b, int row, int coln, int count) {
    int countt = 0;
    for(int i = row - 1; i > row - 4; i--) {
        if(i > -1) {
            if(!strcmp(u.colour, "red")) {
                if(b.board[i][coln] == 1) {
                    countt++;
                } else {
                    break;
                }
            } else if(!strcmp(u.colour, "blue")) {
                if(b.board[i][coln] == 2) {
                    countt++;
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
    count = count + countt;
    return count;
}

int checkdown(struct user u, struct Board b, int row, int coln, int count) {
    int countd = 0;
    for(int i = row + 1; i < row + 4; i++) {
        if(i < 7) {
            if(!strcmp(u.colour, "red")) {
                if(b.board[i][coln] == 1) {
                    countd++;
                } else {
                    break;
                }
            } else if(!strcmp(u.colour, "blue")) {
                if(b.board[i][coln] == 2) {
                    countd++;
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
    count = countd;
    if(count < 3) {
        count = count + checktop(u, b, row, coln, count);
    }
    if(count == 3) {
        return 1;
    } else {
        return 0;
    }
}

int checkdiagonal1(struct user u, struct Board b, int row, int coln, int count) {
    int countbr = 0;
    int i = row + 1;
    int j = coln + 1;
    int c = 0;
    while(i < 7 && j < 7 && c < 3) {
        if(!strcmp(u.colour, "red")) {
            if(b.board[i][j] == 1) {
                ++countbr;
            }
        } else if(!strcmp(u.colour, "blue")) {
            if(b.board[i][j] == 2) {
                ++countbr;
            }
        }
        ++i;
        ++j;
        ++c;
    }
    return countbr;
}

int checkdiagonal(struct user u, struct Board b, int row, int coln, int count) {
    int counttl = 0;
    int i = row - 1;
    int j = coln - 1;
    int c = 0;
    while(i > -1 && j > -1 && c < 3) {
        if(!strcmp(u.colour, "red")) {
            if(b.board[i][j] == 1) {
                ++counttl;
            }
        } else if(!strcmp(u.colour, "blue")) {
            if(b.board[i][j] == 2) {
                ++counttl;
            }
        }
        --i;
        --j;
        ++c;
    }
    count = counttl;
    if(count < 3) {
        count = count + checkdiagonal1(u, b, row, coln, count);
    }
    if(count == 3) {
        return 1;
    } else {
        return 0;
    }
}

int checkdiagonal3(struct user u, struct Board b, int row, int coln, int count) {
    int countbl = 0;
    int i = row + 1;
    int j = coln - 1;
    int c = 0;

    while(i > -1 && j > -1 && c < 3) {
        if(!strcmp(u.colour, "red")) {
            if(b.board[i][j] == 1) {
                ++countbl;
            }
        } else if(!strcmp(u.colour, "blue")) {
            if(b.board[i][j] == 2) {
                ++countbl;
            }
        }
        ++i;
        --j;
        ++c;
    }
    return countbl;
}

int checkdiagonal2(struct user u, struct Board b, int row, int coln, int count) {
    int counttr = 0;
    int i = row - 1;
    int j = coln + 1;
    int c = 0;

    while(i > -1 && j > -1 && c < 3) {
        if(!strcmp(u.colour, "red")) {
            if(b.board[i][j] == 1) {
                ++counttr;
            }
        } else if(!strcmp(u.colour, "blue")) {
            if(b.board[i][j] == 2) {
                ++counttr;
            }
        }
        --i;
        ++j;
        ++c;
    }
    count = counttr;
    if(count < 3) {
        count = count + checkdiagonal3(u, b, row, coln, count);
    }
    if(count == 3) {
        return 1;
    } else {
        return 0;
    }
}

void display(struct Board b) {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 9; j++) {
            if(b.board[i][j] == 2) {
                printf("2");
            } else if(b.board[i][j] == 1) {
                printf("1");
            } else {
                printf("%d", 0);
            }
        }
        printf("\n");
    }
}

int checkforwinner(struct user u, struct Board b, int coln) {
    int count = 0;
    int row = b.topindex[coln - 1] + 1;
    coln = coln - 1;
    int flag = 0;
    flag = checkright(u, b, row, coln, count);
    if(flag == 1) {
        return 1;
    }
    count = 0;
    flag = checkdown(u, b, row, coln, count);
    if(flag == 1) {
        return 1;
    }
    count = 0;
    flag = checkdiagonal(u, b, row, coln, count);
    if(flag == 1) {
        return 1;
    }
    count = 0;
    flag = checkdiagonal2(u, b, row, coln, count);
    if(flag == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    struct user* listofusers = (struct user*)calloc(2, sizeof(struct user));
    for(int i = 0; i < 2; i++) {
        printf("Enter the name of player %d:", i + 1);
        scanf("%s", &listofusers[i].name);
        printf("\n");
        printf("Enter the colour to play:");
        scanf("%s", &listofusers[i].colour);
    }

    int noofrounds;
    printf("Enter the number of rounds to be played:");
    scanf("%d", &noofrounds);

    int round = 1;
    struct scoreboard s;
    s.player1 = 0;
    s.player2 = 0;
    s.tie = 0;

    while(noofrounds >= round) {
        printf("Round %d\n", round);
        struct Board currboard;
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 9; j++) {
                currboard.board[i][j] = 0;
            }
        }
        for(int j = 0; j < 9; j++) {
            currboard.topindex[j] = 6;
        }

        int turn = 1, coln = 0;
        while(1) {
            if(turn == 1) {
                printf("Enter the column %s:", listofusers[turn - 1].name);
                scanf("%d", &coln);
                play(coln, listofusers[turn - 1], &currboard);
                int flag = checkforwinner(listofusers[turn - 1], currboard, coln);
                if(flag == 1) {
                    printf("Player %s has won round %d\n", listofusers[turn - 1].name, round);
                    ++s.player1;
                    break;
                }
                display(currboard);
                ++turn;
            } else {
                printf("Enter the column %s:", listofusers[turn - 1].name);
                scanf("%d", &coln);
                play(coln, listofusers[turn - 1], &currboard);
                int flag = checkforwinner(listofusers[turn - 1], currboard, coln);
                if(flag == 1) {
                    printf("Player %s has won round %d\n", listofusers[turn - 1].name, round);
                    ++s.player2;
                    break;
                }
                display(currboard);
                ++turn;
            }
            if(turn == 3) {
                turn = 1;
            }
        }
        display(currboard);
        int ch = 0;
        printf("1)Do you want to display the scoreboard\n");
        printf("2)Do you want to move round \n");
        printf("Enter your choice:");
        scanf("%d", &ch);

        if(ch == 1) {
            printf("Score of %s:%d\n", listofusers[0].name, s.player1);
            printf("Score of %s:%d\n", listofusers[1].name, s.player2);
        }
        ++round;
    }

    free(listofusers);
    return 0;
}
