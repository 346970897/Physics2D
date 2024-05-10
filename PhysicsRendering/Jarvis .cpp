//
// Created by Rey on 24-5-7.
//

#ifndef PHYSICS2D_JARVIS_H
#define PHYSICS2D_JARVIS_H
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

template<typename T>
double dic(const T &a,const T &b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

template<typename T>
int det(const T &a,const T &b,const T &c){
    return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
template<typename T>
void createJarvisConvexHull(const std::vector<T> &points, std::vector<T> &convexHull){
    //判断points数目
    if(points.size() < 3){
        std::cout << "The number of points is less than 3" << std::endl;
        return;
    }
    //排序并找出最左点位置
    sort(points.begin(), points.end());
    T leftPoint = points[0];
    convexHull.push_back(leftPoint);
    int leftPointIndex = 0;
    do{
        int nextPointIndex = 0;
        for(int index =0;index<points.size();index++){
            if(index==leftPointIndex||index==nextPointIndex){
                continue;
            }
            //查找一个最右点，并将其下标赋值给nextPointIndex
            int ret = det(points[leftPointIndex],points[nextPointIndex],points[index]);
            if(ret<0){
                nextPointIndex = index;
            }else if(ret==0){
                if(dic(points[leftPointIndex],points[nextPointIndex])>dic(points[leftPointIndex],points[index]){
                    nextPointIndex = index;
                }
            }
        }
        leftPointIndex = nextPointIndex;
        convexHull.push_back(points[nextPointIndex]);
    }while(leftPointIndex != 0

}

//测试
int main() {
    std::vector<std::pair<int, int>> points = {{0, 3},
                                               {1, 1},
                                               {2, 2},
                                               {4, 4},
                                               {0, 0},
                                               {1, 2},
                                               {3, 1},
                                               {3, 3}};
    std::vector<std::pair<int, int>> convexHull;
    createJarvisConvexHull(points, convexHull);
    for (auto &point:convexHull) {
        std::cout << point.first << " " << point.second << std::endl;
    }
    return 0;

}

#endif //PHYSICS2D_JARVIS_H
