#include <stdio.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_OBJECTS 100

typedef enum { LINE, RECTANGLE, CIRCLE, TRIANGLE } ShapeType;

typedef struct {
    int id;
    ShapeType type;
    int x1, y1, x2, y2, x3, y3; 
    int radius;                 
    int active;                 
} GraphicsObject;

char canvas[HEIGHT][WIDTH];
GraphicsObject objects[MAX_OBJECTS];
int objectCount = 0;
int nextId = 1;

void clearCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) canvas[i][j] = '_';
    }
}

void displayCanvas() {
    printf("\n--- Current Canvas ---\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) printf("%c ", canvas[i][j]);
        printf("\n");
    }
}

void plotPoint(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) canvas[y][x] = '*';
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

void drawRectangle(int x, int y, int w, int h) {
    drawLine(x, y, x + w, y); drawLine(x + w, y, x + w, y + h);
    drawLine(x + w, y + h, x, y + h); drawLine(x, y + h, x, y);
}

void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r, d = 3 - 2 * r;
    while (y >= x) {
        plotPoint(xc + x, yc + y); plotPoint(xc - x, yc + y);
        plotPoint(xc + x, yc - y); plotPoint(xc - x, yc - y);
        plotPoint(xc + y, yc + x); plotPoint(xc - y, yc + x);
        plotPoint(xc + y, yc - x); plotPoint(xc - y, yc - x);
        x++;
        if (d > 0) { y--; d = d + 4 * (x - y) + 10; } 
        else d = d + 4 * x + 6;
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2); drawLine(x2, y2, x3, y3); drawLine(x3, y3, x1, y1);
}

void renderAll() {
    clearCanvas();
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].active) {
            switch (objects[i].type) {
                case LINE: drawLine(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case RECTANGLE: drawRectangle(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case CIRCLE: drawCircle(objects[i].x1, objects[i].y1, objects[i].radius); break;
                case TRIANGLE: drawTriangle(objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2, objects[i].x3, objects[i].y3); break;
            }
        }
    }
}

void addObject() {
    int choice;
    printf("\nSelect shape:\n1. Line\n2. Rectangle\n3. Circle\n4. Triangle\nChoice: ");
    scanf("%d", &choice);

    GraphicsObject obj;
    obj.id = nextId++;
    obj.active = 1;

    switch (choice) {
        case 1: obj.type = LINE; printf("Enter x1 y1 x2 y2: "); scanf("%d %d %d %d", &obj.x1, &obj.y1, &obj.x2, &obj.y2); break;
        case 2: obj.type = RECTANGLE; printf("Enter top-left x, y, width, height: "); scanf("%d %d %d %d", &obj.x1, &obj.y1, &obj.x2, &obj.y2); break;
        case 3: obj.type = CIRCLE; printf("Enter center x, y, radius: "); scanf("%d %d %d", &obj.x1, &obj.y1, &obj.radius); break;
        case 4: obj.type = TRIANGLE; printf("Enter x1 y1 x2 y2 x3 y3: "); scanf("%d %d %d %d %d %d", &obj.x1, &obj.y1, &obj.x2, &obj.y2, &obj.x3, &obj.y3); break;
        default: return;
    }
    objects[objectCount++] = obj;
    renderAll();
}
void listObjects() {
    printf("\n--- Active Objects ---\n");
    for (int i = 0; i < objectCount; i++) {
        if (objects[i].active) {
            printf("ID: %d | Type: %d\n", objects[i].id, objects[i].type);
        }
    }
}

void deleteObject() {
    listObjects();
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < objectCount; i++) {
        if (objects[i].id == id && objects[i].active) {
            objects[i].active = 0;
            printf("Object deleted.\n");
            renderAll();
            return;
        }
    }
    printf("Object not found.\n");
}

void modifyObject() {
    listObjects();
    int id;
    printf("Enter ID to modify: ");
    scanf("%d", &id);

    for (int i = 0; i < objectCount; i++) {
        if (objects[i].id == id && objects[i].active) {
            if (objects[i].type == LINE) {
                printf("Enter new x1 y1 x2 y2: ");
                scanf("%d %d %d %d", &objects[i].x1, &objects[i].y1, &objects[i].x2, &objects[i].y2);
            } else if (objects[i].type == RECTANGLE) {
                printf("Enter new top-left x, y, width, height: ");
                scanf("%d %d %d %d", &objects[i].x1, &objects[i].y1, &objects[i].x2, &objects[i].y2);
            } else if (objects[i].type == CIRCLE) {
                printf("Enter new center x, y, radius: ");
                scanf("%d %d %d", &objects[i].x1, &objects[i].y1, &objects[i].radius);
            } else if (objects[i].type == TRIANGLE) {
                printf("Enter new x1 y1 x2 y2 x3 y3: ");
                scanf("%d %d %d %d %d %d", &objects[i].x1, &objects[i].y1, &objects[i].x2, &objects[i].y2, &objects[i].x3, &objects[i].y3);
            }
            renderAll();
            return;
        }
    }
    printf("Object not found.\n");
}

int main() {
    clearCanvas();
    int choice;

    do {
        displayCanvas();
        printf("\n--- 2D Graphics Editor ---\n");
        printf("1. Add Object\n2. Delete Object\n3. Modify Object\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addObject(); break;
            case 2: deleteObject(); break;
            case 3: modifyObject(); break;
        }
    } while (choice != 4);

    return 0;
}
