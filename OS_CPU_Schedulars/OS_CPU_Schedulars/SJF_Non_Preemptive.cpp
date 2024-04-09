#include "SJF_Non_Preemptive.h"
#include <algorithm>

int SJF_NP_Sch::run_Schedular(int System_time,int prev_running_time)
{
	

	Check_new_processes(System_time);
	
	check_blocked(System_time);
	

	// Sorting Ready queue based on Burst length
	sort(Ready_Q.begin(), Ready_Q.end(), [](const Process* a, const Process* b) {
		if (a->remaining_burst < b->remaining_burst)
		{
			return true;
		}
		else if ((a->remaining_burst == b->remaining_burst) && (a->ariv_time < b->ariv_time))
		{
			return true;
		}
		return false;
		});
	// Sorting Blocked queue based on arrival time 
	sort(Blocked_Q.begin(), Blocked_Q.end(), [](const Process* a, const Process* b) {
		if (a->ariv_time < b->ariv_time)
		{
			return true;
		}
		else if ((a->ariv_time == b->ariv_time) && (a->remaining_burst < b->remaining_burst))
		{
			return true;
		}
		return false;
		});

	
	if (System_time == 0) 
	{
		//Initializing running task with nullptr until it find a Ready process
		Running_task = nullptr;
		
		if (!Ready_Q.empty()) 
		{
			Running_task = Ready_Q[0];
			Running_task->start_time = System_time;
			return Running_task->remaining_burst;
		}
	}
	else if (prev_running_time == expected_last_return)  // Means that current process is done and need to allocate new one
	{
		// Calculating specs of terminated process
		Running_task->remaining_burst = 0;
		turnaround.push_back(Scheduler::get_turnaround(Running_task,System_time));
		wait_time.push_back(get_waiting_time(Running_task,System_time));

		// Erasing terminated process
		int index = -1;
		for (size_t i = 0; i < Ready_Q.size(); ++i) 
		{
			if (Ready_Q[i] == Running_task) 
			{
				index = static_cast<int>(i);
				break;
			}
		}

		if (index != -1) 
		{
			Ready_Q.erase(Ready_Q.begin() + index);
		}
		//*************************   Alocating New Process to CPU   ****************************************************//
		// Sorting Ready queue based on Burst length
		sort(Ready_Q.begin(), Ready_Q.end(), [](const Process* a, const Process* b) {
			if (a->remaining_burst < b->remaining_burst)
			{
				return true;
			}
			else if ((a->remaining_burst == b->remaining_burst) && (a->ariv_time < b->ariv_time))
			{
				return true;
			}
			return false;
			});
		

		//Alocating new Process to CPU
		if (!Ready_Q.empty()) 
		{
			Running_task = Ready_Q[0];
			Running_task->start_time = System_time;
			return Running_task->remaining_burst;
		}
		
	}
	else   // continue execution of current process until it is terminated 
	{
		if (Running_task != nullptr) 
		{
			Running_task->remaining_burst += (expected_last_return - prev_running_time);
			return Running_task->remaining_burst;
		}
		
	}
	// If it is here then it is Idle task
	// Idle task handling
	// Return burst length of idle task if there is still no process ready
	if (!Ready_Q.empty())
	{
		Scheduler::Running_task = Ready_Q[0];
		Scheduler::Running_task->start_time = System_time;
		return Running_task->remaining_burst;
	}
	return Blocked_Q[0]->ariv_time;
}