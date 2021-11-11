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
    // main function which handles all the game's flow
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
    // gets inputs from the player and assigns needed value to input variable
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
    // handles all the game logic
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
    // prints matrix of values to the screen

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
    // handles game's start
    FillScreen();
    PrintScreen();
}

bool IsBorder(size_t row, size_t col)
{
    // returns true if one of passed coordinates is at the border. In other case returns false
    if (row == 0 
        || row == ROWS_NUM - 1 
        || col == 0 
        || col == COLUMNS_NUM - 1) 
        return true;
    return false;
}

void InsertPoints()
{
    // inserts points to the map
    const int ROW_LENGTH = 4;
    const int COL_LENGTH = 2;

    int points_map[ROW_LENGTH][COL_LENGTH] = {
        {5, 5}, 
        {8, 17},
        {10, 23},
        {2, 7}
    };
    for (size_t row = 0; row < ROW_LENGTH; row++)
    {
        int row_num = points_map[row][0];
        int col_num = points_map[row][1];
        ConsoleScreen[row_num][col_num] = POINT;
}
}

void FillScreen()
{
    // fills the screen with predetermined values

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
    InsertPoints();
}

bool IsPlayersPosition(size_t row, size_t col)
{
    // returns true if passed coordinates corresponds to players' ones. If not, returns false.
    if (row == player_y && col == player_x) return true;
    return false;
}
