#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<ctime>


typedef struct ProcessControlBlock
{
	int pid;                  //����id
	int submit_time;          //�ύ��ʱ��
	int request_time;         //��Ҫ����ʱ��
	int request_left;         //��ǰ����Ҫ��ʱ��
	int finish_time;          //��ɵ�ʱ��
	int run_time;             //��תʱ��=���ʱ�̡��ύʱ��
	float weighed_run_time;   //��Ȩ��תʱ��=��תʱ��/������ʱ��
	int counter;              //���ηֵ���ʱ��Ƭ��С
	bool isFinish;            //��ɱ�־
    int priority;             //ʵʱ���ȼ�
	int nice;                 //��ʱ���ȼ�
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
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ��ʱ���ȼ�nice:%d �Ƿ���ɣ���, ��תʱ��: %d ��Ȩ��תʱ��: %.3f\n\n", pcb->pid, pcb->submit_time,pcb->request_time,pcb->nice,pcb->run_time,pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ��ʱ���ȼ�nice:%d �Ƿ���ɣ���, ��ִ��ʱ��: %d \n\n", pcb->pid, pcb->submit_time,pcb->request_time, pcb->nice, pcb->run_time);
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
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ʵʱ���ȼ�prio:%d �Ƿ���ɣ���, ��תʱ��: %d ��Ȩ��תʱ��: %.3f\n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->run_time, pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ʵʱ���ȼ�prio:%d �Ƿ���ɣ���, ��ִ��ʱ��: %d \n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->run_time);
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
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ʵʱ���ȼ�prio:%d ,niceֵ:%d ���Ƿ���ɣ���, ��תʱ��: %d ��Ȩ��תʱ��: %.3f\n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->nice, pcb->run_time, pcb->weighed_run_time);
		}
		else
		{
			printf("pid: %d, �ύʱ��:%d, ��Ҫʱ��:%d, ʵʱ���ȼ�prio:%d ,niceֵ:%d ���Ƿ���ɣ���, ��ִ��ʱ��: %d \n\n", pcb->pid, pcb->submit_time, pcb->request_time, pcb->priority, pcb->nice, pcb->run_time);
		}
		pcb_display_priority_and_nice(pcb->next);
	}
}


