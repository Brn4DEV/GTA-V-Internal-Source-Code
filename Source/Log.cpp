#include "stdafx.h"

vec_str		CLog::m_msg;
vec_str		CLog::m_error;
vec_str		CLog::m_fatal;

std::string	CLog::m_szFile;

void getTime(char* out)
{
	time_t	t;
	tm		tInfo;
	time(&t);
	localtime_s(&tInfo, &t);
	strftime(out, 32, "[%H:%M:%S]", &tInfo);
	return;
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
void addTime(std::string& str)
{
	char time[32];
	getTime(time);
	str.insert(0, time);
	return;
}

std::ofstream m_Console;
std::ifstream m_Input;

std::string	CLog::log(char* format, char* prefix, va_list args)
{
	std::ofstream	file;
	char			msg[2][0xFF] = {};
	char			time[0x20] = {};

	file.open(CLog::m_szFile, std::ios::out | std::ios::app);
	if (!file.is_open())
		return {};

	getTime(time);
	vsprintf_s(msg[0], format, args);
	sprintf_s(msg[1], "%s %s %s", time, prefix, msg[0]);

	file << msg[1] << std::endl;
	m_Console << std::string(msg[1]) << std::endl;
	return std::string(msg[1]);
}

bool	CLog::initialize(std::string szDir, std::string szFile)
{
	if (!AttachConsole(GetCurrentProcessId()))
		AllocConsole();
	SetConsoleTitleW(L"Web Base *_*");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	m_Console.open("CONOUT$");
	m_Input.open("CONIN$");

	char* appdata = nullptr;
	size_t	size = 0;
	if (_dupenv_s(&appdata, &size, "APPDATA") != 0 || appdata == nullptr)
		return false;

	m_szFile = appdata;
	free(appdata);
	m_szFile.append("\\" + szDir);
	DWORD	attr = GetFileAttributesA(&m_szFile[0]);
	if ((attr == 0xFFFFFFFF || !(attr & FILE_ATTRIBUTE_DIRECTORY)) && !CreateDirectoryA(&m_szFile[0], NULL))
		return false;

	m_szFile.append("\\" + szFile);

	return true;
}

void	CLog::Msg(char* msg, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	va_list	args;
	va_start(args, msg);
	m_msg.push_back(log(msg, "[Msg]", args));
	va_end(args);
	return;
}

void	CLog::Hook(char* msg, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	va_list	args;
	va_start(args, msg);
	m_msg.push_back(log(msg, "[Hook]", args));
	va_end(args);
	return;
}
/*

Created 03/09/2017 by WebModdz
YOUTUBE: https://www.youtube.com/channel/UCLz4UNmYGgUMc92ZgclxsuQ

*/
void	CLog::Info(char* msg, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	va_list	args;
	va_start(args, msg);
	m_msg.push_back(log(msg, "[Info]", args));
	va_end(args);
	return;
}

void	CLog::Error(char* error, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	va_list	args;
	va_start(args, error);
	m_error.push_back(log(error, "[Error]", args));
	va_end(args);
	return;
}

void	CLog::Fatal(char* error, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	va_list	args;
	va_start(args, error);
	m_fatal.push_back(log(error, "[Fatal]", args));
	va_end(args);
	return;
}


