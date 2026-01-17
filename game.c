#include "game.h"

/* global variables */
int PlayerX = 0;
int PlayerY = 0;
int DestCount = 0;

void SetPlayer(int y, int x) {
    PlayerX = x;
    PlayerY = y;
}

void SetDest(Game* g, int y, int x) {
    g->destX = x;
    g->destY = y;
    g->hasBox = false;
    DestCount++;
}

int GetPlayerX(void) { return PlayerX; }
int GetPlayerY(void) { return PlayerY; }

int GetDestX(Game* g) { return g->destX; }
int GetDestY(Game* g) { return g->destY; }

void SetHasBox(Game* g, bool v) {
    g->hasBox = v;
}

bool IfHasBox(Game* g) {
    return g->hasBox;
}

bool IfWin(void) {
    return DestCount == 0;
}

void ChangeDestCount(int v) {
    DestCount += v;
}

void ResetDestCount(void) {
    DestCount = 0;
}