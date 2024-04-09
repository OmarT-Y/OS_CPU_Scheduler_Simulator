#include "Definitions.h"
using namespace std;
vector<Process> Job_Q;
int Process::number_of_tasks_created = 0;
bool Scheduler::Check_new_processes()
{

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

}
double Scheduler::get_avg_turnaround()
{

}
double Scheduler::get_avg_waiting_time()
{

}