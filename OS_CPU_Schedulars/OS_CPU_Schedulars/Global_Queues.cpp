#include <vector>
#include "Definitions.h"
using namespace std;
Process* Running_task;
vector<Process*> Ready_Q;
vector<Process*> Blocked_Q;
vector<Process> Job_Q;
vector<int> turnaround;
vector<int> wait_time;