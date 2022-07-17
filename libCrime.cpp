#include "libCrime.h"

namespace CrimeSpace
{
    int GetRand(int intLower, int intUpper)
    {
        int intRange = intUpper - intLower + 1;
        return rand()%intRange + intLower;
    }

    int ConvertToInt(string strNum)
    {
        int intNum;
        stringstream ss {strNum};
        ss >> intNum;
        if(ss.fail())
        {
            cerr << "Failed to convert " << strNum << " to int" << endl;
            exit(ERR_ARGV);
        }
        return intNum;
    }

    TwoDArr AllocMem(int intRows,int intCols)
    {
        TwoDArr arrGame;
        arrGame = new OneDArr[intRows];
        for(auto r = 0; r < intRows; r++)
        {
            arrGame[r] = new int[intCols];
            for(auto c = 0; c < intCols; c++)
            {
                arrGame[r][c] = EMPTY;
            }
        }


        return arrGame;
    }

    void PlaceFeature(tGame& stcGame, int intFeature,int intFeatCount)
    {
        for(auto i = 0; i < intFeatCount; i++)
        {
            int intCol = GetRand(0,stcGame.intCols-1);
            int intRow = GetRand(0,stcGame.intRows-1);

            while(stcGame.arrGame[intRow][intCol] != EMPTY)
            {
                intCol = GetRand(0,stcGame.intCols-1);
                intRow = GetRand(0,stcGame.intRows-1);
            }

            stcGame.arrGame[intRow][intCol] = intFeature;
        }
    }

    tGame InitGame(int intRows, int intCols, int intNClues, int intNTurns)
    {
        tGame stcGame;
        stcGame.intRows = intRows;
        stcGame.intCols = intCols;
        stcGame.intClueNum = intNClues;
        stcGame.intPotClueNum = intNClues*2;
        stcGame.intNTurns = intNTurns;

        stcGame.arrGame = AllocMem(intRows,intCols);
        stcGame.intPRow = GetRand(0,intRows-1);
        stcGame.intPCol = GetRand(0,intCols-1);

        stcGame.blnTurnsEnd = false;
        stcGame.blnGameWon = false;

        stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] = PLAYER;
        PlaceFeature(stcGame,CLUE,stcGame.intClueNum);
        PlaceFeature(stcGame,POT_CLUE,stcGame.intPotClueNum);

        return stcGame;
    }

    void PrintWorld(tGame& stcGame)
    {
        system("cls");
        cout << "Crime Scene Investigation" << endl;
        cout << "Movement: " << endl;
        cout << "Up: 'w/w' " << endl << "Left: 'a/A'" << endl << "Down: 's/S'" << "Right: 'd/D'" << endl;
        cout << "To investigate press 'I/i' " << endl;
        cout << endl << "#s - are potential clues, @s - are actual clues. Find all actual clues before running out of moves to win the game" << endl << endl;

        for(auto r = 0; r < stcGame.intRows; r++)
        {
            for(auto c = 0; c < stcGame.intCols; c++)
            {
                cout << FEATURES[stcGame.arrGame[r][c]] << " ";
            }
            cout << endl;
        }

        cout << "Number of turns left: " << stcGame.intNTurns << endl;
    }
    bool IsInWorld(int intCol, int intRow, tGame& stcGame)
    {
        if(intCol < stcGame.intCols && intCol >= 0 && intRow < stcGame.intRows && intRow >= 0)
            return true;
        else
            return false;
    }
    void MovePlayer(tGame& stcGame,char chInput)
    {
        int intDRow = stcGame.intPRow;
        int intDCol = stcGame.intPCol;
        switch(chInput)
        {
            case 'w':
                intDRow--;
                break;
            case 'a':
                intDCol--;
                break;
            case 's':
                intDRow++;
                break;
            case 'd':
                intDCol++;
                break;
        }
        if (IsInWorld(intDCol,intDRow,stcGame))
        {
            if(stcGame.arrGame[intDRow][intDCol] != CLUE && stcGame.arrGame[intDRow][intDCol] != POT_CLUE && stcGame.arrGame[intDRow][intDCol] != REVEAL)
            {
                stcGame.arrGame[intDRow][intDCol] = stcGame.arrGame[intDRow][intDCol] + PLAYER;
                stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] = stcGame.arrGame[stcGame.intPRow][stcGame.intPCol] - PLAYER;
                stcGame.intPRow = intDRow;
                stcGame.intPCol = intDCol;
                stcGame.intNTurns--;
            }


        }
    }
    void Investigate(tGame& stcGame)
    {
        int intCol = stcGame.intPCol;
        int intRow = stcGame.intPRow;
        int intDistance = 0;
        for(auto r =0; r<stcGame.intRows; r++)
        {
            for(auto c =0; c<stcGame.intCols; c++)
            {
                intDistance = sqrt(pow((r-intRow),2) + pow((c-intCol),2));
                if(intDistance == 1)
                {
                    if(stcGame.arrGame[r][c] == CLUE)
                    {
                        stcGame.arrGame[r][c] = REVEAL;
                    }
                    else if(stcGame.arrGame[r][c] == POT_CLUE)
                    {
                        stcGame.arrGame[r][c] = EMPTY;
                    }
                }
            }
        }
        stcGame.intNTurns--;
    }

    void GameOver(tGame& stcGame)
    {
        int intClueCount = 0;
        for(auto r = 0; r < stcGame.intRows; r++)
        {
            for(auto c = 0; c < stcGame.intCols; c++)
            {
                if(stcGame.arrGame[r][c] == REVEAL)
                {
                    intClueCount++;
                }
            }
        }
        if(intClueCount == stcGame.intClueNum)
        {
            stcGame.blnGameWon = true;
            PrintWorld(stcGame);
            cout << "Congratulations You Won The Game" << endl;
        }
        if(stcGame.intNTurns == 0)
        {
            PrintWorld(stcGame);
            stcGame.blnTurnsEnd = true;
            cout << "Unfortunately you ran out of turns :(" << endl;
        }
    }

    void DeallocMem(tGame& stcGame)
    {
        for (auto r = 0; r < stcGame.intRows; r++)
        {
            delete[] stcGame.arrGame[r];
        }
        delete[] stcGame.arrGame;
        stcGame.arrGame = nullptr;
    }

}
