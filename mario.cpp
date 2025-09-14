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
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;

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
}
void PutObjectMap(TObject obj)
{
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
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

int main()
{
    InitObject(&mario, 39, 10, 3, 3);

    do
    {
        ClearMap();
        PutObjectMap(mario);
        ShowMap();
    } while (GetKeyState(VK_ESCAPE) >= 0);
    return 0;
}
