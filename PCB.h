#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<ctime>


typedef struct ProcessControlBlock
{
	int pid;                  //进程id
	int submit_time;          //提交的时刻
	int request_time;         //需要的总时间
	int request_left;         //当前仍需要的时间
	int finish_time;          //完成的时刻
	int run_time;             //周转时间=完成时刻—提交时刻
	float weighed_run_time;   //带权周转时间=周转时间/总需求时间
	int counter;              //本次分到的时间片大小
	bool isFinish;            //完成标志
    int priority;             //实时优先级
	int nice;                 //分时优先级
	ProcessControlBlock* next;
}*PCB ;

void pcb_init(PCB& pcb,int n)
{
	if (n == 0) return;
	else
	{
		pcb = (PCB)malloc(sizeof(ProcessControlBlock));
		pcb->pid = n;
		pcb->counter = 0;
		pcb->isFinish = false;
		pcb->submit_time = rand() % 2000;
		pcb->request_left = pcb->request_time =(rand()*1000) % 5000+1000;
		pcb->finish_time = pcb->run_time = 0;
		pcb->weighed_run_time = 0;
		pcb->priority = rand() % 99 +1;
		pcb->nice = rand() % 40 - 19;
		pcb->next = NULL;
		pcb_init(pcb->next,--n);
	}
}
void pcb_display_nice(PCB pcb)
{
	if (pcb == NULL)return;
	else
	{
		if (pcb->isFinish)
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 分时优先级nice:%d 是否完成：是, 周转时间: %d 带权周转时间: %.3f\n\n", pcb->pid, pcb->submit_time,pcb->request_time,pcb->nice,pcb->run_time,pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 分时优先级nice:%d 是否完成：否, 已执行时间: %d \n\n", pcb->pid, pcb->submit_time,pcb->request_time, pcb->nice, pcb->run_time);
		}
		pcb_display_nice(pcb->next);
	}
}
void pcb_display_priority(PCB pcb)
{
	if (pcb == NULL)return;
	else
	{
		if (pcb->isFinish)
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 实时优先级prio:%d 是否完成：是, 周转时间: %d 带权周转时间: %.3f\n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->run_time, pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 实时优先级prio:%d 是否完成：否, 已执行时间: %d \n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->run_time);
		}
		pcb_display_priority(pcb->next);
	}
}
void pcb_display_priority_and_nice(PCB pcb)
{
	if (pcb == NULL)return;
	else
	{
		if (pcb->isFinish)
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 实时优先级prio:%d ,nice值:%d ，是否完成：是, 周转时间: %d 带权周转时间: %.3f\n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->nice, pcb->run_time, pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, 提交时间:%d, 需要时间:%d, 实时优先级prio:%d ,nice值:%d ，是否完成：否, 已执行时间: %d \n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->nice, pcb->run_time);
		}
		pcb_display_priority_and_nice(pcb->next);
	}
}


