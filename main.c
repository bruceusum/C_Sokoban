#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "game.h"

#define MAP(i, j) Map[(i) * M + (j)]

int main(void) {
    FILE* InMap = fopen("missiontest.txt", "r");
    if (!InMap) {
        printf("File could not be opened\n");
        return 1;
    }

    int Reset = 1;

    while (Reset) {
        Reset = 0;

        int N, M;
        fscanf(InMap, "%d %d", &N, &M);

        Game dest[100];
        int destSize = 0;
        char* Map = malloc(N * M * sizeof(char));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                fscanf(InMap, " %c", &MAP(i, j));

                if (MAP(i, j) == '0') {
                    SetPlayer(i, j);
                }
                else if (MAP(i, j) == '2') {
                    SetDest(&dest[destSize++], i, j);
                }
            }
        }

        while (!IfWin() && !Reset) {
            system("cls");

            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    for (int k = 0; k < destSize; k++) {
                        if (GetDestX(&dest[k]) == j && GetDestY(&dest[k]) == i) {
                            if (MAP(i, j) == '1' && !IfHasBox(&dest[k])) {
                                ChangeDestCount(-1);
                                SetHasBox(&dest[k], 1);
                            }
                            else if (MAP(i, j) == '0' && IfHasBox(&dest[k])) {
                                ChangeDestCount(1);
                                SetHasBox(&dest[k], 0);
                            }
                            else if (MAP(i, j) == '-') {
                                MAP(i, j) = '2';
                            }
                        }
                    }
                    printf("%c", MAP(i, j));
                }
                printf("\n");
            }


            int Move = _getch();

            if (Move == 224) {
                Move = _getch();
                int dx = 0, dy = 0;

                if (Move == 72) dy = -1; // up
                if (Move == 80) dy = 1;  // down
                if (Move == 75) dx = -1; // left
                if (Move == 77) dx = 1;  // right

                int nx = PlayerX + dx;
                int ny = PlayerY + dy;

                if (MAP(ny,nx) == '1' &&
                    MAP(ny + dy, nx + dx) != '/' &&
                    MAP(ny + dy, nx + dx) != '1') {

                    MAP(PlayerY, PlayerX) = '-';
                    SetPlayer(ny, nx);
                    MAP(PlayerY, PlayerX) = '0';
                    MAP(ny + dy, nx + dx) = '1';
                }
                else if (MAP(ny, nx) != '/' && MAP(ny, nx) != '1') {
                    MAP(PlayerY, PlayerX) = '-';
                    SetPlayer(ny, nx);
                    MAP(PlayerY, PlayerX) = '0';
                }
            }
            else if (Move == 'r' || Move == 'R') {
                fseek(InMap, 0, SEEK_SET);
                ResetDestCount();
                Reset = 1;
            }
        }

        free(Map);
    }
    
    fclose(InMap);

    if (IfWin()) {
        printf("You Win!!!\n");
    }

    getchar();
    return 0;
}