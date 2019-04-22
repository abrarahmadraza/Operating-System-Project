#include "stdio.h"

#include "string.h"

#include "process.h"

#include "stdlib.h"

#include "stddef.h"

#include <math.h>

#include <time.h>

#define cl system("cls")

typedef char string[20];

struct process {
  int burst_time;
  int pid;
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

int nopq1, nopq2, q1_n = 0, q2_n = 0, i, j, quantum = 0, indexi = -1, k = 0, complete = 0, flagq1=-1, flagq2=-1;
struct process * q1, * q2;
void getinput();

void getinput() {
  printf("\n Total Number of Process in queue 1:\t");
  scanf("%d", & nopq1);
  printf("\n Total Number of Process in queue 2:\t");
  scanf("%d", & nopq2);
  //Allocatig Memory
  q1 = (struct process * ) malloc(nopq1 * sizeof(struct process));
  q2 = (struct process * ) malloc(nopq2 * sizeof(struct process));

  printf("\n\t\tQueue 1\n=============================================\n\n");
  struct process p; //mediator variable
  int i ;
  //Take Input

  for (i = 0; i < nopq1; i++) {

    printf("\n\t\tProcess %d\n=============================================\n\n", i + 1);
    p.pid = (rand()) % (10000 + 1);
    printf("Arrival Time:\t");
    scanf("%d", & p.arrival_time);
    printf("\nBurst Time:\t");
    scanf("%d", & p.burst_time);
    p.remaining_time = p.burst_time;
    q1[q1_n++] = p;

  }

  //Queue 2 input
  printf("\n\t\tQueue 2\n=============================================\n\n");
  for (i = 0; i < nopq2; i++) {

    printf("\n\t\tProcess %d\n=============================================\n\n", i + 1);
    p.pid = (rand()) % (10000 + 1);
    printf("Arrival Time:\t");
    scanf("%d", & p.arrival_time);
    printf("\nBurst Time:\t");
    scanf("%d", & p.burst_time);
    p.remaining_time = p.burst_time;
    q2[q2_n++] = p;

  }

}

int nextindex(int ka, int tim) {
  j = nopq2;
  k = ka;
  if (k == nopq2 - 1) {
    k = 0;
  }
  for (i = k; i < j; i++) {
    if (q2[i].arrival_time <= tim && q2[i].remaining_time != 0) {
      return i;
      break;
    }
    if (i == nopq2 - 1) {
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
  for (time = 0; complete != q1_n + q2_n; time++) {
    for (i = 0; i < nopq1; i++) {
      if (q1[i].arrival_time == time) {
        if (p->remaining_time == INT_MAX) {
          p = & q1[i];

        }

        if (q1[i].remaining_time < p-> remaining_time)
          p = & q1[i];
      }
    }
    //processing for q1
    if (p-> remaining_time != INT_MAX) {
      p-> remaining_time--;
      flagq1=0;
      if (p-> remaining_time == 0) {

        complete++;
        p-> completion_time = time;
        //find next shortest
        p = & default_struct;
        p-> remaining_time = INT_MAX;

        for (j = 0; j < nopq1; j++) {
          if (q1[j].remaining_time < p-> remaining_time && q1[j].arrival_time <= time && q1[j].remaining_time != 0) {
            p = & q1[j];
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

      q = & q2[indexi];

      if (q-> arrival_time <= time && q-> remaining_time != 0) {

        q-> remaining_time--;
        flagq2=0;
        if (q-> remaining_time == 0) {
          q-> completion_time = time;
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
  for (i = 0; i < nopq1; i++) {
    
    q1[i].waiting_time = q1[i].completion_time - (q1[i].arrival_time + q1[i].burst_time)+1;
    q1[i].turnaround_time = q1[i].waiting_time + q1[i].burst_time;
  }
  for (i = 0; i < nopq2; i++) {
    
    q2[i].waiting_time = q2[i].completion_time - (q2[i].arrival_time + q2[i].burst_time)+1;
    q2[i].turnaround_time = q2[i].waiting_time + q2[i].burst_time;
  }
}

void display(struct process * p, int size) {
  printf("\nPId\t\tCompletion\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival");
  printf("\n========================================================================================================================\n");
  int i;
  for (i = 0; i < size; i++) {
    printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\t%d", p[i].pid, p[i].completion_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time, p[i].arrival_time);
  }
  printf("\n\n");
}

int main() {
  getinput();
  process();
  calculate();
  if(flagq1==0)
  {
  printf("\n\t\tQueue 1\n=============================================\n\n");
  display(q1, q1_n);
  }
   if(flagq2==0)
  {
  printf("\n\t\tQueue 2\n=============================================\n\n");
  display(q2, q2_n);
  }
}
