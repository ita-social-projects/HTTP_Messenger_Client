#include "cache.h"
#include "Logger.h"
#include "loginwindow.h"
#include "currentUser.h"

Cache::Cache(const std::string& filename)
{
    const char* home_dir = std::getenv(USER_HOME_DIR);
    
        if (home_dir == nullptr)
        {
            LOG_ERROR("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
            throw std::runtime_error("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
        }
    
}

std::string Cache::GetCachePath()
{
    const char* HomeDirectory = std::getenv(USER_HOME_DIR);

        if ( HomeDirectory == nullptr)
        {
            LOG_ERROR("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
            throw std::runtime_error("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
        }
        else
        {
        return std::string( HomeDirectory) + "\\Cache.txt";
        }
}

QString Cache::OpenByCache(){
    std::string UserName;
    std::string UserToken;
    if(FileExists(GetCachePath())){
        std::ifstream cache_file(GetCachePath(), std::ios::in );
         cache_file>>UserName>>UserToken;
         CurrentUser::getInstance()->setLogin(QString::fromStdString(UserName));
         CurrentUser::getInstance()->setToken((QString::fromStdString(UserToken)));
         return QString::fromStdString(UserName);
    }
    else
    {
        return "";
    }
}

void Cache::CreateIfNotExists(QString UserName)
{
    if (FileExists(GetCachePath()))
	{
        LOG_ERROR("File exists");
        return;
	}

    std::ofstream cache_file(GetCachePath(), std::ios::out | std::ios::trunc);

    if (cache_file.is_open())
	{
        LOG_DEBUG("File is opened");
        cache_file << UserName.toStdString()<<"\n";
        cache_file << CurrentUser::getInstance()->getToken().toStdString();
        cache_file.close();
	}
	else
	{
        LOG_ERROR("Cannot open file \\ Cache.txt \\ for writing");
        throw std::runtime_error("Cannot open file \\ Cache.txt \\ for writing");
	}
}

bool Cache::FileExists(const std::string &filename)
{
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void Cache::DeleteFile()
{
    char* FilePath = new char[GetCachePath().length()+1];
    std::strcpy(FilePath,GetCachePath().c_str());

    if (FileExists(GetCachePath())==false)
    {
        return;
    }
    else
    {
        if(remove(FilePath) != 0 )
        {
            LOG_ERROR("Error deleting file");

        }
        else
        {
             LOG_DEBUG("File deleted");
        }
    }
    delete FilePath;
}
