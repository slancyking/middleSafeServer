#pragma once

#include <string> 
#include <list>
#include <io.h>
using namespace std;

class FileHelp
{
	
 
public:

	struct fileInfo
	{
		string path;
		_finddata_t data;
		fileInfo(string path, _finddata_t data) {
			this->path = path;
			this->data = data;
		}
	};

	typedef list<fileInfo> _fileInfoList;

	FileHelp(string f);
    static list<fileInfo> enumFile(string dir);
	static list<fileInfo> findFile(string dir, string pattern);
	 

private:
	string _f;
	_fileInfoList fileList;

};

