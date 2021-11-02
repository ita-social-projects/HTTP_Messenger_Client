#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <QString>
#include <stdio.h>

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
    static void DeleteFile();

private:
    static bool FileExists(const std::string& filename);
};

#endif
