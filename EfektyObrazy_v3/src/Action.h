#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action
{
    friend class MainWindow;
public:
    Action(): m_name{"NULL"} {};
    Action(std::string & name): m_name{name} {};
    virtual ~Action() = default;

protected:
    std::string m_name;
};

#endif // ACTION_H
