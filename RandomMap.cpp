#include "RandomMap.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

RandomMap::RandomMap(int size)
{
    size_ = size;
    obstacle_ = size / 8;   //设置障碍物的数量为地图大小除以8；
    GenerateObstacle(); //调用GenerateObstacle生成随机障碍物；
}

vector<Point> RandomMap::GenerateObstacle()
{
    // 添加两个障碍物点
    obstacle_point_.push_back(Point(int(size_/2), int(size_/2)));
    obstacle_point_.push_back(Point(int(size_/2), int(size_/2)-1));

    // 在地图的中间生成一个斜着的障碍物
    for (int i = size_/2 - 4; i < size_/2; i++)
    {
        obstacle_point_.push_back(Point(i, size_-i));
        obstacle_point_.push_back(Point(i, size_-i-1));
        obstacle_point_.push_back(Point(size_-i, i));
        obstacle_point_.push_back(Point(size_-i, i-1));
    }

    // 随机生成8个障碍物
    srand((unsigned)time(NULL));
    for (int i = 0; i < obstacle_; i++)
    {
        int x = rand() % 51;
        int y = rand() % 51;
        obstacle_point_.push_back(Point(x, y));

        // 障碍物的方向也是随机的
        if (rand() % 51 > 25)
        {
            for (int j = 0; j < size_/4; j++)
            {
                obstacle_point_.push_back(Point(x, y+j));
            }
        }
        else
        {
            for (int j = 0; j < size_/4; j++)
            {
                obstacle_point_.push_back(Point(x+j, y));
            }
        }
    }
    return obstacle_point_;
}

bool RandomMap::IsObstacle(int x, int y)
{
    for (auto p : obstacle_point_)
    {
        if (x == p.x_ && y == p.y_)
        {
            return true;
        }
    }
    return false;
}

void RandomMap::PrintMap()
{
    for (int i = size_-1; i >= 0; i--)
    {
        for (int j = 0; j < size_; j++)
        {
            if(IsObstacle(j, i))
            {
                cout << "X ";
            }else{
                cout << ". ";
            }
        }
        cout << endl;
    }
}