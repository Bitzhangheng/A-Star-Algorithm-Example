#include "AStar.h"
#include <vector>
#include <math.h>
#include <iostream>
#include <queue>

using namespace std;

double AStar::BaseCost(Point p)
{
    int x_dis = p.x_;
    int y_dis = p.y_;

    return x_dis + y_dis + (sqrt(2) - 2) * min(x_dis, y_dis);
}

double AStar::HeuristicCost(Point p)
{
    int x_dis = map_.size_ - p.x_;
    int y_dis = map_.size_ - p.y_;

    return x_dis + y_dis + (sqrt(2) - 2) * min(x_dis, y_dis);
}


double AStar::TotalCost(Point p)
{
    return BaseCost(p) + HeuristicCost(p);
}

bool AStar::IsValidPoint(int x, int y)
{
    if (x < 0 || y < 0)
    {
        return false;
    }
    if (x >= map_.size_ || y >= map_.size_)
    {
        return false;
    }
    return !map_.IsObstacle(x, y);
}

bool AStar::IsInPointList(Point p, vector<Point> point_list)
{
    for (auto point : point_list)
    {
        if (p.x_ == point.x_ && p.y_ == point.y_)
        {
            return true;
        }
    }
    return false;
}

bool AStar::IsInOpenList(Point p)
{
    return IsInPointList(p, open_set_);
}

bool AStar::IsInCloseList(Point p)
{
    return IsInPointList(p, close_set_);
}

bool AStar::IsStartPoint(Point p)
{
    return p.x_ == 0 && p.y_ == 0;
}

bool AStar::IsEndPoint(Point p)
{
    return p.x_ == map_.size_ - 1 && p.y_ == map_.size_ - 1;
}

vector<Point> AStar::Run()
{
    Point start_point = Point(0, 0);
    start_point.cost_ = 0;
    open_set_.push_back(start_point);
    vector<Point> path;

    while (true)
    {
        int index = SelectPointInOpenList();
        if (index < 0)
        {
            cout << "No path found, algorithm failed!" << endl;
            break;
        }
        Point p = open_set_[index];
        if (IsEndPoint(p))
        {
            path = BuildPath(p);
            break;
        }
        open_set_.erase(open_set_.begin() + index);
        close_set_.push_back(p);

        int x = p.x_;
        int y = p.y_;

        ProcessPoint(x - 1, y + 1, p);
        ProcessPoint(x, y + 1, p);
        ProcessPoint(x + 1, y + 1, p);
        ProcessPoint(x - 1, y, p);
        ProcessPoint(x + 1, y, p);
        ProcessPoint(x - 1, y - 1, p);
        ProcessPoint(x, y - 1, p);
        ProcessPoint(x + 1, y - 1, p);
    }
    return path;
}

void AStar::ProcessPoint(int x, int y, Point parent)
{
    if (!IsValidPoint(x, y))
    {
        return; // Do nothing for invalid point
    }
    Point p = Point(x, y);
    if (IsInCloseList(p))
    {
        return; // Do nothing for visited point
    }
    // cout << "Process Point [ " << p.x_ << " " << p.y_ << " ], "
    //      << "cost: " << p.cost_ << endl;
    if (!IsInOpenList(p))
    {
        Point *parent_ptr = new Point(parent);
        p.parent_ = parent_ptr;
        p.cost_ = TotalCost(p);
        open_set_.push_back(p);
    }
}

int AStar::SelectPointInOpenList()
{
    int index = 0;
    double min_cost = __DBL_MAX__;
    for (int i = 0; i < open_set_.size(); i++)
    {
        double cost = TotalCost(open_set_[i]);
        if (cost < min_cost)
        {
            index = i;
            min_cost = cost;
        }
    }
    return index;
}

vector<Point> AStar::BuildPath(Point p)
{
    vector<Point> path;
    while (true)
    {
        path.push_back(p);
        if (IsStartPoint(p))
        {
            break;
        }
        else
        {
            p = *(p.parent_);
        }
    }
    return path;
}