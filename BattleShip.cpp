//  Name : Franklin Antony
//  ID : 200626510
//  College Username : ec20076

#include <iostream>
using namespace std;

// Added funtion protoype to reuse the printMenu()
void printMenu();

void beginGame()
{
    char playerName, X, Y;
    cout << "\nEnter player name:\n";
    cin >> playerName;
    getCoordinates(X,Y);
    cout << "\nYou have entered the coordinates X: " << X << " and Y:" << Y << "\n";
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
        printMenu();
        break;
    }
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

void printMenu()
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
        printMenu();
        break;
    }
}

int main()
{
    printMenu();
    return 0;
}