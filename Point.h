#pragma once

class Point
{
public:
    Point(int x, int y):x_(x), y_(y){};
    
    int x_;
    int y_;
    double cost_;
    Point *parent_;
};