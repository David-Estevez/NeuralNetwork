#include "terminaltextedit.h"

TerminalTextEdit::TerminalTextEdit(const std::string title)
    : TerminalInterface(title) {}

TerminalTextEdit::TerminalTextEdit(const std::string title, std::string& textToEdit)
    : TerminalInterface(title)
{
    this->textToEdit = &textToEdit;
}

void TerminalTextEdit::setTextToEdit(std::string& textToEdit)
{
    this->textToEdit = &textToEdit;
}

/*! \todo This function only inputs a word, not a full line */
int TerminalTextEdit::show()
{
    TerminalInterface::show();

    std::cout << "Previous value: ";
    if ( textToEdit->empty() )
	std::cout << "\'Empty\'";
    else
	std::cout << *textToEdit,

    std::cout << std::endl << "New value: ";

    std::cin >> *textToEdit;

}
