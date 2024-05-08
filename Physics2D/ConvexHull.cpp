#include "ConvexHull.h"
#include <algorithm>
#include <stack>
template<typename T>
std::vector<Vector3D> ConvexHull<T>::ConvexHull_Graham(std::vector<Vector3D>& points)
{
	std::vector<Vector3D> convexHull;
	// 对点进行排序
	int points_size = points.size();
	int min_index = 0;
	// 找出vector中x坐标最小的点，相等的话找出y坐标最小的点
	for (int i = 1; i < points_size; i++)
	{
		if (points[i].x < points[min_index].x)
		{
			min_index = i;
		}
		else if (points[i].x == points[min_index].x)
		{
			if (points[i].y < points[min_index].y)
			{
				min_index = i;
			}
		}
	}
	// 将最小的点放在第一个位置
	std::swap(points[0], points[min_index]);
	// 将其他点按照与第一个点的极角排序
	Vector3D temp = points[0];
	std::sort(points.begin() + 1, points.end(), [&temp](const Vector3D& a, const Vector3D& b) {

		double ret = det(temp, a, b);
		if (ret < 0) return false;
		else if (ret == 0)
		{
			return dic(temp, a) > dic(temp, b);
		}
		else {
			return true;
		}
		});

	std::vector<int> stack;
	stack.push_back(0);
	stack.push_back(1);
	for (int i = 2; i < points_size; i++)
	{
		while (stack.size() > 1 && det(points[stack[stack.size() - 2]], points[stack.back()], points[i]) < 0) {
			stack.pop_back();
		}
		stack.push_back(i);
	}
	stack.push_back(0);

	for (int i = 0; i < stack.size(); i++)
	{
		convexHull.push_back(points[stack[i]]);
	}
	return convexHull;
}

template<typename T>
std::vector<Vector3D> ConvexHull<T>::ConvexHull_Jearic(std::vector<Vector3D>& points)
{
	std::vector<Vector3D> convexHull;
	//按照x的大小排序
	std::sort(points.begin(), points.end(), [](const Vector3D& a, const Vector3D& b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
		});
	//找出最左下角的点
	convexHull.push_back(points[0]);
	int currentIndex = 0;
	int nextIndex = 0;
	int points_size = points.size();
	do
	{
		nextIndex = (currentIndex + 1) % points_size;
		for (int index = 0; index < points_size; index++)
		{
			if (index == currentIndex || index == nextIndex) continue;
			int ret = det(points[currentIndex], points[nextIndex], points[index]);
			if (ret < 0) {
				nextIndex = index;
			}
			else if (ret == 0) {
				if (dic(points[currentIndex], points[nextIndex]) < dic(points[currentIndex], points[index])) {
					nextIndex = index;
				}
			}
			
		} 
		currentIndex = nextIndex;
		convexHull.push_back(points[currentIndex]);
	} while (currentIndex != 0);
	return convexHull;
}

template<typename T>
std::vector<Vector3D> ConvexHull<T>::ConvexHull_Andrew(std::vector<Vector3D>& points)
{
	int points_size = points.size();
	std::vector<Vector3D> convexHull;
	//按照x的大小排序，相等的话按照y的大小排序
	std::sort(points.begin(), points.end(), [](const Vector3D& a, const Vector3D& b) {
		if (a.x == b.x) return a.y < b.y;
		return a.x < b.x;
		});
	std::vector<int> up; // 存储凸包的点集合
	up.push_back(0);
	for (int index = 1; index < points_size; index++)
	{
		while (up.size() > 1 && det(points[up.size() - 2], points[up.back()], points[index]) < 0)
		{
			up.pop_back();
		}
		up.push_back(index);
	}
	for (int i = 0; i < up.size(); i++)
	{
		convexHull.push_back(points[up[i]]);
	}
	up.clear();
	up.push_back(points_size - 1);
	for (int index = points_size - 2; index >= 0; index--)
	{
		while (up.size() > 1 && det(points[up[up.size() - 2]], points[up.back()], points[index]) < 0)
		{
			up.pop_back();
		}
		up.push_back(index);
	}
	for (int i = 1; i < up.size(); i++)
	{
		convexHull.push_back(points[up[i]]);
	}
	return convexHull;
}

template<typename T>
bool ConvexHull<T>::ConvexHullAlgorim(std::vector<Vector3D>& points, std::vector<Vector3D>& convexHull, CONVEXHULL_ALGORIM type) {
	if(points.size() < 3) return false; 
	std::vector<Vector3D> tempConvexHull;
	switch (type) {
	case CONVEXHULL_ALGORIM::JEARIC:
		tempConvexHull = ConvexHull_Jearic(points);
		break;
	case CONVEXHULL_ALGORIM::GRAHAM:
		tempConvexHull = ConvexHull_Graham(points);
		break;
	case CONVEXHULL_ALGORIM::ANDREW:
		tempConvexHull = ConvexHull_Andrew(points);
		break;

	default:
		break;
	}
	if(tempConvexHull.size() == 0)
		return false;
	//将tempConvexHull 中的值插入convexHull
	convexHull.insert(convexHull.end(), tempConvexHull.begin(), tempConvexHull.end());
	return true;
}

template<typename T>
double ConvexHull<T>::dic(const T& p1, const T& p2) {
	T temp = p1 - p2;
	return temp.GetLength();
}

template<typename T>
// 计算三维空间中各个向量的叉乘，找出它们的夹角关系，顺时针或者逆时针
double ConvexHull<T>::det(const T& p1, const T& p2, const T& p3)
{
	return p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p3.x * p2.y - p1.x * p3.y - p2.x * p1.y;
}
