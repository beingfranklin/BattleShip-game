//  Name : Franklin Antony
//  ID : 200626510
//  College Username : ec20076

#include <iostream>
using namespace std;

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
                    if (integerCharX + length > 7)
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
        cout << "\nInvalid entry. Please try again! \n";
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

void displayBoardState(int fireCount)
{
    int turn = fireCount;
    cout << "\n_____________________________";
    if(turn>0)
        cout << "\n\nTurn " << turn;
    cout << "\nDisplaying the current board state\n\n";
    // printBoard(hitBoard);
}

void fireShip(char playerName, char hitBoard[8][8], char shipBoard[8][8], int totalCells)
{
    char X, Y;
    int fireCount = 0, hitCells = 0;
    cout << "\nPlayer " << playerName << " enter coordinates to fire:";
    cout << "\n____________________________________";
    printBoard(hitBoard);
    do
    {
        displayBoardState(fireCount);
        getCoordinates(X, Y);
        int integerCharY = Y - '0';
        int integerCharX = tolower(X) - 97;
        if (checkValidY(Y) && checkValidX(X) &&
            (hitBoard[integerCharY - 1][integerCharX] != 'M' ||
             hitBoard[integerCharY - 1][integerCharX] != 'H'))
        {
            cout << "\nYou fired at X: " << X << " and "
                 << " Y: " << Y;
            if (shipBoard[integerCharY - 1][integerCharX] == 'S')
            {
                hitBoard[integerCharY - 1][integerCharX] = 'H';
                cout << "\nYou have a hit!\n";
                hitCells++;
                printBoard(hitBoard);
            }
            else
            {
                hitBoard[integerCharY - 1][integerCharX] = 'M';
                cout << "\nYou have a miss!\n";
                printBoard(hitBoard);
            }
            fireCount++;
        }
        else
        {
            cout << "\n Invalid points. Please try again";
        }

    } while (hitCells != totalCells);

    if (hitCells != 0 && hitCells == totalCells)
    {
        cout << "\nYou have won!";
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
void resetShipBoard(char shipBoard[8][8])
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            shipBoard[i][j] = ' ';
}

void beginGame()
{
    char playerName, X, Y;
    int count = 0, totalCells = 0;
    char shipBoard[8][8], hitBoard[8][8];
    resetShipBoard(shipBoard);
    resetShipBoard(hitBoard);
    getPlayerName(playerName);

    addShipMenu();
    while (count < 2)
    {
        addShips(count, shipBoard, totalCells);
        if (count == 5)
        {
            enterToContinue();
        }
    }

    fireShip(playerName, hitBoard, shipBoard, totalCells);
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
    printMainMenu();
    return 0;
}