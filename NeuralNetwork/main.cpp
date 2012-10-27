#include "neuron.h"
#include "layer.h"
#include "neuralnetwork.h"

#include "matrix.h"

#include "data.h"

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
    miNeurona01.setWeight(0, 1.2);
    miNeurona01.setWeight(1, 5);
    miNeurona01.setWeight(2, 1.25);

    std::cout << "Weight#1: " << miNeurona01.getWeight(0) << std::endl
	      << "Weight#2: " << miNeurona01.getWeight(1) << std::endl
	      << "Weight#3: " << miNeurona01.getWeight(2) << std::endl;

    miNeurona01.refresh();
    std::cout << "Network output: " << miNeurona01.getOutput() << std::endl;
    std::cout << "------------------" << std::endl;

    //-- Show weights:
    std::vector<double> myWeights = miNeurona01.getWeight();

    std::cout << "These are the weights: " << std::endl;

    for (int i = 0; i < (int) myWeights.size(); i++)
	std::cout << "Weight#" << i+1 << ": " << myWeights[i] << std::endl;

    //-- Change the weights again:
    std::vector<double> newWeights;
    newWeights.push_back(1.25);
    newWeights.push_back(1.2);
    newWeights.push_back(-5);

    miNeurona01.setWeight( newWeights);

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
    myLayer02.refresh();
    myLayer03.refresh();

    std::vector<double> result = myLayer03.getOutput();
    std::cout << "Output of Network (3, 2, 1): " << result[0] << std::endl;

    std::cout << "------------------" << std::endl;

    //-- Testing matrix:
    //---------------------------------------------------------------------------
    std::cout << "\n Matrix test:" << std::endl;
    Matrix myMatrix01(2,4), myMatrix02(1, 3);

    for (int i = 0; i < 4; i ++)
	for (int j = 0; j < 2 ; j++)
	    myMatrix01.set(j, i, i+j);

    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 1; j++)
	    myMatrix02.set(j, i, i);


    std::cout << "My matrix 01 is : " << std::endl << myMatrix01 << std::endl;
    std::cout << "My matrix 02 is : " << std::endl << myMatrix02 << std::endl;

    myLayer02.setWeights( myMatrix01);
    myLayer03.setWeights( myMatrix02);
    myLayer02.refresh();
    myLayer03.refresh();
    result = myLayer03.getOutput();
    std::cout << "Output of Network (3, 2, 1): " << result[0] << std::endl;

    std::cout << "------------------" << std::endl;

    //-- Testing neural network:

    //-- Dimensions of the network:
    std::vector<int> myDims;
    myDims.push_back(400);
    myDims.push_back(25);
    myDims.push_back(10);

    NeuralNetwork myNetwork( myDims);
    std::cout << "Size in memory: " << sizeof( myNetwork) << std::endl;

    //-- Defining theta matrices:
    Matrix theta1 (25, 401);
    theta1 = returnTheta1();
    std::cout << "Size in memory: " << sizeof( theta1 ) << std::endl;

    Matrix theta2( 10, 26);
    theta2 = returnTheta2();
    std::cout << "Size in memory: " << sizeof( theta2 ) << std::endl;

    std::vector<Matrix> thetaVector;
    thetaVector.push_back( theta1 );
    thetaVector.push_back( theta2 );
    std::cout << "Size in memory: " << sizeof( thetaVector ) << std::endl;

    myNetwork.setWeights( thetaVector );


    myNetwork.setInput(  returnInput2() );
    myNetwork.refresh();

    std::cout << "Output (input:number 3):> "
	      << myNetwork.getOutput() << std::endl;

    myNetwork.setInput( returnInput1() );
    myNetwork.refresh();
    std::cout << "Output (input:number 0):>"
	      << myNetwork.getOutput() << std::endl;

}
