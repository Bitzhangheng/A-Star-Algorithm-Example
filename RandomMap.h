#pragma once
#include "Point.h"
#include <vector>
using namespace std;
class RandomMap
{
public:
    RandomMap(int size = 50);   // 地图的默认大小是50x50
    vector<Point> GenerateObstacle();   // 生成随机障碍物
    bool IsObstacle(int x, int y);  // 判断某个节点是否是障碍物
    void PrintMap();

    int size_;
    int obstacle_;
    vector<Point> obstacle_point_;
};