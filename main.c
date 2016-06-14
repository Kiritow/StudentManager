/** Rewritten by Kiritow.
*   on June 14th, 2016
*
*   All Rights Reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define NUMSTU 3      /*最大学生人数*/
#define NUMSCORE 4    /*成绩个数*/
#define NAMELEN 10    /*姓名的最大长度<10*/

const char SubjectName[NUMSCORE][NAMELEN]= {"数学","语文","英语","平均"};

typedef struct
{
    /*主要数据结构*/
    unsigned long no;	/*学号*/
    char name[NAMELEN];	/*姓名*/
    float score[NUMSCORE];	/*数学、语文、英语、平均成绩*/
    float average; /// Average Score.
}student;

void GUI_MenuShow()
{
    printf("|-------------------------------------------------------|\n");
    printf("|\t\t\t\t\t\t\t|\n");
    printf("|\t\t  请输入选项编号（0 ～～ 7）:  \t\t|\n");
    printf("|\t\t\t\t\t\t\t|\n");
    printf("|-------------------------------------------------------|\n");
    printf("|\t\t\t\t\t\t\t|\n");
    printf("|\t\t    1——创建成绩单          \t\t|\n");
    printf("|\t\t    2——添加学生          \t\t|\n");
    printf("|\t\t    3——编辑学生          \t\t|\n");
    printf("|\t\t    4——删除学生          \t\t|\n");
    printf("|\t\t    5——统计成绩          \t\t|\n");
    printf("|\t\t    6——排序成绩单        \t\t|\n");
    printf("|\t\t    7——显示成绩         \t\t|\n");
    printf("|\t\t    0——退出                 \t\t|\n");
    printf("|-------------------------------------------------------|\n");
    printf("请输入选项编号（0 ～ 7）: ");
}

void GUI_SortMenuShow()
{
    printf("|---------------------------------------|\n");
    printf("|                                       |\n");
    printf("|               排序菜单                |\n");
    printf("|                                       |\n");
    printf("|---------------------------------------|\n");
    printf("|                                       |\n");
    printf("|          1——按学号升序排列          |\n");
    printf("|          2——按学号降序排列          |\n");
    printf("|---------------------------------------|\n");

    printf("请输入选项编号（1 ～2）: ");
}

/// Get Input from KeyBoard.
char USR_GetInput()
{
    char c;
    scanf("%c%*c",&c);
    return c;
}

/// Array of student
student stu[NUMSTU];
int iCurrentStudentInList = 0;

int AddNewStudent()
{
    printf("请输入学号：");
    scanf("%lu%*c",&stu[iCurrentStudentInList].no);
    if(stu[iCurrentStudentInList].no==0)
    {
        return -1;
    }
    printf("请输入姓名：");
    gets(stu[iCurrentStudentInList].name);
    stu[iCurrentStudentInList].average=0;
    for(int i=0; i<NUMSCORE; i++)
    {
        printf("请输入%s成绩：",SubjectName[i]);
        scanf("%f",&stu[iCurrentStudentInList].score[i]);
        stu[iCurrentStudentInList].average+=stu[iCurrentStudentInList].score[i];
    }
    stu[iCurrentStudentInList].average/=NUMSCORE;
    printf("学生信息录入成功 ( %d of %d )\n",iCurrentStudentInList,NUMSTU);
    iCurrentStudentInList++;
    return 0;
}

void CreateNewStudentList()
{
    iCurrentStudentInList=0;
    printf("注意：输入的结束标志为学号为0!\n");
    while(iCurrentStudentInList<NUMSTU)
    {
        if(AddNewStudent()<0) break;
    }
    printf("创建完毕.\n");
}

void SearchStudentInList()
{
    printf("输入你所查找的学生学号:\n");
    unsigned long index;
    scanf("%lu%*c",&index);
    for(int i=0;i<iCurrentStudentInList;i++)
    {
        if(stu[i].no==index)
        {
            /// Found
            printf("开始编辑学号为%lu的学生\n",index);
            printf("请输入姓名：");
            gets(stu[i].name);
            stu[i].average=0;
            for(int j=0; j<NUMSCORE; j++)
            {
                printf("请输入%s成绩：",SubjectName[j]);
                scanf("%f",&stu[i].score[j]);
                stu[i].average+=stu[i].score[j];
            }
            stu[i].average/=NUMSCORE;
            printf("学生信息修改完毕.\n");
            return;
        }
    }
    printf("查无此人.\n");
}

void DeleteStudentInList()
{
    printf("输入你所要删除的学生学号：\n");
    unsigned long index;
    scanf("%lu%*c",&index);
    for(int i=0;i<iCurrentStudentInList;i++)
    {
        if(stu[i].no==index)
        {
            /// Found
            /// Now just move students.
            for(int j=i;j<iCurrentStudentInList-1;j++)
            {
                stu[j]=stu[j+1];
            }
            iCurrentStudentInList--;
            return;
        }
    }
    printf("此用户不存在。\n");
}

void AnalyzeStudentByScore()
{
    /*统计每科成绩>=90分以上的学生人数*/
    /// I just cannot understand the note above.
    if(iCurrentStudentInList<1)
    {
        printf("目前无记录，请添加成绩单信息！\n");
        return;
    }

    for(int i=0;i<NUMSCORE;i++)
    {
        int c=0;
        for(int j=0;j<iCurrentStudentInList;j++)
        {
            if(stu[j].score[i]>=90)
            {
                c++;
            }
        }
        printf("科目%s中大于90分的人数为:%d\n",SubjectName[i],c);
    }
}

int cmp_a(const void* a,const void* b)
{
    return ((student*)a)->no - ((student*)b)->no;
}

int cmp_b(const void* a,const void* b)
{
    return ((student*)b)->no - ((student*)a)->no;
}

void SortMenuProcessAction(char ActionID)
{
    if(iCurrentStudentInList<2)
    {
        printf("成绩表中少于2人则不做排序!\n");
        return;
    }
    switch(ActionID)
    {
    case '1':
        qsort(stu,iCurrentStudentInList,sizeof(student),cmp_a);
        break;
    case '2':
        qsort(stu,iCurrentStudentInList,sizeof(student),cmp_b);
        break;
    }
    printf("排序结束,请选择菜单项显示信息!\n");
}

void DisplayStudentList()
{
    if(iCurrentStudentInList<1)
    {
        printf("无学生记录，请创建成绩单！\n");
        return;
    }
    printf("学生信息如下：\n");
    printf("%15s%15s%10s%10s%10s%10s\n","学号","姓名","数学成绩","语文成绩","英语成绩","平均成绩");
    for(int i=0;i<iCurrentStudentInList;i++)
    {
        printf("%15lu%15s",stu[i].no,stu[i].name);
        for(int j=0;j<NUMSCORE;j++)
        {
            printf("%10.1f",stu[i].score);
        }
        printf("%10.1f\n",stu[i].average);
    }
}
void MenuProcessAction(char ActionID)
{
    switch(ActionID)
    {
        case '1':
            if(iCurrentStudentInList>0)
            {
                printf("\n不能重新创建学生成绩单\n");
            }
            else
            {
                CreateNewStudentList();
            }
            break;
        case '2':
            if(iCurrentStudentInList>=NUMSTU)
            {
                printf("成绩单已满！不可再加学生信息！！\n");
            }
            else
            {
                AddNewStudent();
            }
            break;
        case '3':
            SearchStudentInList();
            break;
        case '4':
            DeleteStudentInList();
            break;
        case '5':
            AnalyzeStudentByScore();
            break;
        case '6':
            GUI_SortMenuShow();
            char ret=USR_GetInput();
            SortMenuProcessAction(ret);
            break;
        case '7':
            DisplayStudentList();
            break;
        default:
            printf("非法输入\n");
            break;
    }
}



void init()
{
    iCurrentStudentInList=0;
}

int main()
{
    /// Initialization
    init();
    while(1)
    {
        GUI_MenuShow();
        char ret=USR_GetInput();
        if(ret=='0') break;
        MenuProcessAction(ret);
    }
    return printf("您选择了“0——退出”\n"),0;
}
