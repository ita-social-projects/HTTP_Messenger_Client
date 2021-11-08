#include "cache.h"
#include "Logger.h"
#include "loginwindow.h"


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

QString Cache::OpenByCache()
{
    std::string UserName;
    std::string UserToken;
    std::string serverURL;

    if(FileExists(GetCachePath()))
    {
        ReadUserImg();
        std::ifstream cache_file(GetCachePath(), std::ios::in );
        cache_file>>UserName>>UserToken>>serverURL;
        CurrentUser::getInstance()->setLogin(QString::fromStdString(UserName));
        CurrentUser::getInstance()->setToken((QString::fromStdString(UserToken)));
        RequestManager::GetInstance()->setServerURL(QString::fromStdString(serverURL));
        return QString::fromStdString(UserName);
    }
    else
    {
        return "";
    }
}

void Cache::ReadUserImg()
{
    const char* home_dir = std::getenv(USER_HOME_DIR);

    if (home_dir == nullptr)
    {
        LOG_ERROR("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
        throw std::runtime_error("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
    }
    std::string ImgPath = std::string(home_dir) + "\\UserImg.png";
    QPixmap PixMapImg;
    if(FileExists(ImgPath)){
        PixMapImg.load(QString::fromStdString(ImgPath));
        CurrentUser::getInstance()->setImage(PixMapImg);
    }
    else
    {
        WriteUserImg();
    }
}

void Cache::WriteUserImg()
{
    const char* home_dir = std::getenv(USER_HOME_DIR);

    if (home_dir == nullptr)
    {
        LOG_ERROR("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
        throw std::runtime_error("The environment variable \"" + std::string(USER_HOME_DIR) + "\" not set");
    }

    std::string path = std::string( home_dir) + "\\UserImg.png";
    QFile PictureFile(QString::fromStdString(path));
    QPixmap PixMapImg = CurrentUser::getInstance()->getImage();
    PixMapImg.save(&PictureFile,"PNG");
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
        WriteUserImg();
        cache_file << UserName.toStdString() << "\n";
        cache_file << CurrentUser::getInstance()->getToken().toStdString() << "\n";
        cache_file << RequestManager::GetInstance()->getServerURL().toString().toStdString();

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

void Cache::DeleteCacheFile()
{
    char* FilePath = new char[GetCachePath().length()+1];
    std::strcpy(FilePath,GetCachePath().c_str());

    if (FileExists(GetCachePath())==false)
    {
        delete[] FilePath;
        return;
    }
    else
    {
        if(remove(FilePath) != 0)
        {
            LOG_ERROR("Error deleting file");
        }
        else
        {
             LOG_DEBUG("File deleted");
        }
    }
    delete[] FilePath;
}
