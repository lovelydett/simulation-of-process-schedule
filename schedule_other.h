#pragma once
#include"PCB.h"
void determine_counter(PCB pcb, int time);
int determine_max(PCB pcb, int time);
void run(PCB pcb, int max, int& time);
bool isAllSubmitFinish(PCB pcb, int time);
bool isAllFinish(PCB pcb);
bool isAllCounterZero(PCB pcb, int time);
/*
1，创建任务指定采用分时调度策略，并指定优先级nice值(-20~19)。

2，将根据每个任务的nice值确定在cpu上的执行时间(counter)。

3，如果没有等待资源，则将该任务加入到就绪队列中。

4，调度程序遍历就绪队列中的任务，通过对每个任务动态优先级的计算(counter+20-nice)结果，选择计算结果最大的一个去运行，当这个时间片用完后(counter减至0)或者主动放弃cpu时，该任务将被放在就绪队列末尾(时间片用完)或等待队列(因等待资源而放弃cpu)中。

5，此时调度程序重复上面计算过程，转到第4步。

6，当调度程序发现所有就绪任务计算所得的权值都为不大于0时，重复第2步。
*/

void schedule_other(PCB& pcb)
{
	if (pcb == NULL) return;
	int max;
	int time = 0;
	while (!isAllFinish(pcb))//仍有进程未完成
	{
		if (!isAllSubmitFinish(pcb, time))//仍有已提交的进程未完成
		{
			determine_counter(pcb, time);//根据nice值计算每个进程的counter
			while (!isAllCounterZero(pcb, time))//仍有权值大于零
			{
				max = determine_max(pcb, time);//计算counter + 20-nice的最大值
				run(pcb, max, time);//执行
			}
		}
		else //所有已提交的进程都完成了，time自增
			time++;
	}
	//至此所有进程完成
}


void determine_counter(PCB pcb,int time)
{
	//假设对nice值为20的进程分配100个时间片,nice值为0的进程分配200个，并以此为标准
	if (pcb == NULL) return;
	else
	{
		if(time>=pcb->submit_time&&!pcb->isFinish) pcb->counter = 200 - 5 * (pcb->nice);//判断进程已经提交且未完成才为其计算counter值
		determine_counter(pcb->next,time);
	}
}

int determine_max(PCB pcb,int time)
{
	int max = 0;
	while (pcb != NULL)
	{
		if (time >= pcb->submit_time && !pcb->isFinish && max < pcb->counter + 20 - pcb->nice) max = pcb->counter + 20 - pcb->nice;
		pcb = pcb->next;
	}
	return max;
}

void run(PCB pcb, int max, int& time)
{
	while (pcb != NULL)
	{
		if (max == pcb->counter + 20 - pcb->nice)
		{
			if (pcb->counter> pcb->request_left)  pcb->counter= pcb->request_left;
			pcb->request_left -= pcb->counter;
			time += pcb->counter;
			pcb->run_time += pcb->counter;
			pcb->counter = 0;
			
			if (pcb->request_left == 0)//在这次时间片之后完成了
			{
				pcb->isFinish = true;
				pcb->finish_time = time;
				pcb->run_time = pcb->finish_time - pcb->submit_time;
				pcb->weighed_run_time = (float)pcb->run_time / (float)pcb->request_time;
			}
			break;
		}
		else pcb = pcb->next;
	}
}

bool isAllSubmitFinish(PCB pcb,int time)//检测某一时刻是否全部已提交的都运行完了
{
	bool flag = true;
	while (pcb != NULL)
	{
		if(time>=pcb->submit_time) flag = flag*pcb->isFinish;
		pcb = pcb->next;
	}
	return flag;
}
bool isAllFinish(PCB pcb)//检测是否所有进程都运行完了
{
	bool flag = true;
	while (pcb!=NULL)
	{
		flag = flag*pcb->isFinish;
		pcb = pcb->next;
	}
	return flag;
}

bool isAllCounterZero(PCB pcb,int time)//判断是否当前可运行的所有进程都没有时间片了
{
	while (pcb != NULL)
	{
		if (time>=pcb->submit_time&&pcb->counter != 0) return false;
		pcb = pcb->next;
	}
	return true;
}