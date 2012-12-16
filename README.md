NeuralNetwork
=============

Neural network implementation on C++

 * Author: [David Estévez-Fernández](http://github.com/David-Estevez)
 * Released under GPL license , Dec 2012

0. Index
----------------------------------------------------------------------
 * 1.Introduction
 * 2.Dependencies 
 * 3.Compilation
 * 4.Usage
 * 5.Version log

1. Introduction
----------------------------------------------------------------------
Implementation of a neural network and a training mechanism using backpropagation
algorithm and gradient descend for optimization.

To use that network a simple terminal interface has been implemented.

This is a work for a programming subject at University Carlos III of Spain.

2. Dependencies
----------------------------------------------------------------------
There are no extra dependencies to make the neural network work, but in order to visualize the
interface properly a terminal with ANSI escape secuences capabilities is required, such as xterm 
or the gnome default terminal, gnome-terminal.

3. Compilation
----------------------------------------------------------------------
 * Using QtCreator:

Install QtCreator : `sudo apt-get install qtcreator`

Run qtcreator and open the NeuralNetwork.pro file downloaded from this repository.

Press "build" button.

* Using g++:

In a terminal run: `cd yourDownloadPath/NeuralNetwork`

Then: `g++ *.cpp -o NeuralNetwork`

4. Basic Usage
----------------------------------------------------------------------
* To run the code just change the working directory with cd and then type in a terminal:

`./NeuralNetwork`

* To select one option in the menu just type the index of that option (starting at 0) and 
press enter key.

* For more information please read the documentation file.

5. Version log
-----------------------------------------------------------------------
 * Version 1.0 Basic neural network with training mechanism and simple terminal interface.

