#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{

  int count, i, j, m=0, n, y=0, time, remain=0, min, flag=0;

	int wait_time=0, turn_a_time=0, a_time[10], b_time[10], p[10], z[10];

  float k=0, x=0;

  printf("Enter number of Processes :\t ");
  scanf("%d",&n);

	printf("\n----------------------------------------------------------------------------------------------------------");
  printf("\n\tNOTE:");
  printf("\n\t ----> ARRIVAL TIME SHOULD BE GREATER THAN 2 AS CPU REMAINS IDLE FOR FIRST 3 SECONDS <----\n");
  printf("\n\t ----> BURST TIME SHOULD BE LESS THAN 10 SECONDS <----\n");
	printf("\n----------------------------------------------------------------------------------------------------------\n\n\n");

  for(count=0; count < n; count++)
  {
    printf("Enter Arrival Time Process Number [%d] : ", count+1);

    	scanf("%d",&a_time[count]);

  	printf("Enter the Burst Time for Process Number [%d]: ", count+1);

    	scanf("%d",&b_time[count]);

  }

for(i=0;i<n;i++)
{
	if(a_time[i]==0)
	{
		printf("\n ----> INVALID ARRIVAL TIME <----\n");
		sleep(2);
		exit(1);
	}
}

for(i=0;i<n;i++)
{
	if(a_time[i]<3)
	{
		printf("\n -----------------------------> WARNING: <------------------------------------------------\n");
		printf("\n ----> INVALID ARRIVAL TIME FOR SOME PROCESSESS, IT SHOULD BE GREATER THAN 3 SECONDS <----\n");
		sleep(2);
		exit(1);
	}
}
  printf("\n\n\tPROCESS\t| TURN-AROUND TIME | WAITING TIME \n\n");
  printf("\t=====================================================\n");


for(i=0;i<n;i++)
{
	m=m+b_time[i];
}


min=10; // Time Quantum

time=m;

for(i=0;i<n;i++)
{
	if(a_time[i]<time)
	{
		time=a_time[i];
	}
}

for(i=time;i<=m;i=i+b_time[j])
{
	min=m;
	remain=0;
	flag=0;

	for(count=0;count<n;count++)
	{

		if(a_time[count]<=i)
		{

			if(b_time[count]<min)
			{

				min = b_time[count];
				j=count;
				flag=1;
			}
			remain=1;
		}
	}
	if(flag==1&&remain==1)
	{
		wait_time=i-a_time[j];
		turn_a_time=wait_time+b_time[j];
		printf("\tP[%d]\t|\t%d\t|\t%d\n",j+1,turn_a_time,wait_time);
		k=k+wait_time;
		x=x+turn_a_time;

		a_time[j]=m+1;
		p[y]=j+1;
		z[y]=i;
		y++;
	}
}

printf("\n\nAverage Waiting Time= %.2f\n",k/n);

printf("Avg Turnaround Time = %.2f",x/n);

printf("\n\n\nTotal time taken by processor to complete all the jobs : %d", m);
printf("\n\nProcess Execution Order:		");

for(i=0;i<n;i++)
{
	printf(" P[%d]   ",p[i]);
	if(i==(n-1))
	{
		printf("End\n");
	}
}


  return 0;
}