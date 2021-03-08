#include "teaching_plan_class.h"


//主函数
int main()
{
	int i;
	Graph graph, * p;
	p = (Graph*)malloc(sizeof(Graph));
	int toplogicalSort_reslut[20];
	memset(toplogicalSort_reslut, 0, sizeof(toplogicalSort_reslut));

    first:
	switch (graph.Menu())
	{
	    case 1:
	    {
		    system("cls");
		    graph.Creat_graph1(p);                               //文件形式输入课程信息创建图 
	    	system("pause");
	    	goto first;
	    }
	    case 2:
	    {
	    	system("cls");
	     	graph.Creat_graph2(p);                               //键盘形式输入课程信息创建图
	    	system("pause");
	    	goto first;
    	}
        case 3:
	    {
		    system("cls");
		    graph.Modify_course(p);                              //修改课程信息 
		    system("pause");
		    goto first;
	    }
	    case 4:
    	{
		    system("cls");
		    graph.Display_information(p);                        //输出课程信息 
		    system("pause");
	    	goto first;
	    }
    	case 5:
    	{
		    system("cls");
		    graph.ToplogicalSort(p, toplogicalSort_reslut);      //拓扑排序 
	    	graph.Output_teachingplan1(p, toplogicalSort_reslut);//按各学期中的学习负担尽量均匀地制定教学计划
		    system("pause");
	    	goto first;
	    }
    	case 6:
    	{
		    system("cls");
	    	graph.ToplogicalSort(p, toplogicalSort_reslut);       //拓扑排序 
	    	graph.Output_teachingplan2(p, toplogicalSort_reslut); //按尽可能短的时间完成学习制定教学计划
	    	system("pause");
	    	goto first;
	    }
	}
	cout << "感谢使用！"; 
	return 0;
}
