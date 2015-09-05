#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <fstream>

#define NUM  51   //城市个数
#define N      150  //群体规模为150
#define pc     0.7  //交叉概率为0.7
#define pm     0.07  //变异概率为0.07
#define ps     0.7239  //进行选择时保留的比例
#define genmax 50000  //最大代数5000

void initialize(struct genotype group[N]);
double randval(int low,int high);
void evaluate(struct genotype group[N]);
int select(int *son,int k);
void crossover(struct genotype *p1,struct genotype *p2);
void copy(struct genotype *p1,struct genotype *p2);
void mutate(struct genotype group[N],int i);
void length(struct genotype *p);
void sort(struct genotype group[N]);
void optimum(struct genotype group[N],int k);
void print_optimum(struct genotype group[N],int k);

/* 定义个体信息 */
struct genotype
{
  int path[NUM]; //个体的路径信息
  int length;        //路径长度
};
struct genotype group[N]; //种群变量group
int table[51][51]={0,12,19,31,22,16,22,11,24,34,12,20,41,26,36,18,30,27,45,20,26,7,21,29,33,18,8,16,21,32,17,6,42,30,27,31,30,18,43,56,44,44,34,37,42,13,23,12,26,24,
						13,12,0,15,37,21,28,34,22,16,28,10,24,50,37,35,8,34,35,50,12,14,10,33,41,43,29,19,18,9,23,23,11,39,20,19,24,31,14,35,61,50,48,46,38,40,19,29,24,21,13,21,
						19,15,0,49,36,35,35,21,31,43,25,38,61,45,50,23,48,46,64,7,24,12,36,45,51,25,27,9,17,37,15,22,54,32,10,12,46,29,49,74,63,62,47,53,55,32,41,28,36,27,32,
						31,37,49,0,20,21,37,37,32,31,26,12,15,17,18,35,7,7,14,48,44,38,31,28,17,42,24,47,43,38,46,26,30,41,55,60,12,26,40,25,13,16,40,14,24,17,7,29,28,37,17,
						22,21,36,20,0,25,40,33,12,14,11,9,35,30,14,16,14,23,31,32,25,27,36,38,33,40,20,37,25,18,39,16,20,21,39,45,11,7,24,42,32,27,48,18,20,12,15,29,8,17,14,
						16,28,35,21,25,0,16,18,34,39,21,18,27,10,34,31,24,14,34,37,41,23,11,13,16,21,9,29,37,42,27,17,44,42,44,47,27,26,49,44,31,37,23,33,41,13,15,8,33,36,11,
						22,34,35,37,40,16,0,14,46,54,33,34,39,21,50,41,41,30,50,40,49,25,6,14,26,11,19,26,43,54,20,27,60,53,45,46,43,39,63,58,46,53,12,49,57,28,32,11,46,46,26,
						11,22,21,37,33,18,14,0,35,45,23,30,45,27,46,29,39,32,52,26,36,12,15,25,33,7,14,13,30,44,9,17,54,41,31,32,40,30,54,61,49,52,26,47,52,23,30,9,38,35,22,
						24,16,31,32,12,34,46,35,0,12,12,21,47,41,23,8,26,35,43,25,13,26,43,47,45,43,26,35,16,8,39,19,23,9,31,37,22,7,19,54,44,38,56,28,26,20,27,34,6,5,23,
						34,28,43,31,14,39,54,45,12,0,21,22,46,44,15,20,24,36,38,37,23,37,50,53,47,52,34,46,27,9,50,28,12,15,43,49,19,15,10,48,41,31,62,21,16,26,28,42,7,16,28,
						12,10,25,26,11,21,33,23,12,21,0,14,40,30,25,10,23,26,40,22,20,16,30,35,35,30,13,26,17,21,28,6,31,20,29,35,21,6,31,50,40,37,43,28,31,10,19,22,14,14,12,
						20,24,38,12,9,18,34,30,21,22,14,0,26,21,16,22,9,14,26,36,32,27,29,30,24,36,16,37,31,27,37,15,26,30,43,48,10,14,32,36,25,24,41,17,23,7,6,23,17,25,8,
						41,50,61,15,35,27,39,45,47,46,40,26,0,18,32,49,22,14,14,61,59,48,33,27,13,48,33,56,57,53,54,39,43,56,68,72,27,41,54,19,9,21,39,26,37,30,21,36,43,52,29,
						26,37,45,17,30,10,21,27,41,44,30,21,18,0,35,40,24,10,29,47,50,33,15,10,6,30,18,39,46,48,36,26,46,49,54,57,28,33,54,36,25,33,23,32,41,20,16,18,38,44,18,
						36,35,50,18,14,34,50,46,23,15,25,16,32,35,0,29,11,25,23,46,36,41,45,45,36,52,32,51,38,24,53,30,11,30,53,59,7,21,23,32,26,16,57,6,6,23,19,40,16,29,24,
						18,8,23,35,16,31,41,29,8,20,10,22,49,40,29,0,30,35,48,17,10,18,39,45,45,36,23,27,9,15,31,14,31,12,24,30,27,9,26,58,48,43,52,34,33,20,28,30,13,5,22,
						30,34,48,7,14,24,41,39,26,24,23,9,22,24,11,30,0,14,17,46,39,37,35,34,25,45,25,46,39,31,47,25,23,35,53,58,5,21,32,27,18,14,46,8,17,16,9,32,21,32,17,
						27,35,46,7,23,14,30,32,35,36,26,14,14,10,25,35,14,0,20,47,45,34,24,21,11,36,19,42,43,41,41,24,37,44,54,58,18,28,45,29,17,23,33,22,31,16,8,23,31,39,14,
						45,50,64,14,31,34,50,52,43,38,40,26,14,29,23,48,17,20,0,62,56,52,44,39,25,56,38,61,57,47,60,41,33,52,70,75,21,38,46,10,5,8,51,17,26,32,22,43,38,49,31,
						20,12,7,48,32,37,40,26,25,37,22,36,61,47,46,17,46,47,62,0,16,15,41,49,53,31,28,16,10,31,22,22,49,25,7,12,43,25,43,73,62,60,52,50,51,31,41,32,31,21,32,
						26,14,24,44,25,41,49,36,13,23,20,32,59,50,36,10,39,45,56,16,0,25,48,54,55,43,32,31,7,15,36,24,35,9,21,27,36,18,27,67,57,52,61,41,39,30,38,39,19,7,32,
						7,10,12,38,27,23,25,12,26,37,16,27,48,33,41,18,37,34,52,15,25,0,26,34,39,18,15,10,18,34,13,11,47,30,20,24,36,22,45,63,51,51,37,43,47,20,30,17,29,24,20,
						21,33,36,31,36,11,6,15,43,50,30,29,33,15,45,39,35,24,44,41,48,26,0,9,21,15,16,28,42,51,24,24,55,51,46,48,38,36,60,52,40,47,13,44,52,24,26,9,43,44,22,
						29,41,45,28,38,13,14,25,47,53,35,30,27,10,45,45,34,21,39,49,54,34,9,0,14,24,22,38,50,55,33,30,56,56,55,57,38,40,63,46,35,43,12,43,52,27,26,17,46,50,25,
						33,43,51,17,33,16,26,33,45,47,35,24,13,6,36,45,25,11,25,53,55,39,21,14,0,36,25,46,51,52,43,32,48,54,60,64,29,38,56,32,21,31,26,32,42,25,18,24,42,49,23,
						18,29,25,42,40,21,11,7,43,52,30,36,48,30,52,36,45,36,56,31,43,18,15,24,36,0,20,16,36,51,10,24,61,48,35,36,46,37,61,65,53,58,22,53,59,29,36,13,45,42,28,
						8,19,27,24,20,9,19,14,26,34,13,16,33,18,32,23,25,19,38,28,32,15,16,22,25,20,0,23,28,35,22,8,41,34,35,39,26,19,43,48,36,39,29,33,39,9,16,8,26,28,8,
						16,18,9,47,37,29,26,13,35,46,26,37,56,39,51,27,46,42,61,16,31,10,28,38,46,16,23,0,24,42,6,21,57,38,19,20,46,32,54,71,59,61,38,53,57,30,39,21,39,32,29,
						21,9,17,43,25,37,43,30,16,27,17,31,57,46,38,9,39,43,57,10,7,18,42,50,51,36,28,24,0,21,29,20,39,15,15,21,36,18,33,67,57,53,55,43,42,27,36,33,22,11,29,
						32,23,37,38,18,42,54,44,8,9,21,27,53,48,24,15,31,41,47,31,15,34,51,55,52,51,35,42,21,0,46,27,20,6,36,42,26,15,12,57,49,40,64,30,25,28,33,43,10,10,30,
						17,23,15,46,39,27,20,9,39,50,28,37,54,36,53,31,47,41,60,22,36,13,24,33,43,10,22,6,29,46,0,23,59,43,25,26,47,34,58,70,58,61,32,54,59,30,38,18,42,37,29,
						6,11,22,26,16,17,27,17,19,28,6,15,39,26,30,14,25,24,41,22,24,11,24,30,32,24,8,21,20,27,23,0,36,26,29,33,24,13,37,51,40,39,37,32,36,9,19,15,20,20,10,
						42,39,54,30,20,44,60,54,23,12,31,26,43,46,11,31,23,37,33,49,35,47,55,56,48,61,41,57,39,20,59,36,0,27,55,61,18,25,13,41,36,25,67,16,7,32,30,49,18,28,34,
						30,20,32,41,21,42,53,41,9,15,20,30,56,49,30,12,35,44,52,25,9,30,51,56,54,48,34,38,15,6,43,26,27,0,30,36,31,16,18,62,53,46,64,35,31,29,36,42,13,6,31,
						27,19,10,55,39,44,45,31,31,43,29,43,68,54,53,24,53,54,70,7,21,20,46,55,60,35,35,19,15,36,25,29,55,30,0,6,50,32,48,80,69,67,57,57,57,38,48,37,37,26,39,
						31,24,12,60,45,47,46,32,37,49,35,48,72,57,59,30,58,58,75,12,27,24,48,57,64,36,39,20,21,42,26,33,61,36,6,0,56,38,54,85,74,72,58,63,63,43,53,40,43,32,43,
						30,31,46,12,11,27,43,40,22,19,21,10,27,28,7,27,5,18,21,43,36,36,38,38,29,46,26,46,36,26,47,24,18,31,50,56,0,18,27,31,22,16,49,7,13,17,12,33,17,28,18,
						18,14,29,26,7,26,39,30,7,15,6,14,41,33,21,9,21,28,38,25,18,22,36,40,38,37,19,32,18,15,34,13,25,16,32,38,18,0,24,49,39,34,49,25,25,13,20,28,7,11,15,
						43,35,49,40,24,49,63,54,19,10,31,32,54,54,23,26,32,45,46,43,27,45,60,63,56,61,43,54,33,12,58,37,13,18,48,54,27,24,0,54,49,38,72,29,20,36,38,52,17,22,38,
						56,61,74,25,42,44,58,61,54,48,50,36,19,36,32,58,27,29,10,73,67,63,52,46,32,65,48,71,67,57,70,51,41,62,80,85,31,49,54,0,12,16,58,26,34,42,32,52,48,59,42,
						44,50,63,13,32,31,46,49,44,41,40,25,9,25,26,48,18,17,5,62,57,51,40,35,21,53,36,59,57,49,58,40,36,53,69,74,22,39,49,12,0,13,47,20,29,31,21,40,39,50,30,
						44,48,62,16,27,37,53,52,38,31,37,24,21,33,16,43,14,23,8,60,52,51,47,43,31,58,39,61,53,40,61,39,25,46,67,72,16,34,38,16,13,0,56,10,18,31,22,45,32,44,31,
						34,46,47,40,48,23,12,26,56,62,43,41,39,23,57,52,46,33,51,52,61,37,13,12,26,22,29,38,55,64,32,37,67,64,57,58,49,49,72,58,47,56,0,55,63,36,37,21,56,57,34,
						37,38,53,14,18,33,49,47,28,21,28,17,26,32,6,34,8,22,17,50,41,43,44,43,32,53,33,53,43,30,54,32,16,35,57,63,7,25,29,26,20,10,55,0,10,24,17,40,22,34,25,
						42,40,55,24,20,41,57,52,26,16,31,23,37,41,6,33,17,31,26,51,39,47,52,52,42,59,39,57,42,25,59,36,7,31,57,63,13,25,20,34,29,18,63,10,0,29,26,47,20,31,31,
						13,19,32,17,12,13,28,23,20,26,10,7,30,20,23,20,16,16,32,31,30,20,24,27,25,29,9,30,27,28,30,9,32,29,38,43,17,13,36,42,31,31,36,24,29,0,9,17,19,24,2,
						23,29,41,7,15,15,32,30,27,28,19,6,21,16,19,28,9,8,22,41,38,30,26,26,18,36,16,39,36,33,38,19,30,36,48,53,12,20,38,32,21,22,37,17,26,9,0,23,23,31,9,
						12,24,28,29,29,8,11,9,34,42,22,23,36,18,40,30,32,23,43,32,39,17,9,17,24,13,8,21,33,43,18,15,49,42,37,40,33,28,52,52,40,45,21,40,47,17,23,0,35,35,15,
						26,21,36,28,8,33,46,38,6,7,14,17,43,38,16,13,21,31,38,31,19,29,43,46,42,45,26,39,22,10,42,20,18,13,37,43,17,7,17,48,39,32,56,22,20,19,23,35,0,12,21,
						24,13,27,37,17,36,46,35,5,16,14,25,52,44,29,5,32,39,49,21,7,24,44,50,49,42,28,32,11,10,37,20,28,6,26,32,28,11,22,59,50,44,57,34,31,24,31,35,12,0,26,
						13,21,32,17,14,11,26,22,23,28,12,8,29,18,24,22,17,14,31,32,32,20,22,25,23,28,8,29,29,30,29,10,34,31,39,43,18,15,38,42,30,31,34,25,31,2,9,15,21,26,0};
int main()
{
  srand((int)time(NULL)); //初始化随机数发生器
  initialize(group);  //初始化种群
  evaluate(group);       //进化：选择、交叉、变异
  return 0;
}

/* 初始化种群 */
void initialize(struct genotype group[N])
{
  int i,j,k;
  struct genotype *p;
  for(i=0;i<=N-1;i++) //初始化种群里的100个个体
	{
	  p=&group[i]; //p指向种群的第i个个体
	  for(j=0;j<=NUM-1;j++) //生成10个城市间的一个随机路径
		{
		  k=0;
		  if(j==0)  
		  	p->path[j]=randval(0,NUM-1);
		  else
			{
			  p->path[j]=randval(0,NUM-1);
			  while(k<j)
				{
				  //与之前城市重复，重新生成一个城市
				  if(p->path[j]==p->path[k]){p->path[j]=randval(0,NUM-1); k=0; }
				  else k++;
				}//end while
			}
		}//end 生成路径
	  length(p); //计算该路径的代价值
	}//end 初始化种群
}

/* 生成一个介于两整型数之间的随机整数 */
double randval(int low,int high)
{
  double val=rand();
  double d;
  d=(double)val/((double)(RAND_MAX));
  val=(double)(d*(high-low+1))+low;
  return val;
}

/* 种群进化，进化代数由genmax决定 */
void evaluate(struct genotype group[N])
{
  int i,j;
  int probability1,probability2,probability3,probability4,probability5;
  probability1=N*pc/2;
  probability2=N*(1-pc);
  probability3=N*(1-pc/2);
  probability4=N*(1-ps);
  probability5=N*ps;
  for(i=1;i<=genmax;i++)
	{
	  //选择
      sort(group);
      optimum(group,i-1);
      for(j=0;j<=probability4-1;j++)
			copy(&group[j],&group[j+probability5]); 
	  //交叉
	  for(j=0;j<=probability1-1;)
		{
		  crossover(&group[probability2+j],&group[probability3+j]);
		  j+=2;
		}
	  //变异
	  mutate(group,i);
	}
  sort(group);
  print_optimum(group,i-1); //输出当代(第i-1代)种群
}

/* 检查k是否在son[NUM]中已出现过 */
int select(int* son,int k)
{
  int i;
  for(i=0;i<=NUM-1;i++)
	  if(son[i]==k) 
	  	return -1;
  return 1;
}

/* 交叉 */
void crossover(struct genotype *p1,struct genotype *p2)
{
  int i,j,crossover_point;
  int *son1,*son2;
  for(i=0;i<=NUM-1;i++) //初始化son1、son2
	{
	  son1[i]=-1;
	  son2[i]=-1;
	}
  crossover_point=randval(1,NUM-1); //交叉位随机生成
  //交叉，生成子代
  //子代1
  //子代1前半部分直接从父代复制
  for(i=0;i<=crossover_point-1;i++)  
  	son1[i]=p1->path[i];
  for(i=crossover_point;i<=NUM-1;i++)
	{
	  for(j=0;j<=NUM-1;j++) //补全p1
		{
		  if(select(son1,p2->path[j])==1)
			{ 
				son1[i]=p2->path[j]; 
				break; 
			}
		}
	}//end 子代1
  //子代2
  //子代1后半部分直接从父代复制
  for(i=crossover_point;i<=NUM-1;i++)  son2[i]=p2->path[i];
  for(i=0;i<=crossover_point-1;i++)
	{
	  for(j=0;j<=NUM-1;j++) //补全p2
		{
		  if(select(son2,p1->path[j])==1)
			{ 
				son2[i]=p1->path[j]; 
				break; 
			}
		  else ;
		}
	}//end 子代2
  //end 交叉
  for(i=0;i<=NUM-1;i++)
	{
	  p1->path[i]=son1[i];
	  p2->path[i]=son2[i];
	}
  length(p1); //计算子代p1的代价
  length(p2); //计算子代p2的代价
}

/* 复制种群中的p1到p2中 */
void copy(struct genotype *p1,struct genotype *p2)
{
  int i;
  for(i=0;i<=NUM-1;i++)  
  	p2->path[i]=p1->path[i];
  p2->length=p1->length;
}

/* 变异 */
void mutate(struct genotype group[N],int flag)
{
  int standard,i,j,k,temp;
  struct genotype *p;
  standard=randval(1,100);
  //在进化后期，增大变异概率
  if(standard<=(flag>100)?(pm*500):(pm*100))
	{
	  i=randval(0,N-1);      //确定发生变异的个体
	  j=randval(0,NUM-1);  //确定发生变异的位
	  k=randval(0,NUM-1);
	  p=&group[i];                 //变异
	  temp=p->path[j];
	  p->path[j]=p->path[k];
	  p->path[k]=temp;
	  length(p);           //重新计算变异后路径的代价
	}
}

/* 计算某个路径的代价值 */
void length(struct genotype *p)
{
  int j;
  p->length=0;
  for(j=1;j<=NUM-1;j++)
	 p->length+=table[p->path[j-1]][p->path[j]];
  p->length+=table[p->path[NUM-1]][p->path[0]];
}

/* 将种群中个体按代价从小到大排序 */
void sort(struct genotype group[N])
{
  int i,j;
  struct genotype temp,*p1,*p2;
  for(j=1;j<=N-1;j++) //排序总共需进行N-1轮
	{
	  for(i=1;i<=N-1;i++)
		{
		  p1=&group[i-1];
		  p2=&group[i];
	 	  if(p1->length>p2->length) //代价值大的往后排
			{
			  copy(p1,&temp);
			  copy(p2,p1);
			  copy(&temp,p2);
			}//end if
		}//end 一轮排序
	}//end 排序  
}

void optimum(struct genotype group[N],int k)
{
  int i,j;
  struct genotype *p;
  for(i=0;i<=N-1;i++)
	  p=&group[i];
}

/* 输出当代种群中的每个个体 */
void print_optimum(struct genotype group[N],int k)
{
  int i,j;
  struct genotype *p;
  for(i=0;i<=N-1;i++)
	  p=&group[i];
  p = &group[0];
  printf("%d \n",p->length);
}

