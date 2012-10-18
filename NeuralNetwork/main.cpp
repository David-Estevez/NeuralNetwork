#include "neuron.h"
#include "layer.h"
#include "matrix.h"

#include <iostream>


int main()
{

    //-- Debuggin' main routine::
    //--------------------------------------------------

    //-- Debuggin' Neurons::
    //----------------------------------------------------------------------
    std::cout << "Neuron test\n------------------------------------------\n";

    Neuron miNeurona01, miNeurona02, miNeurona03, miNeurona04;

    //-- Manually set the input:
    miNeurona02.setOutput(3);
    miNeurona03.setOutput(5);
    miNeurona04.setOutput(-10);

    //-- Add connections:
    miNeurona01.addConnection(miNeurona02);
    miNeurona01.addConnection(miNeurona03);
    miNeurona01 << miNeurona04;

    //-- Show default weights:
    std:: cout << "Weight#1: " << miNeurona01.getWeight(0) << std::endl
	       << "Weight#2: " << miNeurona01.getWeight(1) << std::endl
	       << "Weight#3: "<< miNeurona01.getWeight(2) << std::endl;

    miNeurona01.refresh();
    std::cout << "Network output: " << miNeurona01.getOutput() << std::endl;
    std::cout << "------------------" << std::endl;

    //-- Change weights:
    miNeurona01.changeWeight(0, 1.2);
    miNeurona01.changeWeight(1, 5);
    miNeurona01.changeWeight(2, 1.25);

    std::cout << "Weight#1: " << miNeurona01.getWeight(0) << std::endl
	      << "Weight#2: " << miNeurona01.getWeight(1) << std::endl
	      << "Weight#3: " << miNeurona01.getWeight(2) << std::endl;

    miNeurona01.refresh();
    std::cout << "Network output: " << miNeurona01.getOutput() << std::endl;
    std::cout << "------------------" << std::endl;

    //-- Show weights:
    std::vector<double> myWeights = miNeurona01.getWeight();

    std::cout << "These are the weights: " << std::endl;

    for (int i = 0; i < myWeights.size(); i++)
	std::cout << "Weight#" << i+1 << ": " << myWeights[i] << std::endl;

    //-- Change the weights again:
    std::vector<double> newWeights;
    newWeights.push_back(1.25);
    newWeights.push_back(1.2);
    newWeights.push_back(-5);

    miNeurona01.changeWeight( newWeights);

    std::cout << std::endl << "These are the new weights: " << std::endl;
    std::cout << "Weight#1: " << miNeurona01.getWeight(0) << std::endl
	      << "Weight#2: " << miNeurona01.getWeight(1) << std::endl
	      << "Weight#3: " << miNeurona01.getWeight(2) << std::endl;

    std::cout << "------------------" << std::endl;

    //-- Debuggin' Layers:
    //-------------------------------------------------------------------------
    Layer myLayer01(3), myLayer02(2), myLayer03(1);

    //-- Test size
    std::cout << "\nLayer test\n------------------------------\nSize of layer: " << myLayer01.getN() << std::endl;

    //-- Input some data
    myLayer01.setOutput(newWeights);

    //-- Connect layers
    myLayer02 << myLayer01;
    myLayer03.connectLayer( myLayer02);

    //-- Calculate result
    std::vector<double> result = myLayer03.getOutput();
    std::cout << "Output of Network (3, 2, 1): " << result[0] << std::endl;

    Matrix myMatrix(3,3);
    myMatrix.set(1, 1, 3.14);
    std::cout << myMatrix.get(1,1);

}
