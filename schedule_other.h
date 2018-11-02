#pragma once
#include"PCB.h"
void determine_counter(PCB pcb, int time);
int determine_max(PCB pcb, int time);
void run(PCB pcb, int max, int& time);
bool isAllSubmitFinish(PCB pcb, int time);
bool isAllFinish(PCB pcb);
bool isAllCounterZero(PCB pcb, int time);
/*
1����������ָ�����÷�ʱ���Ȳ��ԣ���ָ�����ȼ�niceֵ(-20~19)��

2��������ÿ�������niceֵȷ����cpu�ϵ�ִ��ʱ��(counter)��

3�����û�еȴ���Դ���򽫸�������뵽���������С�

4�����ȳ���������������е�����ͨ����ÿ������̬���ȼ��ļ���(counter+20-nice)�����ѡ�����������һ��ȥ���У������ʱ��Ƭ�����(counter����0)������������cpuʱ�������񽫱����ھ�������ĩβ(ʱ��Ƭ����)��ȴ�����(��ȴ���Դ������cpu)�С�

5����ʱ���ȳ����ظ����������̣�ת����4����

6�������ȳ��������о�������������õ�Ȩֵ��Ϊ������0ʱ���ظ���2����
*/

void schedule_other(PCB& pcb)
{
	if (pcb == NULL) return;
	int max;
	int time = 0;
	while (!isAllFinish(pcb))//���н���δ���
	{
		if (!isAllSubmitFinish(pcb, time))//�������ύ�Ľ���δ���
		{
			determine_counter(pcb, time);//����niceֵ����ÿ�����̵�counter
			while (!isAllCounterZero(pcb, time))//����Ȩֵ������
			{
				max = determine_max(pcb, time);//����counter + 20-nice�����ֵ
				run(pcb, max, time);//ִ��
			}
		}
		else //�������ύ�Ľ��̶�����ˣ�time����
			time++;
	}
	//�������н������
}


void determine_counter(PCB pcb,int time)
{
	//�����niceֵΪ20�Ľ��̷���100��ʱ��Ƭ,niceֵΪ0�Ľ��̷���200�������Դ�Ϊ��׼
	if (pcb == NULL) return;
	else
	{
		if(time>=pcb->submit_time&&!pcb->isFinish) pcb->counter = 200 - 5 * (pcb->nice);//�жϽ����Ѿ��ύ��δ��ɲ�Ϊ�����counterֵ
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
			
			if (pcb->request_left == 0)//�����ʱ��Ƭ֮�������
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

bool isAllSubmitFinish(PCB pcb,int time)//���ĳһʱ���Ƿ�ȫ�����ύ�Ķ���������
{
	bool flag = true;
	while (pcb != NULL)
	{
		if(time>=pcb->submit_time) flag = flag*pcb->isFinish;
		pcb = pcb->next;
	}
	return flag;
}
bool isAllFinish(PCB pcb)//����Ƿ����н��̶���������
{
	bool flag = true;
	while (pcb!=NULL)
	{
		flag = flag*pcb->isFinish;
		pcb = pcb->next;
	}
	return flag;
}

bool isAllCounterZero(PCB pcb,int time)//�ж��Ƿ�ǰ�����е����н��̶�û��ʱ��Ƭ��
{
	while (pcb != NULL)
	{
		if (time>=pcb->submit_time&&pcb->counter != 0) return false;
		pcb = pcb->next;
	}
	return true;
}