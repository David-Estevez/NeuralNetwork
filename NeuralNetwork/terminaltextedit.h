#ifndef TERMINALTEXTEDIT_H
#define TERMINALTEXTEDIT_H

#include "terminalinterface.h"

#include <iostream>
#include <string>


class TerminalTextEdit: public TerminalInterface
{
public:
    TerminalTextEdit( const std::string title);
    TerminalTextEdit( const std::string title, std::string& textToEdit);

    void setTextToEdit( std::string& textToEdit);
    int show();

private:
    std::string * textToEdit;
};

#endif // TERMINALTEXTEDIT_H
