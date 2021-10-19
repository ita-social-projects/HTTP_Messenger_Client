#pragma once
#include <cstddef>
#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <mutex>
#include <chrono>
#include <thread>
#include <memory>

#include "Log.h"

// if __PRETTY_FUNCTION__ doesnt exist use __FUNCSIG__ instead

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
    #define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define LOG_DEBUG(X)    (Logger::GetInstance())(t_DEBUG,      __FILE__, __PRETTY_FUNCTION__, X)
#define LOG_VERBOSE(X)  (Logger::GetInstance())(t_VERBOSE,    __FILE__, __PRETTY_FUNCTION__, X)
#define LOG_ERROR(X)    (Logger::GetInstance())(t_ERROR,      __FILE__, __PRETTY_FUNCTION__, X)
#define LOG_FATAL(X)    (Logger::GetInstance())(t_FATAL,      __FILE__, __PRETTY_FUNCTION__, X)

#define SET_LOG_LEVEL(X) (Logger::GetInstance()).SetLogLevel(X)
#define SET_LOGS_FILE(X) (Logger::GetInstance()).SetFileForLogs(X)
#define SHOW_LOGS_IN_CONSOLE(X)(Logger::GetInstance()).SetShowInConsole(X)
#define SAVE_LOGS_NOW() (Logger::GetInstance()).SaveLogsToFile()
#define SET_MAX_AMOUNT_OF_LOGS(X) (Logger::GetInstance()).SetMaxAmountOfLogs(X)

#define TIME_FORMAT "%Y-%m-%d_%H-%M"

class Logger{
private:
    std::string m_file_for_saving_logs;
    std::queue<Log> m_all_logs;
    bool show_logs_in_console = false;
    size_t m_max_amount_of_logs = 5;

    // contains the lowest type_of_logs that can be contained in logger
    TYPE_OF_LOG m_level = t_DEBUG;


    std::string GetCurrentTime();

    static std::mutex m_mutex;
    
    Logger();
    Logger(const Logger&);	 
    Logger& operator=(const Logger&);
public:      
   
    ~Logger();   
    void SetLogLevel(TYPE_OF_LOG new_level);
    Logger& operator()( TYPE_OF_LOG type, 
                        std::string file, 
                        std::string function,
                        std::string message);
    static Logger& GetInstance();

    void SetFileForLogs(std::string file_name);
    void SetShowInConsole(bool show);    
    void SaveLogsToFile();
    void SetMaxAmountOfLogs(size_t amount);
};

#endif 
