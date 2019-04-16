#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct Queue
{
	int pid;
	int arrvalTime;
	int burstTime;
};
  
float processFun(struct Queue* q, int size,struct Queue* Que);
void minArrTime(struct Queue* que,int size);
void minBurstTime(struct Queue* que,int size);
int checkAllProFinsh(struct Queue* Que,int size);

float calTotBurstTime(struct Queue* Que,int n)
{
	//to calculate total burst time
	float burstTime=0;
	for(int i=0;i<n;i++)
	{
	
		burstTime+=(Que+i)->burstTime;
	return burstTime;
}
}

int main()
{
	int i,n1,n2;
	float totTurnAroundTime,avgTurnAroundTime,avgWaitingTime,totBurstTime;
	printf("\n ************************* SHORTEST JOB REMAINING FIRST (WITH PREEMPTIVE and MULTILEVEL QUEUE) ***********************************\n");
	printf("\nNo of Processes in Queue1: ");
	scanf("%d",&n1);
	struct Queue *q1=(struct Queue*)malloc(n1*sizeof(struct Queue));
	struct Queue *Que1=(struct Queue*)malloc(n1*sizeof(struct Queue));
	printf("\nEnter the following Details for Processes in Queue1:\n");

	for(i=0;i<n1;i++)
	{
		printf("For Process %d:\n",i+1);
		(q1+i)->pid=i+1;
		(Que1+i)->pid=i+1;
		printf("PId: %d\n", (q1+i)->pid);
		printf("Arrival Time: ");
		scanf("%d",&(q1+i)->arrvalTime);
		(Que1+i)->arrvalTime=(q1+i)->arrvalTime;
		printf("Burst Time: ");
		scanf("%d",&(q1+i)->burstTime);
		(Que1+i)->burstTime=(q1+i)->burstTime;
		printf("\n");
	}

	printf("No of Processes in Queue2: ");
	scanf("%d",&n2);
	struct Queue *q2=(struct Queue*)malloc(n1*sizeof(struct Queue));
	struct Queue *Que2=(struct Queue*)malloc(n1*sizeof(struct Queue));
	printf("\nEnter the following Details for Processes in Queue2:\n");
	for(i=0;i<n2;i++)
	{
		printf("For Process %d:\n",i+1);
		(q2+i)->pid=i+1;
		(Que2+i)->pid=i+1;
		printf("PId: %d\n", (q2+i)->pid);
		
		printf("Arrival Time: ");
		scanf("%d",&(q2+i)->arrvalTime);
		(Que2+i)->arrvalTime=(q2+i)->arrvalTime;
		printf("Burst Time: ");
		scanf("%d",&(q2+i)->burstTime);
		(Que2+i)->burstTime=(q2+i)->burstTime;
		printf("\n");
	}

	printf("\n");

	printf("\nDetais Of Processes in Queue1\n");
	printf("\n Process:     |  Arrival Time:     |   Burst Time:     | ");
	for(i=0;i<n1;i++)
    {
        printf("\n P%d                %d                   %d      ",(q1+i)->pid,(q1+i)->arrvalTime,(q1+i)->burstTime);
    }

    printf("\n");

    printf("\nDetais Of Processes in Queue2\n");
	printf("\n Process:     |   Arival Time:     |   Burst Time:     | ");
	for(i=0;i<n2;i++)
    {
        printf("\n P%d                %d                   %d      ",(q2+i)->pid,(q2+i)->arrvalTime,(q2+i)->burstTime);
    }

    printf("\n\n");

    totTurnAroundTime=processFun(q1,n1,Que1);
    avgTurnAroundTime=totTurnAroundTime/n1;
    totBurstTime=calTotBurstTime(q1,n1);
    avgWaitingTime=(totTurnAroundTime-totBurstTime)/n1;

    printf("\nFor Queue1");
    printf("\nAverage Turn Around Time: %.2f\n", avgTurnAroundTime);
    printf("\nAverage Waiting Time: %.2f\n",avgWaitingTime);

    printf("\n\n");

    totTurnAroundTime=processFun(q2,n2,Que2);
    avgTurnAroundTime=totTurnAroundTime/n2;
    totBurstTime=calTotBurstTime(q2,n2);
    avgWaitingTime=(totTurnAroundTime-totBurstTime)/n2;

    printf("\nFor Queue2");
    printf("\nAverage Turn Around Time: %.2f\n", avgTurnAroundTime);
    printf("\nAverage Waiting Time: %.2f\n",avgWaitingTime);
    printf("\n\n");
	return 0;
}

float processFun(struct Queue* q, int size,struct Queue* Que)
{
	int timeCountr=0,flag=0;
	float tAt=0,wT=0;
	while(!checkAllProFinsh(Que,size))
	{
		if(flag==0)
		{
			minArrTime(Que,size);
			timeCountr+=Que->arrvalTime;
			flag++;
		}
		else
		{
			minBurstTime(Que,size);
		}
		int chk=0;
		for(int i=0;i<size;i++)
		{
			if((Que+i)->burstTime!=0 && timeCountr>=(Que+i)->arrvalTime)
			{
				chk=1;
				break;
			}
					
		}
		if(chk==0)
		{
			minArrTime(Que,size);
			for(int i=0;i<size;i++)
			{
				if((Que+i)->burstTime!=0)
				{
					int x=timeCountr;
					timeCountr+=((Que+i)->arrvalTime)-x;
					break;
				}
			}
		}
		for(int i=0;i<size;i++)
		{
			if((Que+i)->burstTime!=0 && timeCountr>=(Que+i)->arrvalTime)
			{
				if((Que+i)->burstTime>2)
				{
					(Que+i)->burstTime=(Que+i)->burstTime-2;
					timeCountr+=2;
				}
				else
				{
					timeCountr+=(Que+i)->burstTime;
					(Que+i)->burstTime=0;
					int x=timeCountr;
					tAt+=x-((Que+i)->arrvalTime);
				}
				break;				
			}
		}
	}
	return tAt;
}

void minArrTime(struct Queue* que,int size)
{
	int i,j;
	for(i=1;i<=size-1;i++)
	{
		for(j=0;j<size-1;j++)
		{
			if(((que+j)->arrvalTime)>((que+j+1)->arrvalTime))
			{
				//to swap Arrival time in dec Order
				int temp=(que+j)->arrvalTime;
				(que+j)->arrvalTime=(que+j+1)->arrvalTime;
				(que+j+1)->arrvalTime=temp;

				//to swap Burst Time in dec Order
				temp=(que+j)->burstTime;
				(que+j)->burstTime=(que+j+1)->burstTime;
				(que+j+1)->burstTime=temp;

				//to swap pid 
				temp=(que+j)->pid;
				(que+j)->pid=(que+j+1)->pid;
				(que+j+1)->pid=temp;
			}
			else if(((que+j)->arrvalTime)==((que+j+1)->arrvalTime))
			{
				if(((que+j)->burstTime)>((que+j+1)->burstTime))
				{
					//to swap Burst Time in dec Order
					int temp=(que+j)->burstTime;
					(que+j)->burstTime=(que+j+1)->burstTime;
					(que+j+1)->burstTime=temp;

					//to swap pid 
					temp=(que+j)->pid;
					(que+j)->pid=(que+j+1)->pid;
					(que+j+1)->pid=temp;

					//to swap Arrival time in dec Order
					temp=(que+j)->arrvalTime;
					(que+j)->arrvalTime=(que+j+1)->arrvalTime;
					(que+j+1)->arrvalTime=temp;
				}
			}
		}
	}
}

int checkAllProFinsh(struct Queue* Que,int size)
{
	//to check is there any processes left yet to be processed
	int flag=1;
	for(int i=0;i<size;i++)
	{
		if((Que+i)->burstTime!=0)
		{
			flag=0;
			return flag;
		}	
	}
	return flag;
}

void minBurstTime(struct Queue* que,int size)
{
	int i,j;
	for(i=1;i<=size-1;i++)
	{
		for(j=0;j<size-1;j++)
		{
			if(((que+j)->burstTime)>((que+j+1)->burstTime))
			{
				//to swap Burst Time in dec Order
				int temp=(que+j)->burstTime;
				(que+j)->burstTime=(que+j+1)->burstTime;
				(que+j+1)->burstTime=temp;

				//to swap pid 
				temp=(que+j)->pid;
				(que+j)->pid=(que+j+1)->pid;
				(que+j+1)->pid=temp;

				//to swap Arrival time in dec Order
				temp=(que+j)->arrvalTime;
				(que+j)->arrvalTime=(que+j+1)->arrvalTime;
				(que+j+1)->arrvalTime=temp;	
			}
		}
	}
}

