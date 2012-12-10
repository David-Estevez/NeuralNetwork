#ifndef TERMINALINTERFACE_H
#define TERMINALINTERFACE_H

#include <iostream>
#include <string>

class TerminalInterface
{
public:
    TerminalInterface();
    TerminalInterface(const std::string title);

    void setTitle(const std::string newTitle );

    virtual void show();

private:
    std::string menuTitle;

protected:
    //-- ANSI terminal escape sequences:
    static const std::string CLEAR_SCREEN;
    static const std::string HOME_SCREEN;
    static const std::string RESET_FORMAT;
    static const std::string BOLD;
    static const std::string HIGHLIGHT;
    static const std::string PURPLE;

};

#endif // TERMINALINTERFACE_H
