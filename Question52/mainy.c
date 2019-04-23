#include "stdio.h"

#include "string.h"

#include "process.h"

#include "stdlib.h"

#include "stddef.h"

#include <math.h>

#include<windows.h>

#include "graphity.h"

#include <time.h>

#define cl system("cls")

typedef char string[20];

struct process {
  int burst_time;
  int process_id;
  int waiting_time;
  int turnaround_time;
  int remaining_time;
  int arrival_time;
  int completion_time;
}
default_struct = {
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

int number_of_process_in_queue1, number_of_process_in_queue2, index_queue1 , index_queue2 , i, j, quantum , indexi , k , complete , flag_queue1, flag_queue2;
COORD xy;
HANDLE h;
struct process * queue1, * queue2;

void getinput() {
	index_queue1=0;index_queue2=0;quantum=0;indexi=-1;k=0;complete=0;flag_queue1=-1;flag_queue2=-1;
	red();
	cl;
	gotoxy(20,5);
	font(65,60);
	printf("Welcome");
	sleep(1);
	cl;
	cls();
	loading(1);
	font(20,30);
	cls();
	centre();
  printf("Total Number of Process in queue 1:\t");
  	centre();
  	h=GetStdHandle(STD_OUTPUT_HANDLE);
  	xy=cursorpos(h);
    gotoxy(xy.X,xy.Y+1);
  printf("\n\nTotal Number of Process in queue 2:\t");
    green();
    centre();
  	h=GetStdHandle(STD_OUTPUT_HANDLE);
  	xy=cursorpos(h);
    gotoxy(xy.X+42,xy.Y);
  scanf("%d", & number_of_process_in_queue1);
  
  centre();
  	h=GetStdHandle(STD_OUTPUT_HANDLE);
  	xy=cursorpos(h);
    gotoxy(xy.X+42,xy.Y+1);
  scanf("%d", & number_of_process_in_queue2);
  
  cl;
  cls();
  loading(1);
  font(20,30);
  //Allocatig Memory1
  
  queue1 = (struct process * ) malloc(number_of_process_in_queue1 * sizeof(struct process));
  queue2 = (struct process * ) malloc(number_of_process_in_queue2 * sizeof(struct process));
  
  int i, random = (rand()) % (10000 + 1);  
  struct process p; //mediator variable
  
  
  printf("\n\t\t\t\t  Queue 1\n");
  
  //Take Input
	yellow();
	printf("\n\t\tProcess");
	printf("\t\tArrival Time");
	printf("\t\tBurst Time");
	green();
	cls();
  gotoxy(0,0);
  gotoxy(40,3);
   for (i = 0; i < number_of_process_in_queue1; i++) 
   {
   	printf("\n\t\tProcess %d", i + 1);
    p.process_id = random++;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    xy=cursorpos(h);
    gotoxy(40,xy.Y);
    scanf("%d", & p.arrival_time);
    gotoxy(60,xy.Y);
    scanf("%d", & p.burst_time);
    p.remaining_time = p.burst_time;
    queue1[index_queue1++] = p;
    }
    
  //Queue 2 input
  red();
  printf("\n\n\t\t\t\t  Queue 2\n");
  yellow();
	printf("\n\t\tProcess");
	printf("\t\tArrival Time");
	printf("\t\tBurst Time");
	green();
	cls();
  for (i = 0; i < number_of_process_in_queue2; i++) {
   	printf("\n\t\tProcess %d", i + 1);
    p.process_id = random++;
    h=GetStdHandle(STD_OUTPUT_HANDLE);
    xy=cursorpos(h);
    gotoxy(40,xy.Y);
    scanf("%d", & p.arrival_time);
    gotoxy(60,xy.Y);
    scanf("%d", & p.burst_time);
    p.remaining_time = p.burst_time;
    queue2[index_queue2++] = p;

  }

}

int nextindex(int ka, int tim) {
  j = number_of_process_in_queue2;
  k = ka;
  if (k == number_of_process_in_queue2 - 1) {
    k = 0;
  }
  for (i = k; i < j; i++) {
    if (queue2[i].arrival_time <= tim && queue2[i].remaining_time != 0) {
      return i;
      break;
    }
    if (i == number_of_process_in_queue2 - 1) {
      i = 0;
      j = k;
    }

  }
  return -1;
}

void process() {
  struct process * p;
  p = & default_struct;
  p-> remaining_time = INT_MAX;
  struct process * q;
  q = & default_struct;
  int time;
  for (time = 0; complete != index_queue1 + index_queue2; time++) {
    for (i = 0; i < number_of_process_in_queue1; i++) {
      if (queue1[i].arrival_time == time) {
        if (p->remaining_time == INT_MAX) {
          p = & queue1[i];

        }

        if (queue1[i].remaining_time < p-> remaining_time)
          p = & queue1[i];
      }
    }
    //processing for queue1
    if (p-> remaining_time != INT_MAX) {
      p-> remaining_time--;
      flag_queue1=0;
      if (p-> remaining_time == 0) {

        complete++;
        p-> completion_time = time+1;
        //find next shortest
        p = & default_struct;
        p-> remaining_time = INT_MAX;

        for (j = 0; j < number_of_process_in_queue1; j++) {
          if (queue1[j].remaining_time < p-> remaining_time && queue1[j].arrival_time <= time && queue1[j].remaining_time != 0) {
            p = & queue1[j];
          }
        }
      }
      continue;
    }

    //Queue 2
    if (p-> remaining_time == INT_MAX) {

      //find next whose remaining is not zero
      if (indexi == -1) {
        indexi = nextindex(0, time);
        if (indexi == -1) //if not found continue
        {
          continue;
        }
      }

      q = & queue2[indexi];

      if (q-> arrival_time <= time && q-> remaining_time != 0) {

        q-> remaining_time--;
        flag_queue2=0;
        if (q-> remaining_time == 0) {
          q-> completion_time = time+1;
          complete++;
          quantum = 0;

          //find next whose remaining is not zero
          indexi = nextindex(indexi, time);
          continue;
        }
        quantum++;

        if (quantum == 2) {
          quantum = 0;

          //find next whose remaining is not zero
          k = nextindex(indexi, time);
          if (k != -1) {
            indexi = k;
          }
        }

      }
    }
  }
}

void calculate() {
  int i;
  for (i = 0; i < number_of_process_in_queue1; i++) {
    queue1[i].waiting_time = queue1[i].completion_time - (queue1[i].arrival_time + queue1[i].burst_time);
    queue1[i].turnaround_time = queue1[i].waiting_time + queue1[i].burst_time;
  }
  for (i = 0; i < number_of_process_in_queue2; i++) {
    queue2[i].waiting_time = queue2[i].completion_time - (queue2[i].arrival_time + queue2[i].burst_time);
    queue2[i].turnaround_time = queue2[i].waiting_time + queue2[i].burst_time;
  }
}

void display(struct process * p, int size) {
  red();
  font(16,20);
  printf("\nPid\t\tCompletion\t\tBurst Time\t\tWaiting Time\t\tTurnAroundTime\t    Arrival");
  blue();
  cls();
  int i;
  for (i = 0; i < size; i++) {
    printf("\n %d\t\t   %d\t\t\t      %d\t\t\t  %d\t\t\t    %d\t\t    %d", p[i].process_id, p[i].completion_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].arrival_time);
  }
  printf("\n\n");
}

int main() {
	settitle("OS PROJECT Q.52");
	while(1)
	{
	fullscreen();
  getinput();
  process();
  calculate();
  loading(2);
  cl;
  if(flag_queue1==0)
  {
  printf("\n\t\t\t\t\t\t\tQueue 1\n");
  display(queue1, index_queue1);
  }
  green();
   if(flag_queue2==0)
  {
  printf("\n\t\t\t\t\t\t\tQueue 2\n");
  display(queue2, index_queue2);
  }
  printf("\n\n\nDo you want to continue?     ");
  string s;
  green();
  scanf("%s",s);
  if(strcmp(s,"yes")==0)
  {
    fullscreen();
    cl;
  	continue;
  	
  }
  else
  {
  	break;
  }
}
}
