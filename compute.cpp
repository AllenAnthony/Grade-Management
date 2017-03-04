#include "compute.h"
float u_compGPA(float * grade,float *credit,int Num) //计算本科生
{
    float GPA=0,temp,total_c=0;
    int i;
    for(i=0;i<Num;i++)
    {
        total_c+=credit[i];
        if(grade[i]>=95)
            temp=5;
        else if(grade[i]<60)
            temp=0;
        else temp=5-1.0*(95-grade[i])/10;
        GPA+=(temp*credit[i]);
    }
    if(total_c!=0)
       GPA/=total_c;
    return GPA;
}

float p_compGPA(float * grade,float *credit,int Num) //研究生
{
    float GPA=0,temp,total_c=0;
    int i;
    for(i=0;i<Num;i++)
    {
        total_c+=credit[i];
        if(grade[i]>=90)
            temp=4.0;
        else if(grade[i]>=85)
            temp=3.7;
        else if(grade[i]>=82)
            temp=3.3;
        else if(grade[i]>=78)
            temp=3.0;
        else if(grade[i]>=75)
            temp=2.7;
        else if(grade[i]>=71)
            temp=2.3;
        else if(grade[i]>=66)
            temp=2.0;
        else if(grade[i]>=62)
            temp=1.7;
        else if(grade[i]>=60)
            temp=1.3;
        else temp=0;
        GPA+=(temp*credit[i]);
    }
    if(total_c!=0)
       GPA/=total_c;
    return GPA;
}

float Phd_compGPA(float * grade,float *credit,int Num)   //博士生
{
    float GPA=0,temp,total_c=0;
    int i;
    for(i=0;i<Num;i++)
    {
        total_c+=credit[i];
        if(grade[i]<60)
            temp=0;
        else temp=4-3*(100-grade[i])*(100-grade[i])/2;
        GPA+=(temp*credit[i]);
    }
    if(total_c!=0)
       GPA/=total_c;
    return GPA;
}
