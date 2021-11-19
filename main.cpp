#include <iostream>

// define screen's shape
#define ROWS_NUM 29
#define COLUMNS_NUM 69

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
int map_points = 0;
// player values
int player_x = 10;
int player_y = 10;
int player_points = 0;
// game state
bool is_running = true;
bool player_won = false;
USER_INPUTS input = NONE;


int main() 
{
    // main function which handles all the game's flow
    
    HandleStart();

    while (is_running & !player_won) 
    {
        Inputs();
        HandleLogic();
        PrintScreen();
    }

    if (player_won) std::cout << "YOU WON!\n";
    else std::cout << "You have quited the game's loop\n";
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

void ApplyInputToPosition(int &new_player_x, int &new_player_y) 
{
    // changes player's position based on input variable

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
}

void HandleTeleportation(int &new_player_x, int &new_player_y) 
{
    // teleports player if needed

    // x axis
    if (new_player_x < 0) {
        new_player_x = COLUMNS_NUM - 1;
    } 
    new_player_x %= COLUMNS_NUM;
    // y axis
    if (new_player_y < 0) {
        new_player_y = ROWS_NUM - 1;
    } 
    new_player_y %= ROWS_NUM;
}

void ProcessCollisions(int &new_player_x, int &new_player_y) 
{
    // processes collisions with walls and points

    switch (ConsoleScreen[new_player_y][new_player_x]) {
        case WALL: // wall collistion
            new_player_x = player_x - ROWS_NUM;
            new_player_y = player_y - COLUMNS_NUM;
            break;
        case POINT: // point collision
            player_points++;
            map_points--;
            ConsoleScreen[new_player_y][new_player_x] = EMPTY;
            break;
        default:
            break;
    }
}

void HandleTrackPlayerProgress()
{
    // keeps track of map_points variable and 
    // sets player_won variable to true 
    // if player has collected all the points

    if (map_points == 0) player_won = true;
}

void HandleLogic() 
{
    // handles all the game's logic

    int new_player_x = player_x;
    int new_player_y = player_y;

    ApplyInputToPosition(new_player_x, new_player_y);
    HandleTeleportation(new_player_x, new_player_y);
    ProcessCollisions(new_player_x, new_player_y);
    HandleTrackPlayerProgress();

    player_x = new_player_x;
    player_y = new_player_y;
}

void PrintPoints()
{
    // prints out the string with player's collected points

    std::cout 
        << "Points collected: " 
        << player_points 
        << "/" 
        << player_points + map_points 
        << "\n";
}

void PrintScreen() 
{
    // prints the screen out to console

    // clear console
    system("clear"); // user "clear" instead of "CLS" cos I'm using MacOS
    
    PrintPoints();

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
    // returns true if one of the passed coordinates is at the border.
    // In other case returns false

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

    // declare points map and assign points' coordinates
    int points_map[ROW_LENGTH][COL_LENGTH] = {
        {5, 5}, 
        {8, 17},
        {10, 23},
        {2, 7}
    };

    // loop over the points map and insert points to the console screen
    for (size_t row = 0; row < ROW_LENGTH; row++)
    {
        int row_num = points_map[row][0];
        int col_num = points_map[row][1];
        ConsoleScreen[row_num][col_num] = POINT;
    }

    // assigns amount of points to map_points variable
    map_points = ROW_LENGTH;
}

void InsertTeleportationPaths() 
{
    // replaces some borders with empty tiles (portals)

    const int ROW_LENGTH = 46;
    const int COL_LENGTH = 2;

    // calculate the center of the column
    int column_center = COLUMNS_NUM / 2;

    // declare portals map and assign coordinates of empty tiles 
    int portals_map[ROW_LENGTH][COL_LENGTH] = {
        // left top
        {3, 0}, 
        {4, 0},
        {5, 0},
        // left bottom
        {3, COLUMNS_NUM - 1}, 
        {4, COLUMNS_NUM - 1},
        {5, COLUMNS_NUM - 1},
        // right top
        {ROWS_NUM - 4, 0}, 
        {ROWS_NUM - 5, 0},
        {ROWS_NUM - 6, 0},
        // right bottom
        {ROWS_NUM - 4, COLUMNS_NUM - 1}, 
        {ROWS_NUM - 5, COLUMNS_NUM - 1},
        {ROWS_NUM - 6, COLUMNS_NUM - 1},
        // top center
        {0, column_center}, 
        {0, column_center + 1},
        {0, column_center + 2},
        {0, column_center + 3},
        {0, column_center + 4},
        {0, column_center + 5},
        {0, column_center + 6},
        {0, column_center + 7},
        {0, column_center + 8},
        {0, column_center - 1},
        {0, column_center - 2},
        {0, column_center - 3},
        {0, column_center - 4},
        {0, column_center - 5},
        {0, column_center - 6},
        {0, column_center - 7},
        {0, column_center - 8},
        // bottom center
        {ROWS_NUM - 1, column_center}, 
        {ROWS_NUM - 1, column_center + 1},
        {ROWS_NUM - 1, column_center + 2},
        {ROWS_NUM - 1, column_center + 3},
        {ROWS_NUM - 1, column_center + 4},
        {ROWS_NUM - 1, column_center + 5},
        {ROWS_NUM - 1, column_center + 6},
        {ROWS_NUM - 1, column_center + 7},
        {ROWS_NUM - 1, column_center + 8},
        {ROWS_NUM - 1, column_center - 1},
        {ROWS_NUM - 1, column_center - 2},
        {ROWS_NUM - 1, column_center - 3},
        {ROWS_NUM - 1, column_center - 4},
        {ROWS_NUM - 1, column_center - 5},
        {ROWS_NUM - 1, column_center - 6},
        {ROWS_NUM - 1, column_center - 7},
        {ROWS_NUM - 1, column_center - 8},
    };

    // loop over the portals and insert portals to console screen
    for (size_t row = 0; row < ROW_LENGTH; row++)
    {
        int row_num = portals_map[row][0];
        int col_num = portals_map[row][1];
        ConsoleScreen[row_num][col_num] = EMPTY;
    }   
}

void FillScreen()
{
    // fills the screen with predetermined values

    // go over rows
    for (size_t row = 0; row < ROWS_NUM; row++)
    {
        // go over columns
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
    InsertTeleportationPaths();
}

bool IsPlayersPosition(size_t row, size_t col)
{
    // returns true if passed coordinates corresponds to players' ones. 
    // If not, returns false.

    if (row == player_y && col == player_x) return true;
    return false;
}
