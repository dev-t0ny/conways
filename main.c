#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 50

void update(int generation, bool grid[HEIGHT][WIDTH]);
void render(int generation, bool grid[HEIGHT][WIDTH]);

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

        update(generation, grid);
        render(generation, grid);
        usleep(100000); 

    }
    
    return 0;
}


void update(int generation, bool grid[HEIGHT][WIDTH])
{
    printf("%d",generation);
    printf("\n");

}

void render(int generation, bool grid[HEIGHT][WIDTH])
{

}
