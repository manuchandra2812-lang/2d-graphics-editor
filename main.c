#include <stdio.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_OBJECTS 100

typedef enum { LINE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x1, y1, x2, y2; 
    int active;
} GraphicsObject;

char canvas[HEIGHT][WIDTH];
GraphicsObject objects[MAX_OBJECTS];
int objectCount = 0;
int nextId = 1;

void clearCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas() {
    printf("\n--- Current Canvas ---\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
    printf("----------------------\n");
}

void plotPoint(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        plotPoint(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x1 += sx; }
        if (e2 <= dx) { err += dx; y1 += sy; }
    }
}

void renderAll() {
    clearCanvas();
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].active) {
            if (objects[i].type == LINE) {
                drawLine(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2);
            }
        }
    }
}

void addObject() {
    if (objectCount >= MAX_OBJECTS) return;
    
    GraphicsObject obj;
    obj.id = nextId++;
    obj.active = 1;
    obj.type = LINE;
    
    printf("Add Line - Enter x1 y1 x2 y2: ");
    scanf("%d %d %d %d", &obj.x1, &obj.y1, &obj.x2, &obj.y2);
    
    objects[objectCount++] = obj;
    renderAll();
}

int main() {
    clearCanvas();
    int choice;

    do {
        displayCanvas();
        printf("\n1. Add Line\n2. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) addObject();
    } while (choice != 2);

    return 0;
}
