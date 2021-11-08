#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <QString>
#include <QByteArray>
#include <stdio.h>
#include <direct.h>

#ifdef _WIN32
#define USER_HOME_DIR "USERPROFILE"
#else
#define USER_HOME_DIR "HOME"
#endif

class Cache
{
public:
    Cache(const std::string& filename);
    static void CreateIfNotExists(QString UserName);
    static std::string GetCachePath();
    static QString OpenByCache();
    static void DeleteCacheFile();
    static void WriteUserImg();
    static void ReadUserImg();

private:
    static bool FileExists(const std::string& filename);
};

#endif
