typedef std::vector<std::string> vec_str;

class CLog
{
public:
	static vec_str		m_msg;
	static vec_str		m_error;
	static vec_str		m_fatal;
	static bool	initialize(std::string szDir, std::string szFile);
	static void Msg(char* msg, ...);
	static void Hook(char* msg, ...);
	static void Error(char* error, ...);
	static void	Fatal(char* erro, ...);
	static void	Info(char* erro, ...);

protected:
	static std::string	m_szFile;
	static std::string	log(char*, char*, va_list vars);
};