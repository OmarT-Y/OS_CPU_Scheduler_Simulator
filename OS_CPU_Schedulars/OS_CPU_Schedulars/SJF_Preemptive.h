#pragma once
#include "Definitions.h"
class SJF_P_Sch : public Scheduler
{
public:
	int run_Schedular(int System_time, int prev_running_time);
};