#pragma once
#include"PCB.h"
#include"schedule_FIFO.h"
#include"schedule_other.h"
/*
1����������ʱָ�����Ȳ���ΪRR�������������ʵʱ���ȼ���niceֵ(niceֵ����ת��Ϊ�������ʱ��Ƭ�ĳ���)��

2�����û�еȴ���Դ���򽫸�������뵽���������С�

3�����ȳ�������������У�����ʵʱ���ȼ��������Ȩֵ(1000+rt_priority),ѡ��Ȩֵ��ߵ�����ʹ��cpu��

4��������������е�RR����ʱ��ƬΪ0��������niceֵ���ø������ʱ��Ƭ��ͬʱ�����������������е�ĩβ���ظ�����3��

5����ǰ�������ڵȴ���Դ�������˳�cpu���������ȴ������С��ظ�����3��
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
			determine_counter(pcb, time);//����ʵʱ���ȼ��õ���һ��Ҫִ�еĽ���
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

			//���²��ֽ�ִ����һ��ʱ��Ƭ�Ľ��̵���������β
			temp = current;
			while (temp->next != NULL) temp = temp->next;//�ҵ�ԭ����β
			temp->next = pcb;//ԭ������β���
			pcb = current->next;//������ͷΪcurrent����һ��
			current->next = NULL;//��ǰִ����ĳ�Ϊ��β
		}
		time++;
	}
}


