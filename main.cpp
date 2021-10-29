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

// console screen
char ConsoleScreen[ROWS_NUM][COLUMNS_NUM];
// player position
int player_x = 10;
int player_y = 10;


int main() 
{
    // fill the screen with corresponding chars
    FillScreen();

    // print out the screen
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