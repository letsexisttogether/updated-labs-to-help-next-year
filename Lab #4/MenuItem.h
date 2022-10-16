#pragma once

#include <iostream>

class MenuItem
{
private:
    typedef void (*Action) ();

private:
    int16_t m_Index{};
    const char* m_Name{};
    Action m_Action{};

public:
    MenuItem() = delete;
    explicit MenuItem(const MenuItem&) = delete;
    explicit MenuItem(MenuItem&&) = delete;
    MenuItem(int16_t index, const char* name, Action action)
        : m_Index(index), m_Name(name), m_Action(action)
    {}

    void Invoke()
    {
        m_Action();
    }

    friend std::ostream& operator << (std::ostream& writeStream, const MenuItem& thisObj)
    {
        writeStream << thisObj.m_Index << ". " << thisObj.m_Name;
        return writeStream;
    }
};

