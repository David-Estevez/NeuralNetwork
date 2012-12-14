/*! \file terminalinterface.h
 *  \brief Basic terminal interface.
 *
 * Base class for creating simple terminal interfaces. Shows a
 * header on top of the terminal with a given title.
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Dec 10th, 2012
 *
 */

#ifndef TERMINALINTERFACE_H
#define TERMINALINTERFACE_H

#include <iostream>
#include <string>

/*! \class TerminalInterface
 *  \brief Base class for creating simple terminal interfaces.
 *
 *  Shows a header on top of the terminal with a given title.
 *
 */
class TerminalInterface
{
public:
    //-- Constructors
    //--------------------------------------------------
    /*!
     * \brief Default constructor.
     */
    TerminalInterface();

    /*!
     * \brief Creates a TerminalInterface with a given title.
     *
     * \param title Title for the interface.
     */
    TerminalInterface(const std::string title);

    //-- Data interface
    //----------------------------------------------------
    /*!
     * \brief Sets the title for the TerminalInterface.
     *
     * \param newTitle Title for the interface.
     */
    void setTitle(const std::string newTitle );

    /*!
     * \brief Show the current interface on terminal.
     *
     * This interface just shows a terminal interface with just a header.
     * On derived classes this function has to implement the main functionality
     * of the interface.
     *
     * \return A value indicating if it has ended without any issue.
     */
    virtual int show();

private:
    /*!
     * \var std::string menuTitle
     * \brief Title of the interface.
     */
    std::string menuTitle;

protected:
    //-- ANSI terminal escape sequences:
    //------------------------------------------------------------------------
    /*!
     * \var static const std::string CLEAR_SCREEN
     * \brief String containing the ANSI escape code for clearing the terminal.
     */
    static const std::string CLEAR_SCREEN;

    /*!
     * \var static const std::string HOME_SCREEN
     * \brief String containing the ANSI escape code for setting the cursor at
     * position (0,0).
     */
    static const std::string HOME_SCREEN;

    /*!
     * \var static const std::string RESET_FORMAT
     * \brief String containing the ANSI escape code for setting the default
     * output format.
     */
    static const std::string RESET_FORMAT;

    /*!
     * \var static const std::string BOLD
     * \brief String containing the ANSI escape code for setting the output
     * format to bold.
     */
    static const std::string BOLD;

    /*!
     * \var static const std::string HIGHLIGHT
     * \brief String containing the ANSI escape code for setting the output
     * format to highlighted text.
     */
    static const std::string HIGHLIGHT;

    /*!
     * \var static const std::string PURPLE
     * \brief String containing the ANSI escape code for setting the output color
     * to purple.
     */
    static const std::string PURPLE;

};

#endif // TERMINALINTERFACE_H
