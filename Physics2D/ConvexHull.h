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
	//���ݲ�ͬ���㷨����͹��
	bool ConvexHullAlgorim(std::vector<Vector3D>& points, std::vector<Vector3D>& convexHull, CONVEXHULL_ALGORIM type= m_type);
private:
	//�����p1��p2����������
	 double dic(const T& p1, const T& p2);
	//����p1->p2 �� p1->p3�Ĳ�ˣ�����������0��p1->p2��p1->p3��˳ʱ�뷽��
	 double det(const T& p1, const T& p2, const T& p3);
	 int m_type; //͹���㷨����
	 int m_calType; //���㷽ʽ
};

#endif // !CONVEXHULL_H

