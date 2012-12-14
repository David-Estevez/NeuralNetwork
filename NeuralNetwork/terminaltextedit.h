/*! \file terminaltextedit.h
 *  \brief Basic text edition on terminal interface.
 *
 * Shows a terminal menu showing the previous value for a string and
 * asking the user to a new value for it.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Dec 10th, 2012
 *
 */
#ifndef TERMINALTEXTEDIT_H
#define TERMINALTEXTEDIT_H

#include "terminalinterface.h"

#include <iostream>
#include <string>

/*! \class TerminalTextEdit
 *  \brief Basic text edition on terminal interface.
 *
 * Shows a terminal menu showing the previous value for a string and
 * asking the user to a new value for it.
 *
 */
class TerminalTextEdit: public TerminalInterface
{
public:
    //-- Constructors
    //--------------------------------------------------
    /*!
     * \brief Creates a TerminalTextEdit with a given title.
     *
     * \param title Title for the interface.
     */
    TerminalTextEdit( const std::string title);

    /*!
     * \brief Creates a TerminalTextEdit with a given title and
     * a given string to modify.
     *
     * \param title Title for the interface.
     * \param textToEdit String to be modified.
     */
    TerminalTextEdit( const std::string title, std::string& textToEdit);


    //-- TextEdit functions
    //---------------------------------------------------
    /*!
     * \brief Sets the string that will be modified by the TerminalTextEdit.
     *
     * \param textToEdit String to be modified.
     */
    void setTextToEdit( std::string& textToEdit);


    //-- Show function
    //----------------------------------------------------
    /*!
     * \brief Shows the text edit interface on terminal.
     *
     * Shows a terminal menu showing the previous value for a string and
     * asking the user to a new value for it.
     *
     */
    int show();

private:
    /*!
     * \var std::string * textToEdit
     * \brief Pointer to the string to be modified.
     */
    std::string * textToEdit;
};

#endif // TERMINALTEXTEDIT_H
