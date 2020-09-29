#include <iostream>
#include <io.h>
#include <vector>
#include <fstream>

class ListFiles
{
private:
    enum
    {
        SIZE_SUFFIX = 20 //Maximum suffix size
    };
    char *m_dirPath;                         //Directory path
    char *m_suffix;                          //File suffix
    char *m_fullDirPath;                     //File full path
    std::vector<std::string> m_listFiles;    //List of storage file paths
    void buildDirPath(const char *_dirPath); //Build directory path
    void buildSuffix(const char *_fileType); //Build suffix path
    void buildFullPath();                    //Build full file path

public:
    // contructor
    ListFiles(const char *_dirPath, const char *_fileType = "*");

    // destructor
    virtual ~ListFiles();

    // others methodes
    void setPath(const char *_dirPath);      //set new path
    void setFileType(const char *_fileType); //set new search filetype
    bool getListFiles();                     //get a list of file paths

    // overload operator methods

    // overload operator friends
    friend std::ostream &operator<<(std::ostream &_os, const ListFiles &_lf);
};

void ListFiles::buildDirPath(const char *_dirPath)
{
    m_dirPath = new char[strlen(_dirPath) + 1];
    strcpy_s(m_dirPath, strlen(_dirPath) + 1, _dirPath);
}

void ListFiles::buildSuffix(const char *_fileType)
{
    char tmpSu[] = "\\*.";
    m_suffix = new char[SIZE_SUFFIX];
    strcpy_s(m_suffix, SIZE_SUFFIX, tmpSu);
    strcat_s(m_suffix, SIZE_SUFFIX, _fileType);
}

void ListFiles::buildFullPath()
{
    m_fullDirPath = new char[strlen(m_dirPath) + SIZE_SUFFIX];
    strcpy_s(m_fullDirPath, strlen(m_dirPath) + 1, m_dirPath);
    strcat_s(m_fullDirPath, strlen(m_dirPath) + SIZE_SUFFIX, m_suffix);
}

ListFiles::ListFiles(const char *_dirPath, const char *_fileType)
{
    buildDirPath(_dirPath);
    buildSuffix(_fileType);
    buildFullPath();
}

ListFiles::~ListFiles()
{
    delete m_dirPath;
    delete m_suffix;
    delete m_fullDirPath;
    m_listFiles.clear();
}

void ListFiles::setPath(const char *_dirPath)
{
    delete m_dirPath;
    buildDirPath(_dirPath);
    buildFullPath();
}

void ListFiles::setFileType(const char *_fileType)
{
    delete m_suffix;
    buildSuffix(_fileType);
    buildFullPath();
}

bool ListFiles::getListFiles()
{
    intptr_t handle;
    _finddata_t findData;
    handle = _findfirst(m_fullDirPath, &findData);
    std::string sdirPath = m_dirPath;
    sdirPath.append("\\");
    if (handle == -1)
    {
        std::cout << "Failed to find file, this folder is empty! ";
        _findclose(handle);
        return false;
    }
    do
    {
        std::string tmp = sdirPath + findData.name;
        m_listFiles.push_back(tmp);
    } while (_findnext(handle, &findData) == 0);
    _findclose(handle);
    return true;
}

std::ostream &operator<<(std::ostream &_os, const ListFiles &_lf)
{
    for (int i = 0; i < _lf.m_listFiles.size(); ++i)
    {
        _os << _lf.m_listFiles[i] << std::endl;
    }
    return _os;
}
