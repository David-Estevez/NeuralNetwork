#include "terminalmenu.h"

TerminalMenu::TerminalMenu() : TerminalInterface()
{
    numOptions = 0;
    currentOption = -1;
}

TerminalMenu::TerminalMenu(const std::string title ) : TerminalInterface(title)
{
    numOptions = 0;
    currentOption = -1;
}

void TerminalMenu::show()
{
    TerminalInterface::show();

    //-- Choices:
    if (!options.empty())
    {
	std::cout << std::endl;
	for (int i = 0; i < (int) options.size(); i++)
	{
	    if (currentOption == i)	{ std::cout << '>' << HIGHLIGHT ; } else { std::cout << RESET_FORMAT; }
	    std::cout << options.at(i) << std::endl;
	}

    }
    std::cout << RESET_FORMAT;
}

void TerminalMenu::addOption( const std::string newOption)
{
    options.push_back( newOption );
    numOptions = options.size();
}

void TerminalMenu::setCurrent(const int num)
{
    if ( num >= -1 && num < numOptions )
    {
	currentOption = num;
    }
}



