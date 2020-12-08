#include <iostream>
#include <string>
#incldue <vector>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

#define DISKSIZELIMIT 10000.0f

// Search Path
// Delete the first directory in the path if it exceeds a certain capacity
bool SearchPathAndCalculationDiskSize(string strPath, vector<string>& VecstrDirName);

void main(void){
    float fTotalFileSize = 0.0f;
    vector<string> VecstrDirName;
    VecstrDirName.clear();

    if(SearchPathAndCalculationDiskSize("SavePath", VecstrDirName)){
        if(fTotalFileSize >= DISKSIZELIMIT){
            string strCommand = "rm -rf";
            strCommand += VecstrDirName.front();
            system(strCommend.c_str());
        }
    }
}

bool SearchPathAndCalculationDiskSize(string strPath, vector<string>& VecstrDirName){
    struct stat statinfo;
    memset(&statinfo, 0, sizeof(statinfo));
    lstat(strPath.c_str(), &statinfo);
    
    if(!S_ISDIR(statinfo.st_mode))
        return false;

    DIR * dir;
    struct dirent * entry;

    if((dir = opendir(strPath.c_str())) == NULL)
        return false;

    while((entry = readdir(dir)) != NULL){
        memset(&statinfo, 0, sizeof(statinfo));
        string strFilePath = strPath + "/" + entry->d_name;
        while(strFilePath.find("//") != string::npos)
            strFilePath.replace(strFilePath.find("//"), 2, "/");

        lstat(strFilePath.c_str(), &statinfo);

        if(S_ISDIR(statinfo.st_mode)){
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

                VecstrDirName.push_back(strFilePath);
                fTotalFileSize = fTotalFileSize + ((statinfo.st_size / 1024.0f) / 1024.0f);

                string strSubDir = strPath + "/" + entry->d_name;
                SearchPathAndCalculationDiskSize(strSubDir, VecstrDirName);
            }
            else
                fTotalFileSize = fTotalFileSize + ((statinfo.st_size / 1024.0f) / 1024.0f);
        }
    }

    closedir(dir);
    return true;
}