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
	_TaskInfo.start_address = _Process.ReadOfset(__�����ַ, { 104 });
	_TaskInfo.end_address = _Process.ReadOfset(__�����ַ, { 108 });
	_TaskInfo.task_count = (_TaskInfo.end_address - _TaskInfo.start_address) / 4;
	return _TaskInfo;
}

TaskInfo Task::TraverseReceivedTaskInfo()
{
	TaskInfo _TaskInfo;
	_TaskInfo.start_address = _Process.ReadOfset(__�����ַ, { 8 });
	_TaskInfo.end_address = _Process.ReadOfset(__�����ַ, { 12 });
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
		_TaskObject.materials = _Process.ReadInteger(ObjectPointer + 1428); //����
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
		��ɫ��ӡ("������������");
		_TaskInfo = TraverseAllTaskInfo();
	}
	else if (task_type == 0) {
		��ɫ��ӡ("�����ѽ�����");
		_TaskInfo = TraverseReceivedTaskInfo();
	}
	��ɫ��ӡ("task_count %d", _TaskInfo.task_count);
	str += "=================================================================================================================================\n";
	for (size_t i = 0; i < _TaskInfo.task_count; i++)
	{
		_TaskObject = TraverseTaskObject(_Process.ReadInteger(_TaskInfo.start_address + i * 4));
		str += "��ַ:" + FormatString("0x%x", _TaskObject.address);
		str += " | ����ID:" + FormatString("%d", _TaskObject.task_id);
		str += " | ����:" + FormatString("%d", _TaskObject.type);
		str += " | ����ID:" + FormatString("%d", _TaskObject.copy_id);
		str += " | ����:" + FormatString("%d", _TaskObject.materials);
		str += " | ����:" + FormatString("%d", _TaskObject.task_length);
		str += " | ��������:" + FormatString("%s", _TaskObject.condition_type);
		str += " | ����:" + FormatString("%s", _TaskObject.name);
		��ɫ��ӡ("%s", str.c_str());
		str.clear();
	}
}