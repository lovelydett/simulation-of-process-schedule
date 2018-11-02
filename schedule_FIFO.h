#pragma once
#include"PCB.h"
#include"schedule_other.h"

/*
1，创建进程时指定采用FIFO，并设置实时优先级rt_priority(1-99)。

2, 如果没有等待资源，则将该任务加入到就绪队列中。

3，调度程序遍历就绪队列，根据实时优先级计算调度权值(1000+rt_priority),选择权值最高的任务使用cpu，该FIFO任务将一直占有cpu直到有优先级更高的任务就绪(即使优先级相同也不行)或者主动放弃(等待资源)。

4，调度程序发现有优先级更高的任务到达(高优先级任务可能被中断或定时器任务唤醒，再或被当前运行的任务唤醒，等等)，则调度程序立即在当前任务堆栈中保存当前cpu寄存器的所有数据，重新从高优先级任务的堆栈中加载寄存器数据到cpu，此时高优先级的任务开始运行。重复第3步。

5，如果当前任务因等待资源而主动放弃cpu使用权，则该任务将从就绪队列中删除，加入等待队列，此时重复第3步。

*/
PCB determine_max_weight(PCB pcb, int time);
void schedule_FIFO(PCB pcb)
{
	int time = 0;
	PCB current = NULL;
	while (!isAllFinish(pcb))
	{
		while (!isAllSubmitFinish(pcb,time))
		{
			current = determine_max_weight(pcb, time);//每过一个时间单位就检查队列有无更高优先级的进程，有则切换
			current->request_left--;
			current->run_time++;
			time++;
			if (current->request_left <= 0)
			{
				current->isFinish = true;
				current->finish_time = time;
				current->run_time = current->finish_time - current->submit_time;
				current->weighed_run_time = (float)current->run_time / (float)current->request_time;
			}
		}
		time++;
	}
}


PCB determine_max_weight(PCB pcb,int time)
{
	int max=0;
	PCB temp=NULL;
	while (pcb != NULL)
	{
		if (!pcb->isFinish && time >= pcb->submit_time&&max < pcb->priority)
		{
			max = pcb->priority;
			temp = pcb;
		}
		pcb = pcb->next;
	}
	return temp;
}

