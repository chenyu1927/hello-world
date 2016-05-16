#include "ConfigFileReader.h"
#include <stdio.h>
#include <sstream>
#include <string.h>

ConfigFileReader::ConfigFileReader(const char *filename)
	: m_load_ok(false)
{
	_LoadFile(filename);
}

ConfigFileReader::~ConfigFileReader()
{

}

void ConfigFileReader::_LoadFile(const char* filename)
{
	m_config_file.clear();
	m_config_file.append(filename);

	FILE *fp = ::fopen(filename, "r");
	if (0 == fp)
	{
		//error
		return ;
	}

	char buff[256] = {0};
//	int n = fread(buff, sizeof (char), 255, fp);
	while (true)
	{
		bzero(buff, sizeof (buff));
		char *p = fgets(buff, 256, fp); // readline or eof
		if (p == 0)
			break ;
		
		size_t len = strlen(buff);
		if (buff[len-1] == '\n')
			buff[len-1] = '\0';
		
		p = strchr(buff, '#');
		if (0 != p)
		{
			*p = '\0';
		}

		if (strlen(buff) == 0)
			continue ;

		_PairseLine(buff);
		
	}

	fclose(fp);
	m_load_ok = true;
}

void ConfigFileReader::_PairseLine(char *line)
{
	char *p = strchr(line, ':');
	if (p == 0)
		return ;

	*p = 0;
	char *key = _TrimSpace(line);
	char *value = _TrimSpace(p+1);

	if (key && value)
	{
		m_config_map.insert(std::make_pair(key, value));
	}
}

char *ConfigFileReader::_TrimSpace(char *str)
{
	char *start_pos = str;
	while (*start_pos == ' ' || *start_pos == '\t')
		++ start_pos;

	if (strlen(start_pos) == 0)
		return 0;

	char *end_pos = start_pos + strlen(start_pos) - 1;
	while (*end_pos == ' ' || *end_pos == '\t')
	{
		*end_pos = 0;
		-- end_pos;
	}

	int len = (int)(end_pos - start_pos) + 1;
	if (len <= 0)
		return 0;

	return start_pos;
}

int ConfigFileReader::_WriteFile()
{
	FILE *fp = fopen(m_config_file.c_str(), "w+");
	if (fp == 0)
		return -1;

//	char buff[256] = {0};
	map<string, string>::iterator iter = m_config_map.begin();
	for (; iter != m_config_map.end(); ++ iter)
	{
//		bzero(buff, sizeof (buff));
		std::stringstream ss;
		ss << iter->first << ':' << iter->second << '\n';
		fputs(ss.str().c_str(), fp);
	}

	fclose(fp);
	return 0;
}

int ConfigFileReader::SetConfigValue(const char* name, const char* value)
{
	if (!m_load_ok)
		return -1;

	m_config_map[name] = value;

	return _WriteFile();
}

const char* ConfigFileReader::GetConfigName(const char* name)
{
	if (!m_load_ok)
		return 0;

	map<string, string>::iterator iter = m_config_map.find(name);
	if (iter != m_config_map.end())
		return iter->second.c_str();
	else
		return 0;
}

