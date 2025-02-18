

#include "FileHelp.h"
 
#define def_pattern "*.*"


int stringmatchlen(const char* pattern, int patternLen,
    const char* string, int stringLen, int nocase)
{
    while (patternLen) {
        switch (pattern[0]) {
        case '*':
            while (pattern[1] == '*') {
                pattern++;
                patternLen--;
            }
            if (patternLen == 1)
                return 1; /** match */
            while (stringLen) {
                if (stringmatchlen(pattern + 1, patternLen - 1,
                    string, stringLen, nocase))
                    return 1; /** match */
                string++;
                stringLen--;
            }
            return 0; /** no match */
            break;
        case '?':
            if (stringLen == 0)
                return 0; /** no match */
            string++;
            stringLen--;
            break;
        case '[':
        {
            int inot, match;

            pattern++;
            patternLen--;
            inot = pattern[0] == '^';
            if (inot) {
                pattern++;
                patternLen--;
            }
            match = 0;
            while (1) {
                if (pattern[0] == '\\') {
                    pattern++;
                    patternLen--;
                    if (pattern[0] == string[0])
                        match = 1;
                }
                else if (pattern[0] == ']') {
                    break;
                }
                else if (patternLen == 0) {
                    pattern--;
                    patternLen++;
                    break;
                }
                else if (pattern[1] == '-' && patternLen >= 3) {
                    int start = pattern[0];
                    int end = pattern[2];
                    int c = string[0];
                    if (start > end) {
                        int t = start;
                        start = end;
                        end = t;
                    }
                    if (nocase) {
                        start = tolower(start);
                        end = tolower(end);
                        c = tolower(c);
                    }
                    pattern += 2;
                    patternLen -= 2;
                    if (c >= start && c <= end)
                        match = 1;
                }
                else {
                    if (!nocase) {
                        if (pattern[0] == string[0])
                            match = 1;
                    }
                    else {
                        if (tolower((int)pattern[0]) == tolower((int)string[0]))
                            match = 1;
                    }
                }
                pattern++;
                patternLen--;
            }
            if (inot)
                match = !match;
            if (!match)
                return 0; /** no match */
            string++;
            stringLen--;
            break;
        }
        case '\\':
            if (patternLen >= 2) {
                pattern++;
                patternLen--;
            }
            /** fall through */
        default:
            if (!nocase) {
                if (pattern[0] != string[0])
                    return 0; /** no match */
            }
            else {
                if (tolower((int)pattern[0]) != tolower((int)string[0]))
                    return 0; /** no match */
            }
            string++;
            stringLen--;
            break;
        }
        pattern++;
        patternLen--;
        if (stringLen == 0) {
            while (*pattern == '*') {
                pattern++;
                patternLen--;
            }
            break;
        }
    }
    if (patternLen == 0 && stringLen == 0)
        return 1;
    return 0;
}

int stringmatch(const char* pattern, const char* string, int nocase) {
    return stringmatchlen(pattern, strlen(pattern), string, strlen(string), nocase);
}



FileHelp::FileHelp(string f)
{
	this->_f = f;
}

FileHelp::_fileInfoList FileHelp::findFile(string dir, string pattern)
{
	FileHelp::_fileInfoList fList;
	if (dir.back() != '\\') dir += "\\";
	string enumString = dir; 
	enumString += def_pattern;

	intptr_t handle;
	_finddata_t findData;
	handle = _findfirst(enumString.c_str(), &findData);    // 查找目录中的第一个文件
	if (handle == -1)return fList;

	do
	{
		if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
			continue;

		if (strstr(findData.name, "E487B9274756") != 0)
			int ds = 0;


		if (findData.attrib & _A_SUBDIR)    // 是否是子目录
		{
			FileHelp::_fileInfoList subList = findFile(dir + findData.name + "\\", pattern);
			if (subList.size() > 0)
				fList.splice(fList.end(), subList);
		}
		else if (stringmatch(pattern.c_str(), findData.name, true))
			fList.push_back(FileHelp::fileInfo(dir + findData.name, findData));

	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
	 
	return fList;
}

FileHelp::_fileInfoList FileHelp::enumFile(string dir) {
	FileHelp::_fileInfoList fList;
	string enumString = dir;
	if (dir.back() != '\\') return fList;
	enumString += def_pattern;
	
	intptr_t handle;
	_finddata_t findData;
	handle = _findfirst(enumString.c_str(), &findData);    // 查找目录中的第一个文件
	if (handle == -1)return fList; 

	do
	{
		if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
			continue; 
		fList.push_back(FileHelp::fileInfo(dir + findData.name, findData));
		if (findData.attrib & _A_SUBDIR)    // 是否是子目录
		{
			FileHelp::_fileInfoList subList = enumFile(dir + findData.name + "\\");
			if (subList.size() > 0)
				fList.splice(fList.end(), subList); 
		} 
		
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	return fList;
}
