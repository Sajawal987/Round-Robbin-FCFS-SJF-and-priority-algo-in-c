#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
int n;
struct Robbin{
    int brust;
    int turn;
    int wait;
    int id;
};
struct process
{
    int pid;
    int w_time;
    int t_time;
    int b_time;
    int priority;
    int rounds;
    int Rem_B_Time;
};

int TotalRounds = 0;

void calculate_WaitTime(struct process *x, int i, struct process p[])
{
   
    x->w_time = p[i-1].w_time + p[i-1].b_time;
}

void calculate_TurnAroundTime(struct process *x, int i, struct process p[])
{
    x->t_time = p[i].w_time + p[i].b_time;
}

void Display_Table(struct process p[])
{
    printf("----------------------------------\n");
    printf("Process B-Time  T-Time  W-Time\n");
    printf("----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%7d\t%6d\t%6d\t%6d\n", p[i].pid, p[i].b_time, p[i].t_time, p[i].w_time);
    }
    printf("----------------------------------\n");
}
void Display_Table_P(struct process p[])
{
    printf("----------------------------------\n");
    printf("Process B-Time  T-Time  W-Time  Priority\n");
    printf("----------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%7d\t%6d\t%6d\t%6d\t%8d\n", p[i].pid, p[i].b_time, p[i].t_time, p[i].w_time, p[i].priority);
    }
    printf("----------------------------------\n");
}
void Grantt_Chart(struct process p[])
{
    printf("\n\nGRANTT Chart\n");
    for (int i = 0; i < p[n - 1].t_time; i++)
    {
        printf("-");
    }
    printf("\n");

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < (p[j].b_time); i++)
        {
            int mid = (p[j].b_time / 2) - 1; // as we start from 0 so mid is 4/2 = 2 - 1 = 1 etc;
            if (i == p[j].b_time - 1 || (i == 0 && j == 0))
            {
                printf("|");
            }
            else if (j == n - 1 && i == (p[j].b_time - 1))
            {
                printf("|");
            }
            else if (i == mid)
            {
                printf("p");
            }
            else if (i == mid + 1)
            {
                printf("%d", p[j].pid);
            }
            else
            {
                printf(" ");
            }
        }
    }
    printf("\n");

    for (int i = 0; i < p[n - 1].t_time; i++)
    {
        printf("-");
    }

    printf("\n");
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < (p[j].b_time - 2); i++)
        {
            if (j == 0 && i == 0)
            {
                printf("0");
            }
            else
            {
                printf(" ");
            }
        }
        printf("%2d", p[j].t_time);
    }
}
float AverageT_Time(struct process *p)
{
    float AverageTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        AverageTurnAroundTime += p[i].t_time;
    }
    return AverageTurnAroundTime / n;
}
float AverageW_Time(struct process *p)
{
    float AverageWaitTime = 0;
    for (int i = 0; i < n; i++)
    {
        AverageWaitTime += p[i].w_time;
    }
    return AverageWaitTime / n;
}
void BubbleSort(struct process *p)
{
    for (int j=0; j < n-1; j++)
	{
    	for(int i = 0; i < n-j-1; ++i) 
		{
      		if(p[i].b_time> p[i+1].b_time)
			{
		        struct process temp = p[i];
                p[i] = p[i+1];
                p[i+1] = temp;
      		}
    	}
  	}
	
}
void BubbleSort_P(struct process *p)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].priority > p[j + 1].priority)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void BubbleSort_T(struct process *p)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].t_time > p[j + 1].t_time)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void FCFS(struct process *p)
{
    p[0].w_time = 0;

    for (int i = 1; i < n; i++)
    { // calculate wait time
        calculate_WaitTime(&p[i], i, p);
    }
    for (int i = 0; i < n; i++)
    { // calculate TurnAround time
        calculate_TurnAroundTime(&p[i], i, p);
    }
    float AverageWaitTime = AverageT_Time(p);
    float AverageTurnAroundTime = AverageW_Time(p);
    // Print Table

    Display_Table(p);

    printf("\n\nAverage Wait Time: %.2f\n", AverageWaitTime);
    printf("Average Turn Around Time: %.2f\n", AverageTurnAroundTime);

    // Gand Chart
    Grantt_Chart(p);
}
void SJF(struct process *p)
{

    BubbleSort(p); // appply sort on the bases of brust time
    FCFS(p);       // now applay FCFS
}
void PRIORITY(struct process *p)
{
    BubbleSort_P(p);

    p[0].w_time = 0;

    for (int i = 1; i < n; i++)
    { // calculate wait time
        calculate_WaitTime(&p[i], i, p);
    }
    for (int i = 0; i < n; i++)
    { // calculate TurnAround time
        calculate_TurnAroundTime(&p[i], i, p);
    }
    float AverageWaitTime = AverageT_Time(p);
    float AverageTurnAroundTime = AverageW_Time(p);
    // Print Table

    Display_Table_P(p);

    printf("\n\nAverage Wait Time: %.2f\n", AverageWaitTime);
    printf("Average Turn Around Time: %.2f\n", AverageTurnAroundTime);

    // Gand Chart
    Grantt_Chart(p);
}
void Grantt_Chart_Robin(struct process *p,struct Robbin *A,int size,int q){
    for (int i = 0; i < A[size-1].turn; i++)
    {
        printf("-");
    }
    printf("\n");

    for (int j = 0; j < size ; j++)
    {
        for (int i = 0; i < (A[j].brust); i++)
        {
            int mid = (A[j].brust / 2) - 1; // as we start from 0 so mid is 4/2 = 2 - 1 = 1 etc;
            if (i == A[j].brust - 1 || (i == 0 && j == 0))
            {
                printf("|");
            }
            else if (j == n - 1 && i == (A[j].brust - 1))
            {
                printf("|");
            }
            else if (i == mid)
            {
                printf("p");
            }
            else if (i == mid + 1)
            {
                printf("%d", A[j].id);
            }
            else
            {
                printf(" ");
            }
        }
    }
    printf("\n");

    for (int i = 0; i <  A[size-1].turn; i++)
    {
        printf("-");
    }

    printf("\n");
    for (int j = 0; j < size ; j++)
    {
        for (int i = 0; i < (A[j].brust - 2); i++)
        {
            if (j == 0 && i == 0)
            {
                printf("0");
            }
            else
            {
                printf(" ");
            }
        }
        printf("%2d", A[j].turn);
    }

}
void RoundRobbin(struct process *p,int Quantum)
{
    // calculate Rounds
    for (int i = 0; i < n; i++)
    {
        if (p[i].b_time % Quantum == 0)
        {
            p[i].rounds = p[i].b_time / Quantum;
        }
        else
        {
            p[i].rounds = p[i].b_time / Quantum + 1;
        }
        TotalRounds += p[i].rounds;
    }
    struct Robbin *A = (struct Robbin *)malloc(sizeof(struct Robbin)*TotalRounds); 
    for(int i = 0;i<TotalRounds;i++){
        A[i].turn = 0;
        A[i].wait = 0;
        A[i].id = 0;
        A[i].brust = 0;
    }
    for (int i = 0; i < n; i++)
    {
        p[i].Rem_B_Time = p[i].b_time;
    }
    p[0].w_time = 0;
    int count = 0,i,x = 0,sub = 0; 
    while (1)
    {

        for (i = 0; i < n; i++)
        {
            // we need an iterator for the process structure here
            if (p[i].Rem_B_Time >= Quantum)
            {
                A[x+1].wait = A[x].wait +Quantum;
                A[x].turn = A[x].wait + Quantum;
                p[i].Rem_B_Time -= Quantum;
                p[i].w_time = A[x].wait;
                A[x].id = p[i].pid;
                A[x].brust = Quantum;
                if (p[i].rounds == 1)
                {
                    count++;      // 1 process has completed its rounds
                }
                if(i==0){
                    sub = Quantum;
                }
                if(count == n-1 || count == n){
                    sub = 0;
                    A[x+1].wait = A[x].wait;
                    A[x].turn = A[x-1].turn + Quantum;
                }
            }
            else if (p[i].Rem_B_Time != 0)
            {
                A[x+1].wait = A[x].wait + p[i].Rem_B_Time;
                A[x].turn = A[x].wait + p[i].Rem_B_Time;
                A[x].brust = p[i].Rem_B_Time;
                if(i==0){
                    sub = p[i].Rem_B_Time;
                }
                if(count == n-1 || count == n){  // no increment for the last process
                    sub = 0;
                    A[x+1].wait = A[x].wait;
                    A[x].turn = A[x-1].turn + Quantum;
                }
                p[i].Rem_B_Time = 0;
                p[i].w_time = A[x].wait;
                A[x].id = p[i].pid;
                count++;      // 1 process has completed its rounds
            }
            else
            {
                continue;
            }
            p[i].rounds--;
            x++;
        }
        if( count == n)
        {
            break;
        }
        A[x].wait -= sub;   //  subtract the wait time for the first process every time
    }
    for(int i = 0; i <x;i++){
        printf("%d ",A[i].id);
        printf("%d ",A[i].wait);
        printf("%d\t",A[i].turn);
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    { // calculate TurnAround time
        calculate_TurnAroundTime(&p[i], i, p);
    }
    float AverageWaitTime = AverageW_Time(p);
    float AverageTurnAroundTime = AverageT_Time(p);
    // BubbleSort_T(p);
    Display_Table(p);
    printf("\n\nAverage Wait Time: %.2f\n", AverageWaitTime);
    printf("Average Turn Around Time: %.2f\n", AverageTurnAroundTime);

    // Gand Chart
    Grantt_Chart_Robin(p,A,x,Quantum);
}
int main()
{
    printf("Enter The Number Of processes You want to create :");
    scanf("%d", &n);
    struct process *p = (struct process *)malloc(sizeof(struct process) * n);
    for (int i = 0; i < n; i++)
    { // giving pid to each process
        p[i].pid = i + 1;
        p[i].b_time = 0;
        p[i].w_time = 0;
        p[i].t_time = 0;
        p[i].priority = 0;
        p[i].rounds = 0;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Enter The Brust Time of the Process P[%d] :", p[i].pid);
        scanf("%d", &p[i].b_time);
        printf("Enter The Priority of the Process P[%d] :", p[i].pid);
        scanf("%d", &p[i].priority);
        printf("\n");
    }

    int Quantum = 0;
    printf("Enter the Quantum value :");
    scanf("%d", &Quantum);
    printf("\n\tFirst Come First Serve\n");
    FCFS(p);
    printf("\n");
    printf("\n\tShortest Job First\n");
    SJF(p);
    printf("\n");
    printf("\n\tPriority Scheduling\n");
    PRIORITY(p);
    printf("\n");
    printf("\n\tRound Robin\n");
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].pid > p[j + 1].pid)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    RoundRobbin(p,Quantum);
    return 0;
}