/**
 * \file testSquare.cpp
 *
 * Test code for class Square.
 *
 *  Created on: 22 Sep 2014
 *      Author: Alexander Senior.
 */

#include "Square.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

using std::cout;
using std::endl;

void testSquare();
static void testDefaultConstructor();


void testSquare(){
	cout << "\n***Testing class Square.***\n" << endl;

	testDefaultConstructor();

}

static void testDefaultConstructor(){
	cout << "\n***Testing default Square c'tor.***\n" << endl;

	// Cases for row/column: -1, 0, 1, 7, 8, 9
	try{
		cout << "Trying to create bad square (-1 row), expecting exception ..." << endl;
		Square s(-1,0);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}

	cout << "Creating a Square at r=0, c=0." << endl;
	Square s(0,0);
	cout << "No issue." << endl;

	cout << "Creating a Square at r=1, c=0." << endl;
	Square s1(1,0);
	cout << "No issue." << endl;

	cout << "Creating a Square at r=7, c=0." << endl;
	Square s2(7,0);
	cout << "No issue." << endl;

	cout << "Creating a Square at r=8, c=0." << endl;
	Square s3(8,0);
	cout << "No issue." << endl;

	try{
		cout << "Trying to create bad square (row=9), expecting exception ..." << endl;
		Square s(9,0);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}

	// Test whether set and what possible values are.
	cout << "Testing square for setness, expecting unset: " << endl;
	if(s.isSet())
		assert(false && "Square was set?");
	else
		cout << "Square was not set." << endl;

	cout << "Possible values should have all integers from 1 to : "
			<< Square::puzzle_size << endl;

	std::set<int> vals;
	for(int i = 1; i <= Square::puzzle_size; ++i) {
		auto ret = vals.insert(i);
		if(!ret.second)
			assert(false && "Error in making set?");
	}

	if(vals == s.getPossibleValues())
		cout << "Have them all" << endl;
	else
		assert(false && "Did not have expected set of values?");
}




