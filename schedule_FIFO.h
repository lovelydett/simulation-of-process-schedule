#pragma once
#include"PCB.h"
#include"schedule_other.h"

/*
1����������ʱָ������FIFO��������ʵʱ���ȼ�rt_priority(1-99)��

2, ���û�еȴ���Դ���򽫸�������뵽���������С�

3�����ȳ�������������У�����ʵʱ���ȼ��������Ȩֵ(1000+rt_priority),ѡ��Ȩֵ��ߵ�����ʹ��cpu����FIFO����һֱռ��cpuֱ�������ȼ����ߵ��������(��ʹ���ȼ���ͬҲ����)������������(�ȴ���Դ)��

4�����ȳ����������ȼ����ߵ����񵽴�(�����ȼ�������ܱ��жϻ�ʱ�������ѣ��ٻ򱻵�ǰ���е������ѣ��ȵ�)������ȳ��������ڵ�ǰ�����ջ�б��浱ǰcpu�Ĵ������������ݣ����´Ӹ����ȼ�����Ķ�ջ�м��ؼĴ������ݵ�cpu����ʱ�����ȼ�������ʼ���С��ظ���3����

5�������ǰ������ȴ���Դ����������cpuʹ��Ȩ��������񽫴Ӿ���������ɾ��������ȴ����У���ʱ�ظ���3����

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
			current = determine_max_weight(pcb, time);//ÿ��һ��ʱ�䵥λ�ͼ��������޸������ȼ��Ľ��̣������л�
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

