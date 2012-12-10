#include "terminalinterface.h"

TerminalInterface::TerminalInterface()
{
}

TerminalInterface::TerminalInterface(const std::string title)
{
    menuTitle = title;
}

void TerminalInterface::setTitle(const std::string newTitle)
{
    menuTitle = newTitle;
}

int TerminalInterface::show()
{
    //-- Clear terminal:
    std::cout << CLEAR_SCREEN;
    std::cout << HOME_SCREEN;
    std::cout << RESET_FORMAT;

    //-- Display menu:
    for (int i = 0; i < 80 ; i++)
	std::cout << '#';

    std::cout << std::endl << PURPLE << BOLD <<  menuTitle << RESET_FORMAT << std::endl;

    for (int i = 0; i < 80 ; i++)
	std::cout << '#';

    std::cout << RESET_FORMAT;

    return 1;
}

//-- ANSI terminal escape sequences:
const std::string TerminalInterface::CLEAR_SCREEN = "\033[2J";
const std::string TerminalInterface::HOME_SCREEN = "\033[0;0H";
const std::string TerminalInterface::RESET_FORMAT = "\033[0m";
const std::string TerminalInterface::BOLD = "\033[1m";
const std::string TerminalInterface::HIGHLIGHT = "\033[7m";
const std::string TerminalInterface::PURPLE = "\033[0;35m";
