#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <list>
#include <map>
#include <iterator>
#include <string>
#include <memory.h>

using namespace std;

typedef map<string, bool> FILE_LIST;

int nTotalFileSize = 0;

bool SearchPath(string strDir, FILE_LIST& list){
	struct stat statinfo;
	memset(&statinfo, 0, sizeof(statinfo));
	lstat(strDir.c_str(), &statinfo);
	if(!S_ISDIR(statinfo.st_mode)){
		cout << strDir + " is no Directory" << endl;
		return false;
	}

	DIR * dir;
	struct dirent * entry;
	
	if((dir = opendir(strDir.c_str())) == NULL){
		cout << strDir + "open error" << endl;
		return false;
	}

	while((entry = readdir(dir)) != NULL){
		memset(&statinfo, 0, sizeof(statinfo));
		string strFilePath = strDir + "/" + entry->d_name;
		while(strFilePath.find("//") != string::npos)
			strFilePath.replace(strFilePath.find("//"), 2, "/");

		lstat(strFilePath.c_str(), &statinfo);

		if(S_ISDIR(statinfo.st_mode)){
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			list.insert(pair<string, bool>(strFilePath, true));

			cout << "Directory : " << strFilePath << endl;
			cout << "Directory Size : " << statinfo.st_size << endl;
			nTotalFileSize += 4096;

			string strSubDir = strDir + "/" + entry->d_name;
			SearchPath(strSubDir, list);
		}
		else{
			list.insert(pair<string, bool>(strFilePath, false));
			
			cout << "File : " << strFilePath << endl;
			cout << "File Size : " << statinfo.st_size << endl;
			nTotalFileSize += statinfo.st_size;
		}
	}

	closedir(dir);

	return true;
}

int main(int argc, char * argv[]){
	string strSrcDir = argv[1];
	FILE_LIST file_list;
	SearchPath(strSrcDir, file_list);
	cout << "Total Size : " << nTotalFileSize << endl;
	return 0; 
}

