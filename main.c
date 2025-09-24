#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 50

void update(bool grid[HEIGHT][WIDTH], bool nextGrid[HEIGHT][WIDTH]);
void render(int generation, bool grid[HEIGHT][WIDTH]);
void fill(bool grid[HEIGHT][WIDTH]);


struct Position
{
    int x;
    int y;
};


int main()
{
    int generation = 0;
    bool grid[HEIGHT][WIDTH];
    bool nextGrid[HEIGHT][WIDTH];     
    
    for (int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        { 
            grid[i][j] = false;
            nextGrid[i][j] = false;
        }
    }

    fill(grid);

    while (1)
    {
        generation++;
        
        render(generation, grid);
        update(grid,nextGrid);
       
        //grid = nextGrid;
        
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                grid[i][j] = nextGrid[i][j];
            }
        }

        usleep(100000); 
        //sleep(2);
    }
    
    return 0;
}

void clearScreen()
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void fill(bool grid[HEIGHT][WIDTH])
{
    int choix = 1;

    // petit glider
    if (choix == 1)
    {
        grid[1][2] = true; 
        grid[2][3] = true; 
        grid[3][1] = true;
        grid[3][2] = true;
        grid[3][3] = true;
    }

    choix = 2;
    // spaceship
    if (choix == 2)
    {
    grid[0][1] = true;
    grid[0][4] = true;

    grid[1][0] = true;
    grid[1][5] = true;

    grid[2][5] = true;

    grid[3][0] = true;
    grid[3][4] = true;
    grid[3][5] = true;
    }
}


int countNeighbours(struct Position p, bool grid[HEIGHT][WIDTH])
{
    int count = 0;
    
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            struct Position currentCheck = {p.x + j, p.y + i };
            bool isInBounds = false;
            bool isValid = false;

            if (i == 0 && j == 0)
            {
                continue;
            }

            if (currentCheck.y < HEIGHT && currentCheck.x < WIDTH && currentCheck.x >= 0 && currentCheck.y >= 0)
            {
                isInBounds = true;
            }

            if (isInBounds)
            {
                if (grid[currentCheck.y][currentCheck.x]) 
                {
                    count++;
                }
            }
        }
    }
        return count;
}


void update(bool grid[HEIGHT][WIDTH], bool nextGrid[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            struct Position currentPos = {j,i};
            int neighbourCount = countNeighbours(currentPos, grid);
//            printf("%d", neighbourCount); 
//           printf("\n");
            // alive 
            if (grid[currentPos.y][currentPos.x])
            {
                //underpopulation
                if (neighbourCount < 2)
                {
                    nextGrid[currentPos.y][currentPos.x] = false;
                }
                //redondant mais jsuis visuel en ce moment
                else if (neighbourCount == 2 || neighbourCount == 3)
                {
                    nextGrid[currentPos.y][currentPos.x] = true;
                }
                //overpopulation
                else if (neighbourCount > 3)
                {
                    nextGrid[currentPos.y][currentPos.x] = false;
                }
            }
           
            // dead
             else
            {

                //reproduction
                if (neighbourCount == 3)
                {
                    nextGrid[currentPos.y][currentPos.x] = true;
                }
            }
            
             
        }
    }
}

void render(int generation, bool grid[HEIGHT][WIDTH])
{
    clearScreen();

    for (int i = 0; i < HEIGHT;i++)
    {
        printf("\n");
        for (int j = 0; j < WIDTH;j++)
        {
            bool currentSelection = grid[i][j];

            if (currentSelection)
            {
                printf("%s", " ■ ");
            }
            else
            {
               printf("%s"," □ ");    
            }
        }
    }
    printf("%s","\n generation: ");
    printf("%d",generation);
    fflush(stdout);
}
