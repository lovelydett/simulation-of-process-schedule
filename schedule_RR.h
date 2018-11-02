#pragma once
#include"PCB.h"
#include"schedule_FIFO.h"
#include"schedule_other.h"
/*
1，创建任务时指定调度参数为RR，并设置任务的实时优先级和nice值(nice值将会转换为该任务的时间片的长度)。

2，如果没有等待资源，则将该任务加入到就绪队列中。

3，调度程序遍历就绪队列，根据实时优先级计算调度权值(1000+rt_priority),选择权值最高的任务使用cpu。

4，如果就绪队列中的RR任务时间片为0，则会根据nice值设置该任务的时间片，同时将该任务放入就绪队列的末尾。重复步骤3。

5，当前任务由于等待资源而主动退出cpu，则其加入等待队列中。重复步骤3。
*/

void schedule_RR(PCB pcb)
{
	int time=0;
	PCB current;
	PCB temp;
	while (!isAllFinish(pcb))
	{
		while (!isAllSubmitFinish(pcb,time))
		{
			determine_counter(pcb, time);//根据实时优先级得到下一个要执行的进程
			current = determine_max_weight(pcb, time);
			if (current->counter > current->request_left) current->counter = current->request_left;
			current->request_left -= current->counter;
			time += current->counter;
			current->counter = 0;
			if (current->request_left == 0)
			{
				current->isFinish = true;
				current->finish_time = time;
				current->run_time = current->finish_time - current->submit_time;
				current->weighed_run_time = (float)current->run_time / (float)current->request_time;
			}

			//以下部分将执行完一个时间片的进程调整到队列尾
			temp = current;
			while (temp->next != NULL) temp = temp->next;//找到原队列尾
			temp->next = pcb;//原队列首尾相接
			pcb = current->next;//队列新头为current的下一个
			current->next = NULL;//当前执行完的成为新尾
		}
		time++;
	}
}


