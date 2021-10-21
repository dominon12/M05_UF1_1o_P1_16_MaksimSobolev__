#include <iostream>

// define screen's shape
#define ROWS_NUM 29
#define COLUMNS_NUM 119

// define cell's chars
#define BORDER_CHAR '#'
#define NORMAL_CHAR '-'
#define PLAYER_CHAR '0'


bool is_border(size_t row, size_t col)
{
    if (row == 0 
        || row == ROWS_NUM - 1 
        || col == 0 
        || col == COLUMNS_NUM - 1) 
        return true;
    return false;
}

int main() 
{
    // console screen
    char ConsoleScreen[ROWS_NUM][COLUMNS_NUM];
    // player position
    int player_x = 10;
    int player_y = 10;

    // go throw rows
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        // go throw columns
        for (size_t col = 0; col < COLUMNS_NUM; col++)
        {
            // assign value to a cell
            if (is_border(row, col)) 
                ConsoleScreen[row][col] = BORDER_CHAR;
            else 
                ConsoleScreen[row][col] = NORMAL_CHAR;
        }
    }

    // put player to the screen
    ConsoleScreen[player_x][player_y] = PLAYER_CHAR;


    // print out the screen
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        for (size_t col = 0; col < COLUMNS_NUM; col++)
        {
            // print cell's value out
            std::cout << ConsoleScreen[row][col];
        }
        std::cout << std::endl;
    }
}