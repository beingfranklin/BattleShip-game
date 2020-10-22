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

void getCoordinates(char &X, char &Y)
{
    do
    {

        cout << "\nEnter the X coordinate (A-H):\n";
        cin >> X;
        if (!((X >= 'A' && X <= 'H') || (X >= 'a' && X <= 'h')))
        {
            cout << "Invalid entry. Please try again";
        }
    } while (!((X >= 'A' && X <= 'H') || (X >= 'a' && X <= 'h')));

    do
    {
        cout << "\nEnter the Y coordinate (1-8):\n";
        cin >> Y;
        if (!(Y >= '1' && Y <= '8'))
        {
            cout << "Invalid entry. Please try again";
        }
    } while (!(Y >= '1' && Y <= '8'));
}

void addShips(int &count)
{
    char X, Y, direction = 'z';
    cout << "\n----- Adding Ship " << count + 1 << " of 5 ----- ";
    getCoordinates(X, Y);
    getDirection(direction);
    cout << "\nYou have added a ship to the coordinates X: " << X << " and Y:" << Y << " in " << direction << " direction\n\n";
    count++;
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
    cout << "\n\nTurn " << turn + 1;
    cout << "\nDisplaying the current board state\n\n";
}

void fireShip(char playerName)
{
    char X, Y;
    int fireCount = 0;
    cout << "\nPlayer " << playerName << " enter coordinates to fire:";
    cout << "\n____________________________________";
    while (fireCount < 2)
    {
        displayBoardState(fireCount);
        getCoordinates(X, Y);
        cout << "\nYou fired at X: " << X << " and "
             << " Y: " << Y;
        fireCount++;
    }
}

void beginGame()
{
    char playerName, X, Y;
    int count = 0;
    getPlayerName(playerName);

    while (count < 2)
    {
        addShips(count);
        if (count == 2)
        {
            enterToContinue();
        }
    }

    fireShip(playerName);
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