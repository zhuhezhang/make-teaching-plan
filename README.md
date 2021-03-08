@[TOC](目录)
# 1.问题描述与要求
大学的每个专业都要制定教学计划。假设任何专业都有固定的学习年限，每学年含两学期，每学期的时间长度和学分上限值均相等。每个专业开设的课程都是确定的，而且课程在开设时间的安排必须满足先修关系。每门课程有哪些先修课程是确定的，可以有任意多门，也可以没有。每门课恰好占一个学期。试在这样的前提下设计一个教学计划编制程序。
要求：
（1）对某专业的各门课程信息以及直接先修课信息的编辑，应该提供文件形式输入和键盘输入两种方式。输入信息应包括：每门课的课程号（固定占3位的字母数字串）、课程名、学分和直接先修课的课程号。
（2）编制教学计划时应输入的参数包括：学期总数，一学期的学分上限。
（3）允许用户指定下列两种编排策略之一：一是使学生在各学期中的学习负担尽量均匀；二是使课程尽可能地集中在前几个学期中。
（4）若根据给定的条件问题无解，则报告适当的信息；否则将教学计划输出到用户指定的文件中。文件中教学计划的表格格式自行设计。
（5）如果输入的先修课程号不在该专业开设的课程序列中，则作为错误处理；应建立内部课程序号与课程号之间的对应关系。
（6）产生多种（例如5种）不同的方案，并使方案之间的差异尽可能地大。
# 2.需求分析
题目主要要求用户可以以文件形式或者键盘形式输入课程信息，包括课程号、课程名、学分以及直接先修课程，并允许用户指定两种编排策略之一（一是使学生在各学期中的学习负担尽量均匀；二是使课程尽可能地集中在前几个学期中）输出课程表至指定文件中。
# 3.设计
## 3.1设计思想
从主菜单出发：菜单包括七个指令，分别是文件形式读入课程信息、键盘形式读入课程信息、课程信息修改、课程信息输出、按各学期中的学期负担均匀地制定教学计划、按尽可能短的时间完成制定教学计划以及退出程序，而类里面的函数声明基本上就这几个。为了储存课程信息定义一个结构体，而在类里面除了定义课程结构体数组存放课程信息外，还有课程个数变量以及表示课程先修关系的邻接矩阵。程序围绕主菜单进行，执行完一个函数之后利用goto语句可以返回主菜单继续执行其他功能。当然，在执行之前，应当选择所提供的任意一种读入课程信息方式读入课程信息才可以执行其他功能。
## 3.2设计表示
![在这里插入图片描述](https://img-blog.csdnimg.cn/202103082342547.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)

## 3.3详细设计
主函数以及头文件部分在前面的设计思想基本上已经说过，所以这里就不再说明，直接说类里面函数定义。这里从函数调用顺序出发，方便理解一些：运行程序会先调用程序菜单，主要就是打印出函数名，返回对应函数数字指令。首先必须要读入课程数据，有文件方式读入以及键盘方式读入两种方式：对于文件读入，首先创建文件输入流in，并从用in文本文件course_information.txt（由本人直接新建该文件并输入所有课程信息）依次读入所有课程信息，最后再in.close()关闭文件即可，键盘读入部分思想和文件差不多，就不再说明了。接下来是一个很简单的课程信息修改函数，提供修改相应课程的名称以及课程学分，还有一个为了方便查看课程信息而写的输出显示信息在屏幕上的函数，包括课程信息以及表示课程间的先修关系邻接矩阵。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234305183.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)

然后是一个在输出教学计划之前必须要调用的根据课程先修关系构造拓扑序列函数：定义一个数组存放各结点的入度（从indegree[1]开始存放），利用memset初始化该数组所有元素为0，然后利用循环从邻接矩阵中统计所有课程入度（先修课程）。如果入度为0，则进栈，然后从栈顶元素出发依次出栈，并且每一个元素出栈时其对应的后继课程的入度会减1，若减1之后其入度为0，则将其压入栈，如此循环直到栈空。当然，每一次出栈的结点也应该用一个数组将其保存下来，用于后面的教学计划输出，其伪代码如上图所示。
对于按各学期中的学习负担尽量均匀地制定教学计划：其基本思想是先计算平均学分并赋值给average_credit，假设学期数为8，之后根据拓补序列累加，每次累加到大于average_credit就换下一个学期，这样分配就能达到学习负担均匀的目的。根据这个思想，首先创建文件输入流out并打开文件teaching_plan1.txt（若没有则自动创建该文件），计算平均学分，一个学期计划输出放在一个大循环while里面，首先判断若总学分还有剩余。当剩余总学分多于当前学期还能修的学分，并且前学期还能修的学分还剩余则依次利用文件输出流out输出本学期要修的课程至文件teaching_plan1.txt中，每次还要更新本学期还能修的学分等信息。若是剩余总学分少于或等于当前学期还能修的学分，则直接输出剩下的课程即可。最后再利用out.close()关闭文件即可。
同样地对于按尽可能短的时间完成学习制定教学计划：其基本思想是根据拓扑序列以及每学期学分上限（这里假定为15），只要一个学期的学分上限未超过15则继续安排课程在本学期，否则换下一学期直至输出完拓扑序列中的所有课程。根据这个思想首先同样地创建文件输入流out并打开文件teaching_plan2.txt（若没有则自动创建该文件），然后计算课程总学分，若课程总剩余学分还大于15（每学期学分上限），则依次输出各个学期的课程信息至文件teaching_plan2.txt中，输出到最后若课程总学分小与15，则直接安排剩下的课程到下学期即可，最后同样的也是要利用out.close()关闭文件teaching_plan2.txt。
# 4.用户手册
 程序打开运行就是菜单，在执行其他操作之前一定要利用文件方式读入或者是键盘方式读入课程信息，当然存储课程信息的文件course_information.txt也一定要包含在程序所在的那个文件才行。读入课程信息之后可以根据菜单输入相应指令执行相应操作，例如输出显示课程信息、输出教学计划至指定文件中teaching_plan1.txt/teaching_plan2.txt（文件在源程序所在的文件夹）等，每执行一个功能后会返回菜单执行其他功能或者选择退出程序。
# 5.测试数据及测试结果
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234315419.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234323114.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234330763.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234337426.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021030823434413.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210308234351198.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQzNzk0NjMz,size_16,color_FFFFFF,t_70#pic_center)

# 6.源程序清单
teaching_plan_class.h     //存放课程信息结构体以及封装各个函数的类
teaching_plan_fun.cpp    //类里面各个函数的定义
teaching_plan_main.cpp   //对各函数调用的主函数
course_information.txt    //文件形式输入课程信息调用的文件
teaching_plan1.txt       //存放按各学期中的学习负担尽量均匀地制定的教学计划
teaching_plan2.txt       //存放按尽可能短的时间完成学习制定的教学计划
