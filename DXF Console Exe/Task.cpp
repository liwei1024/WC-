#include "pch.h"
#include "Task.h"
#include "utils.h"

using namespace std;


Task::Task()
{
}


Task::~Task()
{
}

TaskInfo Task::TraverseAllTaskInfo()
{
	TaskInfo _TaskInfo;
	_TaskInfo.start_address = _Process.ReadOfset(__任务基址, { 104 });
	_TaskInfo.end_address = _Process.ReadOfset(__任务基址, { 108 });
	_TaskInfo.task_count = (_TaskInfo.end_address - _TaskInfo.start_address) / 4;
	return _TaskInfo;
}

TaskInfo Task::TraverseReceivedTaskInfo()
{
	TaskInfo _TaskInfo;
	_TaskInfo.start_address = _Process.ReadOfset(__任务基址, { 8 });
	_TaskInfo.end_address = _Process.ReadOfset(__任务基址, { 12 });
	_TaskInfo.task_count = (_TaskInfo.end_address - _TaskInfo.start_address) / 12;
	return _TaskInfo;
}

TaskObject Task::TraverseTaskObject(DWORD ObjectPointer)
{
	TaskObject _TaskObject;
	if (ObjectPointer != 0)
	{
		_TaskObject.address = ObjectPointer;
		_TaskObject.task_id = _Process.ReadInteger(ObjectPointer);
		_TaskObject.type = _Process.ReadInteger(ObjectPointer + 308);
		_TaskObject.copy_id = _Process.ReadInteger(_Process.ReadInteger(ObjectPointer + 0x2B8));
		_TaskObject.materials = _Process.ReadInteger(ObjectPointer + 1428); //材料
		_TaskObject.task_length = _Process.ReadInteger(ObjectPointer + 28);
		_TaskObject.condition_type = _Process.ReadString(_Process.ReadInteger(ObjectPointer + 720), 100);
		if (_TaskObject.task_length > 7)
		{
			_TaskObject.name = _Process.ReadString(_Process.ReadInteger(ObjectPointer + 8), 100);
		}
		else {

			_TaskObject.name = _Process.ReadString(ObjectPointer + 8, 100);
		}
	}

	return _TaskObject;
}

VOID Task::OutputTaskInfo(int task_type)
{
	TaskInfo _TaskInfo;
	TaskObject _TaskObject;
	string str;
	if (task_type == -1)
	{
		粉色打印("遍历所有任务");
		_TaskInfo = TraverseAllTaskInfo();
	}
	else if (task_type == 0) {
		粉色打印("遍历已接任务");
		_TaskInfo = TraverseReceivedTaskInfo();
	}
	粉色打印("task_count %d", _TaskInfo.task_count);
	str += "=================================================================================================================================\n";
	for (size_t i = 0; i < _TaskInfo.task_count; i++)
	{
		_TaskObject = TraverseTaskObject(_Process.ReadInteger(_TaskInfo.start_address + i * 4));
		str += "地址:" + FormatString("0x%x", _TaskObject.address);
		str += " | 任务ID:" + FormatString("%d", _TaskObject.task_id);
		str += " | 类型:" + FormatString("%d", _TaskObject.type);
		str += " | 副本ID:" + FormatString("%d", _TaskObject.copy_id);
		str += " | 材料:" + FormatString("%d", _TaskObject.materials);
		str += " | 长度:" + FormatString("%d", _TaskObject.task_length);
		str += " | 任务条件:" + FormatString("%s", _TaskObject.condition_type);
		str += " | 标题:" + FormatString("%s", _TaskObject.name);
		青色打印("%s", str.c_str());
		str.clear();
	}
}