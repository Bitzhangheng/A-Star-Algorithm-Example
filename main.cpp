#include <iostream>
#include "RandomMap.h"
#include "AStar.h"
#include <algorithm>

using namespace std;

int main()
{
    RandomMap map = RandomMap(50);
    //map.PrintMap();

    AStar a_star(map);

    vector<Point> path = a_star.Run();

    for (int i = map.size_-1; i >= 0; i--)
    {
        for (int j = 0; j < map.size_; j++)
        {
            if(map.IsObstacle(j, i))
            {
                cout << "X ";
            }else{
                bool is_path_point = false;
                for (auto p:path)
                {
                    if (p.x_ == j && p.y_ == i)
                    {
                        is_path_point = true;
                        break;
                    }
                }
                if(is_path_point)
                {
                    cout << "* ";
                } else {
                    cout << ". ";
                }                
            }
        }
        cout << endl;
    }
    //system("pause");
    return 0;
}