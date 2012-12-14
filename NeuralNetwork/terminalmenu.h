/*! \file terminalmenu.h
 *  \brief Basic terminal menu interface.
 *
 * Shows a terminal menu with multiple choices and returns the selected
 * one.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Dec 12th, 2012
 *
 */
#ifndef TERMINALMENU_H
#define TERMINALMENU_H

#include "terminalinterface.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/*! \class TerminalMenu
 *  \brief Basic terminal menu interface.
 *
 * Shows a terminal menu with multiple choices and returns the selected
 * one.
 *
 * This menu can be configured by setting one by one all the possible choices
 * that the menu will show.
 *
 * The function show() will return the index of the selected choice, or -1 if
 * none was selected or an error happened.
 *
 */
class TerminalMenu : public TerminalInterface
{
public:
    //-- Constructors
    //--------------------------------------------------
    /*!
     * \brief Default constructor.
     */
    TerminalMenu();

    /*!
     * \brief Creates a TerminalMenu with a given title.
     *
     * \param title Title for the interface.
     */
    TerminalMenu(const std::string title);


    //-- Menu functions
    //---------------------------------------------------
    /*!
     * \brief Adds an option to the interface.
     *
     * \param newOption Text of the new option.
     */
    void addOption(const std::string newOption);

    /*!
     * \brief Sets the current selected option.
     *
     * \param num Current selected option.
     */
    void setCurrent(const int num);


    //-- Show function
    //----------------------------------------------------
    /*!
     * \brief Shows the menu on terminal.
     *
     * Shows the menu on terminal, and waits for user input to
     * select one of the choices. Then, it returns the index
     * (starting at 0) of the selected choice, or -1 in case of
     * error or none of them selected.
     *
     * \return Index of selected option, starting at 0.
     */
    int show();

private:
    /*!
     * \var std::vector<std::string> options
     * \brief Vector of strings containing the text of each choice of the menu.
     */
    std::vector<std::string> options;

    /*!
     * \var int numOptions
     * \brief Number of choices in the menu.
     */
    int numOptions;

    /*!
     * \var int currentOption
     * \brief Option currently selected.
     */
    int currentOption;

};

#endif // TERMINALMENU_H
