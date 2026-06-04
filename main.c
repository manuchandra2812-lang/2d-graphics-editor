#include <stdio.h>

#define HEIGHT 20
#define WIDTH 40

char canvas[HEIGHT][WIDTH];

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void drawLine(int row, int startCol, int endCol)
{
    int j;

    for(j = startCol; j <= endCol; j++)
    {
        canvas[row][j] = '*';
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    printf("===== 2D GRAPHICS EDITOR =====\n\n");

    initializeCanvas();

    drawLine(5, 10, 30);

    displayCanvas();

    return 0;
}
