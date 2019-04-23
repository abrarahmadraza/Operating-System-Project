#include "stdio.h"

#include "string.h"

#include "process.h"

#include "stdlib.h"

#include "stddef.h"

#include <math.h>

#include <time.h>

#include<windows.h>

#include "graphity.h"

#define cl system("cls")

typedef char string[20];

struct process {
  int burst_time;
  int process_id;
  int waiting_time;
  int turnaround_time;
  int remaining_time;
  int arrival_time;
  int priority;
  int completion_time;
}
default_struct = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

int number_of_queue1 = 0, number_of_queue2 = 0, number_of_queue3 = 0, number_of_processes = 0, i, j, k, complete = 0;
int flagRoundRobin = -1, flagPriority = -1, flagFCFS = -1;
int indexRR = -1, indexP = -1, indexF = -1;
COORD xy;
HANDLE h;
struct process * queue_of_RoundRobin, * queue_of_Priority, * queue_of_FCFS;

struct process * Process_for_RoundRobin = & default_struct;
struct process * Process_for_Priority = & default_struct;
struct process * Process_for_FCFS = & default_struct;

void getinput() {

  number_of_queue1 = 0;
  number_of_queue2 = 0;
  number_of_queue3 = 0;
  number_of_processes = 0;
  complete = 0;
  flagRoundRobin = -1;
  flagPriority = -1;
  flagFCFS = -1;
  indexRR = -1;
  indexP = -1;
  indexF = -1;

  red();
  cl;
  gotoxy(20, 5);
  font(65, 60);
  printf("Welcome");
  sleep(1);
  cl;
  cls();
  loading(1);
  font(20, 30);
  cls();
  centre();
  printf("\n\t\t\t Total Number of Process:\t");
  green();
  scanf("%d", & number_of_processes);

  cl;
  cls();
  loading(1);
  font(20, 30);
  //Allocatig Memory
  queue_of_RoundRobin = (struct process * ) malloc(number_of_processes * sizeof(struct process));
  queue_of_Priority = (struct process * ) malloc(number_of_processes * sizeof(struct process));
  queue_of_FCFS = (struct process * ) malloc(number_of_processes * sizeof(struct process));
  int i, random = (rand()) % (10000 + 1);

  yellow();
  printf("\n\t\tProcess \t");
  printf("Priority(1-9)");
  printf("\t Burst Time");
  printf("\t Algorithm");
  green();
  cls();

  for (i = 0; i < number_of_processes; i++) {
    struct process p1;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    xy = cursorpos(h);
    gotoxy(xy.X, xy.Y);

    printf("\n\t\tProcess %d", i + 1);
    p1.process_id = random++;
    p1.arrival_time = 0;

    h = GetStdHandle(STD_OUTPUT_HANDLE);
    xy = cursorpos(h);
    gotoxy(40, xy.Y);
    scanf("%d", & p1.priority);
    gotoxy(50, xy.Y);
    scanf("%d", & p1.burst_time);
    gotoxy(65, xy.Y);

    p1.remaining_time = p1.burst_time;
    if (p1.priority > 0 && p1.priority <= 3) {
      flagRoundRobin = 0;
      queue_of_RoundRobin[number_of_queue1++] = p1;
      puts("Round Robin");
    } else if (p1.priority > 3 && p1.priority <= 6) {
	  flagPriority = 0;
      queue_of_Priority[number_of_queue2++] = p1;
      puts("Priority");
    } else {
      flagFCFS = 0;
      queue_of_FCFS[number_of_queue3++] = p1;
      puts("FCFS");
    }
  }
  sleep(1);
}

int nextindexRR(int index, int tim) {
  j = number_of_queue1;
  k = index;
  if (k == -1) {
    k = 0;
  }
  for (i = k; i < j; i++) {
    if (queue_of_RoundRobin[i].arrival_time <= tim && queue_of_RoundRobin[i].remaining_time != 0) {
      return i;
      break;
    }
    if (i == number_of_queue1 - 1) {
      i = 0;
      j = k;
    }

  }
  return -1;

}
int roundrobin(int tim) {
  int quantum = 0, time = tim, lasttime = tim;

  while (time < tim + 10) {
    if (indexRR == -1) {
      indexRR = nextindexRR(indexRR, time);
      if (indexRR == -1) {
        time++;
        continue;
      }

    }

    Process_for_RoundRobin = & queue_of_RoundRobin[indexRR];
    

    Process_for_RoundRobin->remaining_time--;
    time++;
    lasttime = time;
    if (Process_for_RoundRobin->remaining_time == 0) {

      Process_for_RoundRobin->completion_time = time;
      complete++;
      quantum = 0;

      //find next 
      indexRR = nextindexRR(indexRR, time);
      continue;
    }
    quantum++;

    if (quantum == 4) //quantum=4
    {
      quantum = 0;

      //find next 
      k = nextindexRR(indexRR, time);
      if (k != -1) {
        indexRR = k;
      }
    }
  }
  return lasttime;
}
int nextindexP(int index, int tim) {
  int highprio = INT_MAX;
  j = number_of_queue2;
  k = index;
  if (k == -1) {
    k = 0;
  }
  for (i = k; i < j; i++) {
    if (queue_of_Priority[i].arrival_time <= tim && queue_of_Priority[i].remaining_time != 0 && queue_of_Priority[i].priority < highprio) {
      index = i;
      highprio = queue_of_Priority[i].priority;
    }
    if (i == number_of_queue2 - 1) {
      i = 0;
      j = k;
    }
  }
  if (highprio != INT_MAX)
    return index;

  return -1;

}
int priority(int tim) {
  int time = tim, lasttime = tim;
  while (time < tim + 10) {
    if (indexP == -1) {
      indexP = nextindexP(indexP, time);
      if (indexP == -1) {
        time++;
        continue;
      }

    }
    Process_for_Priority = & queue_of_Priority[indexP];
    

    Process_for_Priority->remaining_time--;
    time++;
    lasttime = time;
    if (Process_for_Priority->remaining_time == 0) {
      Process_for_Priority->completion_time = time;
      complete++;

      //find next 
      indexP = nextindexP(indexP, time);
      continue;
    }

  }
  return lasttime;
}

int nextindexF(int index, int tim) {
  j = number_of_queue3;
  k = index;
  if (k == -1) {
    k = 0;
  }
  for (i = k; i < j; i++) {
    if (queue_of_FCFS[i].arrival_time <= tim && queue_of_FCFS[i].remaining_time != 0) {
      return i;
      break;
    }
    if (i == number_of_queue3 - 1) {
      i = 0;
      j = k;
    }

  }
  return -1;

}
int FCFS(int tim) {
  int time = tim, lasttime = tim;
  while (time < tim + 10) {
    if (indexF == -1) {
      indexF = nextindexF(indexF, time);
      if (indexF == -1) {
        time++;
        continue;
      }
    }

    Process_for_FCFS = & queue_of_FCFS[indexF];
    

    Process_for_FCFS->remaining_time--;

    time++;
    lasttime = time;
    if (Process_for_FCFS->remaining_time == 0) {
      Process_for_FCFS->completion_time = time;
      complete++;

      //find next 
      indexF = nextindexF(indexF, time);
      continue;
    }
  }
  return lasttime;
}
void process() {
  int time;
  for (time = 0; complete != number_of_queue1 + number_of_queue2 + number_of_queue3;) {
  	if(flagRoundRobin == 0)
    time = roundrobin(time);
    if(flagPriority == 0)
    time = priority(time);
    if(flagFCFS == 0)
    time = FCFS(time);
  }
}

void calculate() {
  int i;
  for (i = 0; i < number_of_queue1; i++) {
    queue_of_RoundRobin[i].waiting_time = queue_of_RoundRobin[i].completion_time - (queue_of_RoundRobin[i].arrival_time + queue_of_RoundRobin[i].burst_time);
    queue_of_RoundRobin[i].turnaround_time = queue_of_RoundRobin[i].waiting_time + queue_of_RoundRobin[i].burst_time;
  }
  for (i = 0; i < number_of_queue2; i++) {
    queue_of_Priority[i].waiting_time = queue_of_Priority[i].completion_time - (queue_of_Priority[i].arrival_time + queue_of_Priority[i].burst_time);
    queue_of_Priority[i].turnaround_time = queue_of_Priority[i].waiting_time + queue_of_Priority[i].burst_time;
  }
  for (i = 0; i < number_of_queue3; i++) {
    queue_of_FCFS[i].waiting_time = queue_of_FCFS[i].completion_time - (queue_of_FCFS[i].arrival_time + queue_of_FCFS[i].burst_time);
    queue_of_FCFS[i].turnaround_time = queue_of_FCFS[i].waiting_time + queue_of_FCFS[i].burst_time;
  }
}

void display(struct process * t, int size) {

  red();
  font(20, 23);
  printf("\nPid\tCompletion\tBurst Time\tWaiting Time\tTurnAroundTime\tArrival");
  blue();
  cls();
  int i;
  for (i = 0; i < size; i++) {
    printf("\n%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d", t[i].process_id, t[i].completion_time, t[i].burst_time, t[i].waiting_time, t[i].turnaround_time, t[i].arrival_time);
  }
  printf("\n\n");
}

int main() {
  settitle("OS PROJECT Process_for_Priority.25");
  fullscreen();
  getinput();
  process();
  calculate();
  loading(2);
  
  if (flagRoundRobin == 0) {
    printf("\n\t\t\t\tRound Robin\n");
    display(queue_of_RoundRobin, number_of_queue1);
  }

  green();
  if (flagPriority == 0) {
    printf("\n\t\t\t\tPriority\n");
    display(queue_of_Priority, number_of_queue2);
  }
  green();
  if (flagFCFS == 0) {
    printf("\n\t\t\t\tFCFS\n");
    display(queue_of_FCFS, number_of_queue3);
  }
}
