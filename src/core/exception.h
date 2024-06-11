#pragma once

#include <exception>
#include <string>
#include <fstream>
#include <iostream>

class BaseException : public std::exception
{
public:
    explicit BaseException(const std::string &message) : msg_(message) {}
    virtual const char *what() const noexcept override
    {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

class FileNotFoundException : public BaseException
{
public:
    explicit FileNotFoundException(const std::string &message) : BaseException(message) {}
};

class InvalidValueException : public BaseException
{
public:
    explicit InvalidValueException(const std::string &message) : BaseException(message) {}
};

class Logger
{
public:
    static void Log(const std::string &message)
    {
        std::ofstream logFile("../lof/error.log", std::ios_base::app);
        logFile << message << std::endl;
    }

    static void Print(const std::string &message)
    {
        std::cerr << "Error: " << message << std::endl;
    }
};  