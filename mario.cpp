#include <iostream>
#include <cstring>

#include <cmath>
#include <windows.h>

using namespace std;

#define mapWidth 80
#define mapHeight 25

typedef struct SObject
{
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL IsFly;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brickLength;

void SetObjectPos(TObject *obj, float xPos, float yPos)
{
    (*obj).x = xPos;
    (*obj).y = yPos;
}
void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight)
{
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth;
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
}

BOOL IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj)
{
    (*obj).IsFly = TRUE;
    (*obj).vertSpeed += 0.05;
    SetObjectPos(obj, (*obj).x, (*obj).y + (*obj).vertSpeed);

    for (int i = 0; i < brickLength; i++)
        if (IsCollision(*obj, brick[i]))
        {
            (*obj).y -= (*obj).vertSpeed;
            (*obj).vertSpeed = 0;
            (*obj).IsFly = FALSE;
            break;
        }
}

BOOL IsPosInMap(int x, int y)
{
    return ((x >= 0) && (x <= mapWidth) && (y >= 0) && (y <= mapHeight));
}
void PutObjectMap(TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i, j))
                map[j][i] = '@';
}
void ClearMap()
{
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = '.';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        strcpy(map[j], map[0]);
}

void ShowMap()
{
    map[mapHeight - 1][mapWidth - 1] = '\0';
    for (int j = 0; j < mapHeight; j++)
        std::cout << map[j] << std::endl;
}

void setCur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void HorizonMoveMap(float dx)
{
    for (int i = 0; i < brickLength; i++)
    {
        brick[i].x += dx;
    }
    brick[0].x += dx;
}
BOOL IsCollision(TObject o1, TObject o2)
{
    return ((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

void CreateLevel()
{
    InitObject(&mario, 39, 10, 3, 3);

    brickLength = 5;
    brick = new TObject[brickLength];
    InitObject(brick + 0, 20, 20, 40, 5);
    InitObject(brick + 1, 60, 15, 10, 10);
    InitObject(brick + 2, 80, 20, 20, 5);
    InitObject(brick + 3, 120, 15, 10, 10);
    InitObject(brick + 4, 150, 20, 40, 5);
}

int main()
{
    CreateLevel();

    do
    {
        ClearMap();

        if ((mario.IsFly == FALSE) && (GetKeyState(VK_SPACE) < 0))
            mario.vertSpeed = -1;
        if (GetKeyState('A') < 0)
            HorizonMoveMap(1);
        if (GetKeyState('D') < 0)
            HorizonMoveMap(-1);

        VertMoveObject(&mario);
        for (int i = 0; i < brickLength; i++)
        {
            PutObjectMap(brick[i]);
        }
        PutObjectMap(mario);

        setCur(0, 0);
        ShowMap();

        Sleep(10);
    } while (GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}
