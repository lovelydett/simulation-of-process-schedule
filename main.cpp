#include<stdio.h>
#include<windows.system.h>
#include"PCB.h"
#include"schedule_other.h"
#include"schedule_FIFO.h"

int main()
{
	printf("**ʵ���� ���̵��� 2016211969 л���� \n\n");
	PCB head=NULL;
	printf("1.Schedule_OTHER���ȣ�\n\n   ��ʼ�����ݣ�\n\n");
	pcb_init(head,5);
	pcb_display_nice(head);
	schedule_other(head);
	printf("���н����\n\n");
	pcb_display_nice(head);
	printf("-----------------------------------------------------------------------\n");

	printf("2.Schedule_FIFO���ȣ�\n\n   ��ʼ�����ݣ�\n\n");
	pcb_init(head, 5);
	pcb_display_priority(head);
	schedule_FIFO(head);
	printf("���н����\n\n");
	pcb_display_priority(head);
    printf("-----------------------------------------------------------------------\n");

	printf("3.Schedule_RR���ȣ�\n\n   ��ʼ�����ݣ�\n\n");
	pcb_init(head, 5);
	pcb_display_priority_and_nice(head);
	schedule_FIFO(head);
	printf("���н����\n\n");
	pcb_display_priority_and_nice(head);
	system("pause");
	return 0;
}




