#ifndef CONFIGFILEREADER_H_H
#define CONFIGFILEREADER_H_H

#include <map>
#include <string>
#include <boost/noncopyable.hpp>

using std::map;
using std::string;
class ConfigFileReader : boost::noncopyable
{
public:
	ConfigFileReader(const char* filename);
	~ConfigFileReader();

	int   SetConfigValue(const char *key, const char *value);
	const char* GetConfigName(const char *name);
private:
	void _LoadFile(const char* filename);
	void _PairseLine(char *line);
	int	 _WriteFile();
	char* _TrimSpace(char *str);


private:

	bool m_load_ok;
	map<string, string> m_config_map;
	string m_config_file;
};


#endif /* CONFIGFILEREADER_H_H */
