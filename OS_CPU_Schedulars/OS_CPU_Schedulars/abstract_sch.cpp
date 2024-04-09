#include "definitions_sch.h"
using namespace std;
vector<Process> Job_Q;
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
	return false;
}
double Scheduler::get_avg_turnaround()
{
	return 0;
}
double Scheduler::get_avg_waiting_time()
{
	return 0;
}