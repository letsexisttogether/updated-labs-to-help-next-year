#ifndef MENU_ITEM 
#define MENU_ITEM

#include <iostream>

class MenuItem
{
private:
    using Action = void(*)();

private:
    uint16_t m_Index{};
    char* m_Name{};
    Action m_Action{};

public:
    MenuItem() = delete;
    explicit MenuItem(const MenuItem& extraMenuItem) noexcept
        : m_Index(extraMenuItem.m_Index), m_Name(new char[strlen(extraMenuItem.m_Name)]),
        m_Action(extraMenuItem.m_Action)
    {
        memcpy(m_Name, extraMenuItem.m_Name, strlen(extraMenuItem.m_Name));
    }
    explicit MenuItem(MenuItem&& extraMenuItem) noexcept
        : m_Index(extraMenuItem.m_Index), m_Name(new char[strlen(extraMenuItem.m_Name)]),
        m_Action(extraMenuItem.m_Action)
    {
        memcpy(m_Name, extraMenuItem.m_Name, strlen(extraMenuItem.m_Name));

        extraMenuItem.m_Index = 0;
        extraMenuItem.m_Name = nullptr;
        extraMenuItem.m_Action = nullptr;
    };

    MenuItem(char *name, Action action) noexcept
        : m_Name(name), m_Action(action)
    {}
    MenuItem(uint16_t index, char *name) noexcept
        : m_Index(index), m_Name(name)
    {}
    MenuItem(uint16_t index, char *name, Action action) noexcept
        : m_Index(index), m_Name(name), m_Action(action)
    {}

    ~MenuItem()
    {
        delete[] m_Name;
    }

    void Invoke()
    {
        m_Action();
    }

    uint16_t GetIndex() const noexcept
    {
        return m_Index;
    }
    char* GetName() const noexcept
    {
        return m_Name;
    }
    Action GetAction() const noexcept
    {
        return m_Action;
    }

    
    MenuItem& operator =(const MenuItem&) = delete;
    MenuItem& operator =(const MenuItem&&) = delete;
    friend std::ostream& operator << (std::ostream& writeStream, const MenuItem& thisObj)
    {
        writeStream << thisObj.m_Index << ". " << thisObj.m_Name;
        return writeStream;
    }
};

#endif
