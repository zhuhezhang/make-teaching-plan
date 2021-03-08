#include "teaching_plan_class.h"


//文件形式输入课程信息创建图
void  Graph::Creat_graph1(Graph* p)
{
	ifstream in("course_information.txt");
	in >> p->course_number;
	for (int i = 1;i <= p->course_number;i++)
	{
		in >> p->course[i].id >> p->course[i].name >> p->course[i].credit;
		p->course[i].course_exist = true;
	}
	int i, j;
	for (int k = 0;k < 19;k++)                    //依次输入19对关系（对应图的19条边）
	{
		in >> i >> j;
		p->adjmatrix[i][j] = 1;                   //表示课程ci是课程cj的先修课程
	}
	in.close();
	cout << "文件里面的课程信息已成功录入！" << endl;
}

//键盘形式输入课程信息创建图
void Graph::Creat_graph2(Graph* p)
{
	cout << "请输入课程总数" << endl;
	cin >> p->course_number;
	cout << "请依次输入课程编号、课程名称和学分" << endl;
	for (int i = 1;i <= p->course_number;i++)
	{
		cin >> p->course[i].id >> p->course[i].name >> p->course[i].credit;
		p->course[i].course_exist = true;
	}
	memset(p->adjmatrix, 0, sizeof(p->adjmatrix));//初始化adjmatrix全部元素为0 
	cout << "请输入课程之间的前后关系" << endl;
	int i, j, k;
	for (k = 1;k <= 19;k++)                       //依次输入19对关系（对应图的19条边） 
	{
		cin >> i >> j;
		p->adjmatrix[i][j] = 1;                   //表示课程ci是课程cj的先修课程
	}
	cout << "键盘输入的课程信息已成功录入！" << endl;
}

//输出课程信息 
void Graph::Display_information(Graph* p)
{
	cout<<"课程信息："<<endl;
	for (int i = 1;i <= p->course_number;i++)
	{
		cout << p->course[i].id << " ";
		cout << p->course[i].name << " ";
		cout << p->course[i].credit << " ";
		cout << endl;
	}
	cout<<endl<<"课程关系矩阵："<<endl;
	for (int i = 1;i <= p->course_number;i++)
	{
		for (int j = 1;j <= p->course_number;j++)
			cout << p->adjmatrix[i][j] << " ";
		cout << endl;
	}
}

//修改课程信息
void Graph::Modify_course(Graph* p)
{
	int number, choice;
	cout << "请输入您想修改的课程编号：" << endl;
	cin >> number;
	cout << "您想修改的信息为(1.课程名称 2.课程学分)：" << endl;
	cin >> choice;
	if (choice == 1)
	{
		cout << "请输入新的课程名称" << endl;
		cin >> p->course[number].name;
	}
	if (choice == 2)
	{
		cout << "请输入新的课程学分" << endl;
		cin >> p->course[number].credit;
	}
	cout << "修改成功" << endl;
}

//构造拓扑序列
void Graph::ToplogicalSort(Graph* p, int toplogicalSort_reslut[])
{
	int indegree[p->course_number + 1];           //存放各结点的入度（从indegree[1]开始存放）
	memset(indegree, 0, sizeof(indegree));
	for (int i = 1;i <= p->course_number;i++)     //统计各结点的入度
		for (int j = 1;j <= p->course_number;j++)
			if (p->adjmatrix[i][j]) indegree[j]++;

	stack <int> s;
	for (int i = 1;i <= p->course_number;i++)     //入度为0，则压入栈
		if (!indegree[i]) s.push(i);

	int num = 0;                                  //开始进行拓扑排序
	while (!s.empty())                            //栈非空
	{
		int top;
		top = s.top();                            //取栈顶元素
		s.pop();                                  //出栈
		toplogicalSort_reslut[num++] = top;       //保存栈顶元素
		for (int j = 1;j <= p->course_number;j++)
		{
			if (p->adjmatrix[top][j])
			{
				if (!--indegree[j]) s.push(j);    //每出一个元素，则它指向的结点入度减1 
			}                                     //并判断是否为0，若为零则入栈 
		}
	}
}
	
//按各学期中的学习负担尽量均匀地制定教学计划
void Graph::Output_teachingplan1(Graph* p, int toplogicalSort_reslut[])
{
	ofstream out("teaching_plan1.txt");
	int average_credit = 0;
	for (int i = 1;i <= p->course_number;i++)     //计算课程总学分
	{
		average_credit += p->course[i].credit;
	}

	int remaine_credit = average_credit;          //remaining_credit为剩余总学分 
	average_credit /= 8;                          //假设共8个学期
	out << "平均学分为:" << average_credit << endl << endl;
	int term_number = 1, j = 0;                   //学期编号、拓扑序列的下标

	while (remaine_credit > 0)                    //总学分还剩余
	{
		int term_credit = 0;
		int term_remaine_credit = average_credit; //当前学期还能修的学分
		out << "第" << term_number << "学期:" << endl;
		if (remaine_credit > term_remaine_credit) //剩余总学分多于当前学期还能修的学分
		{
			while (term_remaine_credit > 0)       //当前学期还能修的学分还剩余
			{
				out << p->course[toplogicalSort_reslut[j]].id << " ";
				out << p->course[toplogicalSort_reslut[j]].name << " ";
				out << p->course[toplogicalSort_reslut[j]].credit << " ";

				term_remaine_credit -= p->course[toplogicalSort_reslut[j]].credit;
				remaine_credit -= p->course[toplogicalSort_reslut[j]].credit;
				term_credit += p->course[toplogicalSort_reslut[j]].credit;
				j++;
				out << endl;
			}
			term_number++;                        //当前学期没有还能修的学分，换下学期
		}
		else                                      //剩余总学分少于或等于当前学期还能修的学分
		{
			out << p->course[toplogicalSort_reslut[j]].id << " ";
			out << p->course[toplogicalSort_reslut[j]].name << " ";
			out << p->course[toplogicalSort_reslut[j]].credit << " ";

			term_remaine_credit -= p->course[toplogicalSort_reslut[j]].credit;
			remaine_credit -= p->course[toplogicalSort_reslut[j]].credit;
			term_credit += p->course[toplogicalSort_reslut[j]].credit;
			j++;
			out << endl;
		}
		out << "本学期总学分为：" << term_credit << endl << endl;
	}
	out << "学期总数为:" << term_number << endl;
	out.close();
	cout << "教学计划已保存到文件teaching_plan1.txt中" << endl;
}

//按尽可能短的时间完成学习制定教学计划
void Graph::Output_teachingplan2(Graph* p, int toplogicalSort_reslut[])
{
	ofstream out("teaching_plan2.txt");
	int term_credit;                              //学期总学分
	int term_number = 1;                          //学期编号
	int number = 0;                               //拓扑排序结果下标
	int remain_credit = 0;                        //剩余总学分
	for (int i = 1;i <= p->course_number;i++)     //计算课程总学分
	{
		remain_credit += p->course[i].credit;
	}

	while (remain_credit > 15)                    //每学期学分上限为15 
	{
		term_credit = 0;
		out << "第" << term_number << "学期:" << endl;
		while (term_credit + p->course[toplogicalSort_reslut[number]].credit < 15)
		{                                         //当前本学期总学分+下一个要安排课程的学分<学分上限15
			out << p->course[toplogicalSort_reslut[number]].id << " ";
			out << p->course[toplogicalSort_reslut[number]].name << " ";
			out << p->course[toplogicalSort_reslut[number]].credit << " " << endl;
			term_credit += p->course[toplogicalSort_reslut[number]].credit;
			remain_credit -= p->course[toplogicalSort_reslut[number]].credit;
			number++;
		}
		term_number++;
		out << "本学期总学分为：" << term_credit << endl << endl;
    }

	term_credit = 0;
	out << "第" << term_number << "学期:" << endl;//总学分剩余小于15时 
	while (remain_credit > 0)
	{
		out << p->course[toplogicalSort_reslut[number]].id << " ";
		out << p->course[toplogicalSort_reslut[number]].name << " ";
		out << p->course[toplogicalSort_reslut[number]].credit << " " << endl;
		term_credit += p->course[toplogicalSort_reslut[number]].credit;
		remain_credit -= p->course[toplogicalSort_reslut[number]].credit;
		number++;
	}
	out << "本学期总学分为：" << term_credit << endl << endl;
	out << "学期总数为:" << term_number << endl;
	out.close();
	cout << "教学计划已保存到文件teaching_plan2.txt中" << endl;
}

//程序菜单
int Graph::Menu()
{
	int i;
	do {
		system("cls");
		cout << "***************教学计划编制系统****************" << endl << endl;
		cout << "           1.文件形式读入课程信息" << endl;
		cout << "           2.键盘形式读入课程信息" << endl;
		cout << "           3.课程信息修改" << endl;
		cout << "           4.课程信息输出" << endl;
		cout << "           5.按各学期中的学习负担尽量均匀地制定教学计划" << endl;
		cout << "           6.按尽可能短的时间完成学习制定教学计划" << endl;
		cout << "           7.退出程序" << endl << endl;
		cout << "请输入您的选择：";
		cin >> i;
	} while (i < 1 || i>7);
	return i;
}
