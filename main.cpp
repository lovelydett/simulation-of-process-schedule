#include<stdio.h>
#include<windows.system.h>
#include"PCB.h"
#include"schedule_other.h"
#include"schedule_FIFO.h"

int main()
{
	printf("**实验四 进程调度 2016211969 谢宇霆 \n\n");
	PCB head=NULL;
	printf("1.Schedule_OTHER调度：\n\n   初始化数据：\n\n");
	pcb_init(head,5);
	pcb_display_nice(head);
	schedule_other(head);
	printf("运行结果：\n\n");
	pcb_display_nice(head);
	printf("-----------------------------------------------------------------------\n");

	printf("2.Schedule_FIFO调度：\n\n   初始化数据：\n\n");
	pcb_init(head, 5);
	pcb_display_priority(head);
	schedule_FIFO(head);
	printf("运行结果：\n\n");
	pcb_display_priority(head);
    printf("-----------------------------------------------------------------------\n");

	printf("3.Schedule_RR调度：\n\n   初始化数据：\n\n");
	pcb_init(head, 5);
	pcb_display_priority_and_nice(head);
	schedule_FIFO(head);
	printf("运行结果：\n\n");
	pcb_display_priority_and_nice(head);
	system("pause");
	return 0;
}




