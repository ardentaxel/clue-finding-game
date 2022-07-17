#ifndef LIBCRIME_H_INCLUDED
#define LIBCRIME_H_INCLUDED

#include <iostream>
#include <sstream>
#include <ctime>
#include <cctype>
#include <assert.h>
#include <cmath>
using namespace std;

enum StatusCodes
{
    SUCCESS,
    ERR_ARGC,
    ERR_ARGV
};

enum FeatureIndex
{
    EMPTY,
    PLAYER,
    POT_CLUE,
    CLUE,
    REVEAL
};
const char FEATURES[] = {'.','P','#','#','@'};


typedef int* OneDArr;
typedef int** TwoDArr;
struct tGame
{
    int intRows;
    int intCols;
    int intPRow;
    int intPCol;
    int intClueNum;
    int intPotClueNum;
    int intNTurns;
    bool blnTurnsEnd;
    bool blnGameWon;

    TwoDArr arrGame;

};

const int MIN_E_SPACE = 10;
const int MAX_SIZE = 30;
const int MIN_SIZE = 3;

namespace CrimeSpace
{
    int ConvertToInt(string strNum);
    tGame InitGame(int intRows, int intCols, int intNClues, int intNTurns);
    void DeallocMem(tGame& stcGame);
    void PrintWorld(tGame& stcGame);
    void MovePlayer(tGame& stcGame,char chInput);
    void Investigate(tGame& stcGame);
    void GameOver(tGame& stcGame);

}



#endif // LIBCRIME_H_INCLUDED
#ifndef LIBCRIME_H_INCLUDED
#define LIBCRIME_H_INCLUDED



#endif // LIBCRIME_H_INCLUDED
