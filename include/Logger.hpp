#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Logger
{
    enum class Color
    {
#ifdef _WIN32
        RED   = 4,
        GREEN = 2,
        WHITE = 15
#else
        RED = 31,
        GREEN = 32,
        WHITE = 0
#endif
    };

    static void setConsoleFontColor(Color color)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(color));
#else
        std::cout << "\033[" << static_cast<int>(color) << "m";
#endif
    }

    template <typename T>
    void printInfo(T message)
    {
        std::cout << message << std::endl;
    }

    template <typename T>
    void printError(T message)
    {
        setConsoleFontColor(Color::RED);
        std::cout << message << std::endl;
        setConsoleFontColor(Color::WHITE);
    }

    template <typename T>
    void printValue(std::string message, T value)
    {
        std::cout << message << ": " << value << std::endl;
    }
}

#endif