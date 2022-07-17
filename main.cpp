#include "libCrime.h"
#include <assert.h>
#include <iostream>

using namespace std;
using namespace CrimeSpace;

int main(int argc, char** argv)
{
    srand(time(nullptr));
    if(argc != 5)
    {
        cerr << "Invalid number of arguments" << endl;
        cerr << "Please run " << argv[0] << "with: " << endl
             << "<TotalRows>" << endl
             << "<TotalCols>" << endl
             << "<N_TurnsLeft>" << endl
             << "<N_Clues>" << endl;
        exit(ERR_ARGC);
    }
    int intRows = ConvertToInt(argv[1]);
    int intCols = ConvertToInt(argv[2]);
    int intNTurns = ConvertToInt(argv[3]);
    int intNClues = ConvertToInt(argv[4]);
    int intFeatureCount = intNClues + 2*intNClues + 1;

    if((intRows * intCols) < intFeatureCount)
    {
        cerr << "World is too small. Increase world size or reduce number of clues" << endl;
        assert((intRows * intCols) > intFeatureCount);
    }
    if(intCols > MAX_SIZE || intRows > MAX_SIZE || intCols < MIN_SIZE || intRows < MIN_SIZE)
    {
        cerr << "<TotalRows> and <TotalCols> cannot be greater than " << MAX_SIZE << " or less than " << MIN_SIZE << endl;
        assert(intCols < MAX_SIZE && intRows < MAX_SIZE && intCols > MIN_SIZE && intRows > MIN_SIZE);
    }

    tGame CrimeWorld = InitGame(intRows,intCols,intNClues,intNTurns);
    bool blnContinue = true;
    char chInput = '\n';
    do
    {
        PrintWorld(CrimeWorld);

        cin >> chInput;
        switch(toupper(chInput))
        {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                MovePlayer(CrimeWorld,chInput);
                break;
            case 'I':
                Investigate(CrimeWorld);
                break;
            case 'Q':
                blnContinue = false;
                break;
        }
        system("pause");
        GameOver(CrimeWorld);



    }while(blnContinue && !CrimeWorld.blnTurnsEnd && !CrimeWorld.blnGameWon);

    if(!blnContinue)
    {
        cout << "Boohoo! You chose to quit the game QUITTER!" << endl;
    }
    DeallocMem(CrimeWorld);

    return SUCCESS;
}
