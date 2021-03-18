#pragma once
#include "RandomMap.h"
#include "Point.h"
#include <vector>

using namespace std;
class AStar
{
public:
    AStar(RandomMap map):map_(map){};
    // 节点到起点的移动代价
    double BaseCost(Point p);
    // 节点到终点的启发函数
    double HeuristicCost(Point p);
    // 代价总和
    double TotalCost(Point p);

    // 判断点是否有效，不在地图内部或者障碍物所在点都是无效的
    bool IsValidPoint(int x, int y);
    // 判断点是否在某个集合中
    bool IsInPointList(Point p, vector<Point> point_list);
    // 判断点是否在open_set中
    bool IsInOpenList(Point p);
    // 判断点是否在close_set中
    bool IsInCloseList(Point p);

    // 判断点是否是起点
    bool IsStartPoint(Point p);
    // 判断点是否是终点
    bool IsEndPoint(Point p);

    // A*主函数逻辑
    vector<Point> Run();

    // 针对每一个节点进行处理：如果是没有处理过的节点，则计算优先级设置父节点，并且添加到open_set中
    void ProcessPoint(int x, int y, Point parent);
    // 从open_set中找到优先级最高的节点，返回其索引
    int SelectPointInOpenList();
    // 从终点往回沿着parent构造结果路径
    vector<Point> BuildPath(Point p);

    RandomMap map_;
    vector<Point> open_set_;
    vector<Point> close_set_;
};