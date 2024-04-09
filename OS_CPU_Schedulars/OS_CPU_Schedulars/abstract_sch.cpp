#include "definitions_sch.h"
using namespace std;
vector<Process> Job_Q;
int Process::number_of_tasks_created = 0;
bool Scheduler::Check_new_processes(int sys_time)
{
	return false;
}
int Scheduler::get_turnaround(Process* p,int System_time)
{
	return System_time - (p->ariv_time);
}
int Scheduler::get_waiting_time(Process* p,int System_time)
{
	return System_time - (p->ariv_time) - (p->burst_time);
}
bool Scheduler::check_blocked(int sys_time)
{
	bool added = false;
	for (int i = 0; i < Blocked_Q.size(); i++)
	{
		if (Blocked_Q[i]->ariv_time >= sys_time)
		{
			Ready_Q.push_back(Blocked_Q[i]);
			added = true;
		}
	}
	return added;
}
double Scheduler::get_avg_turnaround()
{
	double avg_turnaround = 0;
	for (int i = 0; i < turnaround.size(); i++)
	{
		avg_turnaround += turnaround[i];
	}

	avg_turnaround = avg_turnaround / turnaround.size();

	return avg_turnaround;
}
double Scheduler::get_avg_waiting_time()
{
	double avg_waiting_time = 0;
	for (int i = 0; i < wait_time.size(); i++)
	{
		avg_waiting_time += wait_time[i];
	}

	avg_waiting_time = avg_waiting_time / wait_time.size();

	return avg_waiting_time;
}
