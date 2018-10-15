#pragma once
class Task
{
public:
	Task();
	~Task();
	TaskInfo TraverseAllTaskInfo();
	TaskInfo TraverseReceivedTaskInfo();
	TaskObject TraverseTaskObject(DWORD ObjectPointer);
	VOID OutputTaskInfo(int task_type);
};

