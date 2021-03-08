#ifndef TEACHING_PLAN_CLASS_H_
#define TEACHING_PLAN_CLASS_H_
#include <stack>
#include <cstring>
#include <fstream>
#include <iostream>
#define COURSE_MAX_NUMBER 20                                         //最大课程个数
using namespace std;

//课程结构体
struct Course
{
	char id[10];                                                     //课程编号
	char name[20];                                                   //课程名
	int credit;                                                      //课程学分
	bool course_exist;                                               //判断当前课程是否存在
};

//图类
class Graph
{
public:
	void Creat_graph1(Graph* p);                                     //文件形式输入课程信息创建图
	void Creat_graph2(Graph* p);                                     //键盘形式输入课程信息创建图
	void Modify_course(Graph* p);                                    //修改课程
	void ToplogicalSort(Graph* p, int toplogicalSort_reslut[]);      //拓扑排序
	void Output_teachingplan1(Graph* p, int toplogicalSort_reslut[]);//按各学期中的学习负担尽量均匀地制定教学计划
	void Output_teachingplan2(Graph* p, int toplogicalSort_reslut[]);//按尽可能短的时间完成学习制定教学计划
	void Display_information(Graph* p);                              //输出课程信息 
	int Menu();                                                      //程序菜单
private:
	Course course[COURSE_MAX_NUMBER];                                //课程信息 
	int course_number;                                               //课程数量
	int adjmatrix[COURSE_MAX_NUMBER][COURSE_MAX_NUMBER];             //邻接矩阵存放课程之间的关系
};

#endif
