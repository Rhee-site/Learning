void CheckSavePathDiskSize(const string strSavePath){
    CFileFind find;
    CString cstrPath(strSavePath.c_str());
    CString cstrFileType = "*.*";
    CString cstrFileName;
    CString cstrPathName;

    int nResult = 1;
    unsigned int nFileCount = 0;
    unsigned int nFileSize = 0;
    unsigned int nTotalFileSize = 0;

    cstrPath += cstrFileType;
    find.FindFile((LPCTSTR)cstrPath);

    while(nResult){
        cstrFileName = find.GetFileName();
        cstrPathName = find.GetFilePath();
        nFileSize = find.GetLength();

        if(cstrFileName.IsEmpty()){
            if(nResult){
                if(!find.IsDirectory()){
                    // This is nFileSize
                    nFileCount+=;
                    nTotalFileSize += nFileSize;
                }
                else{
                    // This is Directory
                }
            }
        }
        nResult = find.FindNextFile();
    }

    cout << "File Count : " << nFileCount << endl;
    cout << "Total File Size : " << nTotalFileSize << endl;
}