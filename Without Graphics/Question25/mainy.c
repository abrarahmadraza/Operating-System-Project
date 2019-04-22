#include "stdio.h"
#include "string.h"
#include "process.h"
#include "stdlib.h"
#include "stddef.h"
#include <math.h>
#include <time.h>

#define cl system("cls")

struct process{
	int burst_time;
	int pid;
	int waiting_time;
	int turnaround_time;
	int remaining_time;
	int arrival_time;
	int priority;
	int completion_time;
}default_struct= {0,0,0,0,0,0,0,0};


int q1_n=0,q2_n=0,q3_n=0,n=0,i,j,k,complete=0;
int flag1=-1,flag2=-1,flag3=-1; 
int indexRR=-1,indexP=-1,indexF=-1;
struct process *q1,*q2,*q3;

	struct process *p=&default_struct;
	struct process *q=&default_struct;
	struct process *r=&default_struct;
	
void getinput(){
	printf("\n Total Number of Process:\t");
	scanf("%d",&n);
	//Allocatig Memory
	q1 = (struct process *)malloc(n*sizeof(struct process));
	q2 = (struct process *)malloc(n*sizeof(struct process));
	q3 = (struct process *)malloc(n*sizeof(struct process));
	int i,random=(rand())%(10000+1);
	for(i=0;i<n;i++){
		struct process p1;
		printf("\n\t\tProcess %d\n=============================================\n\n",i+1);
		p1.pid= random++;
		p1.arrival_time=0;
		printf("Priority (1-9):\t");
		scanf("%d",&p1.priority);
		printf("\nBurst Time:\t");
		scanf("%d",&p1.burst_time);
		p1.remaining_time = p1.burst_time;
		if(p1.priority>0 && p1.priority<=3){
			q1[q1_n++]  = p1;
		}else if(p1.priority>3 && p1.priority<=6){
			q2[q2_n++] = p1;
		}else{
			q3[q3_n++] = p1;
		}		
	}
}

int nextindexRR(int index,int tim)
{
	j=q1_n;
	k=index;
	for(i=k;i<j;i++)
	{
		if(q1[i].arrival_time<=tim&&q1[i].remaining_time!=0)
		{
			return i;
			break;
		}
		if(i==q1_n-1)
		{
			i=0;
			j=k;
		}
		
	}
	return -1;
						
}
int roundrobin(int tim)
{
	int quantum=0,time=tim,lasttime=tim;
	
	while(time<tim+10)
	{
		if(indexRR==-1)
		{
			indexRR=nextindexRR(indexRR,time);
			if(indexRR==-1)
			{
				time++;
				continue;
			}
			
		}
		
		p=&q1[indexRR];
		flag1=0;
		lasttime=time;

		p->remaining_time--;
		time++;
		
		if(p->remaining_time==0)
					{
						
						p->completion_time=time;
						complete++;
						quantum=0;
						
						
						//find next 
						indexRR=nextindexRR(indexRR,time);
						continue;
					}
					quantum++;
					
					if(quantum==4)//quantum=4
					{
						quantum=0;
						
						//find next 
						k=nextindexRR(indexRR,time);
						if(k!=-1)
						{
							indexRR=k;
						}
					}
	}
	return lasttime;
}
int nextindexP(int index,int tim)
{
	int highprio=INT_MAX;
	j=q2_n;
	k=index;
	for(i=k;i<j;i++)
						{
							if(q2[i].arrival_time<=tim&&q2[i].remaining_time!=0&&q2[i].priority<highprio)
							{
								index=i;
								highprio=q2[i].priority;
							}
							if(i==q2_n-1)
							{
								i=0;
								j=k;
							}
						}
						if(highprio!=INT_MAX)
						return index;
						
						return -1;
						
}
int priority(int tim)
{
	int time=tim,lasttime=tim;
	while(time<tim+10)
	{
		if(indexP==-1)
		{
			indexP=nextindexP(indexP,time);
			if(indexP==-1)
			{
				time++;
				continue;
			}
										

		}
		q=&q2[indexP];
		flag2=0;
		lasttime=time;
		q->remaining_time--;
		time++;
		if(q->remaining_time==0)
					{
						
						q->completion_time=time;
						complete++;
						
						
						//find next 
						indexP=nextindexP(indexP,time);
						continue;
					}
		
	}
	return --lasttime;
}

int nextindexF(int index,int tim)
{
	j=q3_n;
	k=index;
	for(i=k;i<j;i++)
	{
		if(q3[i].arrival_time<=tim&&q3[i].remaining_time!=0)
		{
			return i;
			break;
		}
		if(i==q3_n-1)
		{
			i=0;
			j=k;
		}
		
	}
	return -1;
						
}
int FCFS(int tim)
{
	int time=tim,lasttime=tim;
	while(time<tim+10)
	{
		if(indexF==-1)
		{
			indexF=nextindexF(indexF,time);
			if(indexP==-1)
			{
				time++;
				continue;
			}
		}
			r=&q3[indexF];
			flag3=0;
			lasttime=time;
			r->remaining_time--;
			
			time++;
		if(r->remaining_time==0)
					{
						
						r->completion_time=time;
						complete++;
						
						
						//find next 
						indexF=nextindexF(indexF,time);
						continue;
					}
				}
				return --lasttime;
}

void process()
{
	int time;
	for(time =0;complete!=q1_n+q2_n+q3_n;time++)
	{
		time=roundrobin(time);
		time=priority(time);
		time=FCFS(time);
	}
}

void calculate()
{
	int i;
	for(i=0;i<q1_n;i++)
	{
		q1[i].completion_time;
		q1[i].waiting_time=q1[i].completion_time-(q1[i].arrival_time+q1[i].burst_time);
		q1[i].turnaround_time=q1[i].waiting_time+q1[i].burst_time; 
	}
	for(i=0;i<q2_n;i++)
	{
		q2[i].completion_time;
		q2[i].waiting_time=q2[i].completion_time-(q2[i].arrival_time+q2[i].burst_time);
		q2[i].turnaround_time=q2[i].waiting_time+q2[i].burst_time; 
	}
	for(i=0;i<q3_n;i++)
	{
		q3[i].completion_time;
		q3[i].waiting_time=q3[i].completion_time-(q3[i].arrival_time+q3[i].burst_time);
		q3[i].turnaround_time=q3[i].waiting_time+q3[i].burst_time; 
	}
}

void display(struct process *t,int size){	
	printf("\nPId\t\tCompletion\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
	printf("\n=======================================================================================================================\n");
	int i;
	for(i=0;i<size;i++){
		printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",t[i].pid,t[i].completion_time,t[i].burst_time,t[i].waiting_time,t[i].turnaround_time,t[i].arrival_time);
	}
	printf("\n\n");
}

int main()
{
	getinput();
	process();
	calculate();
	cl;
if(flag1==0)
{	
	printf("\n\t\tRound Robin\n=============================================\n\n");
	display(q1,q1_n);
}
if(flag2==0)
{
	printf("\n\t\tPriority\n=============================================\n\n");
	display(q2,q2_n);
}
	
	if(flag3==0)
	{
	printf("\n\t\tFCFS\n=============================================\n\n");
	display(q3,q3_n);
	}
}
