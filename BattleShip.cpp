//  Name : Franklin Antony
//  ID : 200626510
//  College Username : ec20076

#include "Board.h"
#include "Player.h"
#include "displayBoard.h"
#include <iostream>
using namespace std;

Player::~Player()
{
}

Board::~Board()
{
}

// Added funtion protoype to reuse the printMenu()
void printMainMenu();

void getPlayerName(char &playerName)
{
    cout << "\nEnter player name:\n";
    cin >> playerName;
}

bool inValidDirection(char direction)
{
    if (!(
            direction == 'N' || direction == 'S' || direction == 'W' || direction == 'E' ||
            direction == 'n' || direction == 's' || direction == 'w' || direction == 'e'))
    {
        return true;
    }
    return false;
}

void getDirection(char &direction)
{
    do
    {
        if (inValidDirection(direction) && direction != 'z')
        {
            cout << "Invalid direction!\n";
        }
        cout << "\nEnter the direction(N/E/S/W)";
        cin >> direction;
    } while (inValidDirection(direction));
}

bool checkValidX(char X)
{
    if ((X >= 'A' && X <= 'H') || (X >= 'a' && X <= 'h'))
    {
        return true;
    }
    return false;
}

bool checkValidY(char Y)
{
    if (Y >= '1' && Y <= '8')
    {
        return true;
    }
    return false;
}

void getCoordinates(char &X, char &Y)
{
    do
    {

        cout << "\nEnter the X coordinate (A-H):\n";
        cin >> X;
        if (!checkValidX(X))
        {
            cout << "Invalid entry. Please try again";
        }
    } while (!checkValidX(X));

    do
    {
        cout << "\nEnter the Y coordinate (1-8):\n";
        cin >> Y;
        if (!checkValidY(Y))
        {
            cout << "Invalid entry. Please try again";
        }
    } while (!checkValidY(Y));
}

bool checkIfPointPossible(char X, char Y, char direction, int length, char shipBoard[8][8])
{
    // Condtion 1: Exceeds the box
    int integerCharY = Y - '0';
    int integerCharX = tolower(X) - 97;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (integerCharX == i && integerCharY - 1 == j)
            {
                switch (direction)
                {
                case 'N':
                case 'n':
                    if (integerCharX - length < 0)
                    {
                        return false;
                    }
                    break;
                case 'S':
                case 's':
                    if (integerCharX + length > 8)
                    {
                        return false;
                    }
                    break;
                case 'E':
                case 'e':
                    if (integerCharY + length > 7)
                    {
                        return false;
                    }
                    break;
                case 'W':
                case 'w':
                    if (integerCharY - length < 0)
                    {
                        return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}

void printBoard(char board[8][8])
{
    cout << "      A - B - C - D - E - F - G - H\n";
    for (int i = 0; i < 8; i++)
    {
        cout << "- - - - - - - - - - - - - - - - - - -\n";
        cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++)
            cout << "   " << board[i][j];
        cout << "\n";
    }
}

void addShips(int &count, char shipBoard[8][8], int &totalCells)
{
    char X, Y, direction = 'z';
    int length = 0, shipLength = 0;
    cout << "\n----- Adding Ship " << count + 1 << " of 5 ----- ";
    getCoordinates(X, Y);
    getDirection(direction);
    cout << "\n Enter ship length: ";
    cin >> shipLength;
    int integerCharY = Y - '0';
    int integerCharX = tolower(X) - 97;
    if (checkIfPointPossible(X, Y, direction, shipLength, shipBoard))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                if (integerCharX == i && integerCharY - 1 == j)
                {
                    shipBoard[j][i] = 'S';
                    int tempI = i;
                    int tempJ = j;
                    switch (direction)
                    {
                    case 'N':
                    case 'n':
                        while (++length < shipLength)
                        {
                            shipBoard[--tempJ][i] = 'S';
                        };
                        break;
                    case 'S':
                    case 's':
                        while (++length < shipLength)
                        {
                            shipBoard[++tempJ][i] = 'S';
                        };
                        break;
                    case 'E':
                    case 'e':
                        while (++length < shipLength)
                        {
                            shipBoard[j][++tempI] = 'S';
                        };
                        break;
                    case 'W':
                    case 'w':
                        while (++length < shipLength)
                        {
                            shipBoard[j][--tempI] = 'S';
                        };
                        break;
                    }
                }
            }
        }
        cout << "\nYou have added a ship to the coordinates X: " << X << " and Y:" << Y << " in " << direction << " direction\n\n";
        count++;
        totalCells = totalCells + shipLength;
    }
    else
    {
        cout << "\nInvalid entry. Please try again! \n\n";
    }
    printBoard(shipBoard);
}
void enterToContinue()
{
    cout << "\nPress enter to continue!";
    cin.clear();          //clears the stream
    cin.ignore(50, '\n'); //ignores next line(enter)
    cin.get();            //“cin>>” expects at least one char input, just enter doesn’t work
}

void Player::displayBoardState(int fireCount, char hitBoard[8][8])
{
    int turn = fireCount;
    cout << "\n_____________________________\n";
    if (turn > 0)
        cout << "\n\nTurn " << turn;
    cout << "\n\nDisplaying the current board state\n\n";
    printBoard(hitBoard);
}

bool Player::checkWon(int hitCells, int totalCells)
{
    if (hitCells != 0 && hitCells == totalCells)
    {
        return true;
    }
    return false;
}

void Player::fireShip(char playerName, char hitBoard[8][8], char shipBoard[8][8], int totalCells, int &fireCount, int &hitCells)
{
    char X, Y;
    cout << "\nPlayer " << playerName << " enter coordinates to fire:";
    cout << "\n____________________________________\n";
    // printBoard(hitBoard);
    // do
    // {
    displayBoardState(fireCount, hitBoard);
    getCoordinates(X, Y);
    int integerCharY = Y - '0';
    int integerCharX = tolower(X) - 97;
    if (checkValidY(Y) && checkValidX(X) &&
        (hitBoard[integerCharY - 1][integerCharX] != 'M' ||
         hitBoard[integerCharY - 1][integerCharX] != 'H'))
    {
        cout << "\nYou fired at X: " << X << " and "
             << " Y: " << Y;

        printBoard(hitBoard);
        fireCount++;
    }
    else
    {
        cout << "\n Invalid points. Please try again";
    }

    // } while (hitCells != totalCells);

    if (checkWon(hitCells, totalCells))
    {
        cout << "\nYou have won!";
        displayBoardState(fireCount, hitBoard);
    }
}

void addShipMenu()
{

    cout << "\n____________________________________________";
    cout << "\n\t\t  Add Ship";
    cout << "\n____________________________________________";
    cout << "\n\t   No  Name         Squares";
    cout << "\n____________________________________________";
    cout << "\n\t    1  Carrier         5";
    cout << "\n\t    1  Battleship      4";
    cout << "\n\t    2  Cruiser         3";
    cout << "\n\t    1  Submarine       3";
    cout << "\n\t    1  Destroyer       2";
    cout << "\n____________________________________________\n\n";
}
void Board::resetShipBoard(char shipBoard[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            shipBoard[i][j] = ' ';
}

void beginGame()
{
    Board B;
    Player A, C;
    char playerName1, playerName2, X, Y;
    int count1 = 0, count2 = 0, totalCells1 = 0, totalCells2 = 0;
    int fireCount1 = 0, hitCells1 = 0, fireCount2 = 0, hitCells2 = 0;
    char shipBoard1[8][8], hitBoard1[8][8], shipBoard2[8][8], hitBoard2[8][8];
    B.resetShipBoard(shipBoard1);
    B.resetShipBoard(hitBoard1);
    B.resetShipBoard(shipBoard2);
    B.resetShipBoard(hitBoard2);
    getPlayerName(playerName1);
    getPlayerName(playerName2);

    addShipMenu();

    while (count1 < 2)
    {
        addShips(count1, shipBoard1, totalCells1);
        if (count1 == 2)
        {
            enterToContinue();
        }
    }

    addShipMenu();

    while (count2 < 2)
    {
        addShips(count2, shipBoard2, totalCells2);
        if (count2 == 2)
        {
            enterToContinue();
        }
    }

    cout<<"\n********\n\n";
    printBoard(shipBoard1);
    printBoard(shipBoard2);


    do
    {
        A.fireShip(playerName1, hitBoard1, shipBoard1, totalCells1, fireCount1, hitCells1);
        C.fireShip(playerName2, hitBoard2, shipBoard2, totalCells2, fireCount2, hitCells2);
            cout<<"\n***%%%%%   %%%%*****\n\n";
    printBoard(hitBoard1);
    printBoard(hitBoard2);
    } while (hitCells1 != totalCells1 || hitCells2 != totalCells2);

    enterToContinue();
}

void exitOut()
{
    cout << "\nGood Bye!!!\n";
    exit(0);
}

void endGame()
{
    char response;
    cout << "\n Are you sure you want to exit the game? (Y/N)\n";
    cin >> response;
    switch (response)
    {
    case 'Y':
    case 'y':
        exitOut();
        break;
    case 'N':
    case 'n':
    default:
        printMainMenu();
        break;
    }
}

int displayMenu()
{
    int response = 0;
    cout << "\n------------------------------------------------------------";
    cout << "\n\t\t  B A T T L E S H I P \t\t";
    cout << "\n\t\t      Main Menu \t\t";
    cout << "\n------------------------------------------------------------";
    cout << "\n\t\t     1.Start Game \t\t";
    cout << "\n\t\t     2.Exit Game \t\t";
    cout << "\n\t\tEnter Menu Selection (1-2) \t\t\n";
    cin >> response;
    return response;
}

void printMainMenu()
{
    switch (displayMenu())
    {
    case 1:
        beginGame();
        break;
    case 2:
        endGame();
        break;
    default:
        cout << "\n Sorry! Invalid Choice";
        // Loops the code if found invalid
        printMainMenu();
        break;
    }
}

int main()
{
    Board B;
    printMainMenu();
    return 0;
}