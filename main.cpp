#include <iostream>

// define screen's shape
#define ROWS_NUM 29
#define COLUMNS_NUM 119

// define functions to use them before declaring
void FillScreen();
bool IsBorder(size_t row, size_t col);
void HandleStart();
bool IsPlayersPosition(size_t row, size_t col);
void Inputs();
void HandleLogic();
void PrintScreen();

// define cell's chars
enum MAP_TILES { EMPTY = ' ', WALL = '#', POINT = '.',PLAYER = '0' };
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };

// console screen
MAP_TILES ConsoleScreen[ROWS_NUM][COLUMNS_NUM];
// player's position
int player_x = 10;
int player_y = 10;
// game state
bool is_running = true;
USER_INPUTS input = NONE;


int main() 
{
    HandleStart();

    while (is_running) 
    {
        Inputs();
        HandleLogic();
        PrintScreen();
    }

    std::cout << "You have quited the game's loop" << std::endl;
}

void Inputs()
{
    char raw_input;

    std::cin >> raw_input;

    switch(raw_input)
    {
        case 'S':
        case 's':
            input = UP;
            break;
        case 'W':
        case 'w':
            input = DOWN;
            break;
        case 'D':
        case 'd':
            input = RIGHT;
            break;
        case 'A':
        case 'a':
            input = LEFT;
            break;
        case 'Q':
        case 'q':
            input = QUIT;
            break;
        default:
            input = NONE;
            break;
    }
}

void HandleLogic() 
{
    int new_player_x = player_x;
    int new_player_y = player_y;

    switch (input) 
    {
        case UP:
            new_player_y++;
            break;
        case DOWN:
            new_player_y--;
            break;
        case RIGHT:
            new_player_x++;
            break;
        case LEFT:
            new_player_x--;
            break;
        case QUIT:
            is_running = false;
            break;
        default:
            break;
    }

    if (!IsBorder(new_player_y, new_player_x)) 
    {
        player_x = new_player_x;
        player_y = new_player_y;
    }
}

void PrintScreen() 
{
    // clear console
    system("clear"); // user "clear" instead of "CLS" cos I'm using MacOS
    
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        for (size_t col = 0; col < COLUMNS_NUM; col++)
        {
            if (IsPlayersPosition(row, col)) std::cout << (char)PLAYER; // print player's char
            else std::cout << (char)ConsoleScreen[row][col]; // print cell's value out
        }
        std::cout << std::endl;
    }
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
                ConsoleScreen[row][col] = WALL;
            else 
                ConsoleScreen[row][col] = EMPTY;
        }
    }
}

bool IsPlayersPosition(size_t row, size_t col)
{
    if (row == player_y && col == player_x) return true;
    return false;
}
