#ifndef CONVEXHULL_H
#define CONVEXHULL_H
#include<iostream>
#include<vector>
#include"PhysicsVector.h"
typedef PhysicsVector Vector3D;
enum CONVEXHULL_ALGORIM
{
	JEARIC=10000,
	GRAHAM,
	ANDREW
};
enum CONVEXHULL_CALTYPE
{
	X=2000,
	Y,
	Z
};
template<typename T>
class ConvexHull
{
	
public:
	ConvexHull()=default;
	~ConvexHull() = default;
	ConvexHull(int type, int calType) :m_type(type), m_calType(calType) {};
	std::vector<Vector3D> ConvexHull_Graham(std::vector<Vector3D>& points);
	std::vector<Vector3D> ConvexHull_Jearic(std::vector<Vector3D>& points);
	std::vector<Vector3D> ConvexHull_Andrew(std::vector<Vector3D>& points);
	//根据不同的算法计算凸包
	bool ConvexHullAlgorim(std::vector<Vector3D>& points, std::vector<Vector3D>& convexHull, CONVEXHULL_ALGORIM type= m_type);
private:
	//计算从p1到p2的向量长度
	 double dic(const T& p1, const T& p2);
	//计算p1->p2 和 p1->p3的叉乘，如果结果大于0则p1->p2在p1->p3的顺时针方向
	 double det(const T& p1, const T& p2, const T& p3);
	 int m_type; //凸包算法类型
	 int m_calType; //计算方式
};

#endif // !CONVEXHULL_H

