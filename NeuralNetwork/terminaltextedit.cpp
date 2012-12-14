#include "terminaltextedit.h"

//-- Constructors
//--------------------------------------------------
TerminalTextEdit::TerminalTextEdit(const std::string title)
    : TerminalInterface(title) {}

TerminalTextEdit::TerminalTextEdit(const std::string title, std::string& textToEdit)
    : TerminalInterface(title)
{
    this->textToEdit = &textToEdit;
}

//-- TextEdit functions
//---------------------------------------------------
void TerminalTextEdit::setTextToEdit(std::string& textToEdit)
{
    this->textToEdit = &textToEdit;
}



//-- Show function
//----------------------------------------------------
int TerminalTextEdit::show()
{
    //-- Display header
    TerminalInterface::show();

    //-- Display previous value for string
    std::cout << "Previous value: ";
    if ( textToEdit->empty() )
	std::cout << "\'Empty\'";
    else
	std::cout << *textToEdit;

    //-- Ask for new value for string
    std::cout << std::endl << "New value: ";
    std::getline( std::cin, *textToEdit);

    return 0;
}
