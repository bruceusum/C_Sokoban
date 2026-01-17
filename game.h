#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct {
    int destX;
    int destY;
    bool hasBox;
} Game;

extern int PlayerX;
extern int PlayerY;
extern int DestCount;


void SetPlayer(int y, int x);
void SetDest(Game* g, int y, int x);

int GetPlayerX(void);
int GetPlayerY(void);

int GetDestX(Game* g);
int GetDestY(Game* g);

void SetHasBox(Game* g, bool v);
bool IfHasBox(Game* g);

bool IfWin(void);
void ResetDestCount(void);
void ChangeDestCount(int v);

#endif
