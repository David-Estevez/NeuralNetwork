#ifndef TERMINALMENU_H
#define TERMINALMENU_H

#include "terminalinterface.h"

#include <iostream>
#include <vector>
#include <string>


class TerminalMenu : public TerminalInterface
{
public:
    TerminalMenu();
    TerminalMenu(const std::string title);

    void addOption(const std::string newOption);
    void setCurrent(const int num);

    void show();

private:
    std::vector<std::string> options;

    int numOptions;
    int currentOption;

};

#endif // TERMINALMENU_H
