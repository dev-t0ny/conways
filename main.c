#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 50

void update(bool grid[HEIGHT][WIDTH]);
void render(int generation, bool grid[HEIGHT][WIDTH]);

struct Position
{
    int x;
    int y;
};


int main()
{
    int generation = 0;
    bool grid[HEIGHT][WIDTH];
    
    for (int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        { 
            grid[i][j] = false;
        }
    }

    while (1)
    {
        generation++;

        update(grid);
        render(generation, grid);
        usleep(100000); 

    }
    
    return 0;
}

void clearScreen()
{
    printf("\033[2J\033[H");
    fflush(stdout);
}



int countNeighbours(struct Position p, bool grid[HEIGHT][WIDTH])
{
    int count = 0;
    
    for (int i = -1; i < 1; i++)
    {
        for (int j = -1; j < 1; j++)
        {
            struct Position currentCheck = {p.x + j, p.y + i };
            bool isInBounds = false;

            if (currentCheck.y < HEIGHT && currentCheck.x < WIDTH && currentCheck.x > 0 && currentCheck.y > 0)
            {
                isInBounds = true;
            }

            if (grid[currentCheck.y][currentCheck.x])
            {
                count++;
            }
        }
    }

    return count;
}


void update(bool grid[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            struct Position currentPos = {i,j};
            int neighbourCount = countNeighbours(currentPos, grid);
           
            //dead 
            if (grid[currentPos.y][currentPos.x])
            {
                if (neighbourCount == 3)
                {
                    grid[currentPos.y][currentPos.x] = true;     
                }
                
            }
           
            //alive
             else
            {   
                if (neighbourCount == 2 || neighbourCount == 3)
                {
                            
                }
                else
                {   
                    grid[currentPos.y][currentPos.x] = false;
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
                printf("%s", "■");
            }
            else
            {
               printf("%s","□");    
            }
        }
    }
}
