#include <iostream>

// define screen's shape
#define ROWS_NUM 29
#define COLUMNS_NUM 119

// define cell's chars
#define BORDER_CHAR '#'
#define NORMAL_CHAR '-'
#define PLAYER_CHAR '0'

// define functions to use them before declaring
void FillScreen();
void PrintScreen();
bool IsBorder(size_t row, size_t col);
bool IsPlayersPosition(size_t row, size_t col);
void Inputs();
void HandleStart();

// console screen
char ConsoleScreen[ROWS_NUM][COLUMNS_NUM];
// player position
int player_x = 10;
int player_y = 10;
// game state
bool is_running = true;


int main() 
{
    HandleStart();

    while (is_running) 
    {
        // get player's inputs
        Inputs();

        // print out the screen
        PrintScreen();
    }

    std::cout << "You have quited the game" << std::endl;
}

void HandleStart()
{
    FillScreen();
    PrintScreen();
}

bool IsBorder(size_t row, size_t col)
{
    if (row == 0 
        || row == ROWS_NUM - 1 
        || col == 0 
        || col == COLUMNS_NUM - 1) 
        return true;
    return false;
}

void FillScreen()
{
    // go throw rows
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        // go throw columns
        for (size_t col = 0; col < COLUMNS_NUM; col++)
        {
            // assign value to a cell
            if (IsBorder(row, col)) 
                ConsoleScreen[row][col] = BORDER_CHAR;
            else 
                ConsoleScreen[row][col] = NORMAL_CHAR;
        }
    }
}

bool IsPlayersPosition(size_t row, size_t col)
{
    if (row == player_y && col == player_x) return true;
    return false;
}

void PrintScreen() 
{
    // clear console
    system("clear"); // user "clear" instead of "CLS" cos I'm using MacOS
    
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        for (size_t col = 0; col < COLUMNS_NUM; col++)
        {
            if (IsPlayersPosition(row, col)) std::cout << PLAYER_CHAR; // print player's char
            else std::cout << ConsoleScreen[row][col]; // print cell's value out
        }
        std::cout << std::endl;
    }
}

void Inputs()
{
    char input;

    std::cin >> input;

    switch(input)
    {
        case 'S':
        case 's':
            player_y++;
            break;
        case 'W':
        case 'w':
            player_y--;
            break;
        case 'D':
        case 'd':
            player_x++;
            break;
        case 'A':
        case 'a':
            player_x--;
            break;
        case 'Q':
        case 'q':
            is_running = false;
            break;
        default:
            break;
    }
}