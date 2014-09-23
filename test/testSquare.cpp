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
static void testSetterConstructor();
static void testCopyConstructor();
static void testSetValue();
static void testAssignment();


void testSquare(){
	cout << "\n***Testing class Square.***\n" << endl;

	testDefaultConstructor();
	testSetterConstructor();
	testCopyConstructor();
	testSetValue();
	testAssignment();

	cout << "\n*** All done! ***" << endl;
}

static void testDefaultConstructor(){
	cout << "\n***Testing default Square c'tor.***\n" << endl;

	// Cases for row/column: -1, 0, 1, 7, 8, 9
	try{
		cout <<
		"Trying to create bad square (-1 row), expecting exception ..." << endl;
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
		cout <<
		"Trying to create bad square (row=9), expecting exception ..." << endl;
		Square s(9,0);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}

	try{
		cout <<
		"Trying to create bad square (-1 col), expecting exception ..." << endl;
		Square s(0,-1);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}


	cout << "Creating a Square at r=0, c=1." << endl;
	Square s4(0,1);
	cout << "No issue." << endl;

	cout << "Creating a Square at r=0, c=7." << endl;
	Square s5(0,7);
	cout << "No issue." << endl;

	cout << "Creating a Square at r=0, c=8." << endl;
	Square s6(0,8);
	cout << "No issue." << endl;

	try{
		cout <<
		"Trying to create bad square (col=9), expecting exception ..." << endl;
		Square s(0,9);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}

	try{
		cout <<
		"Trying to create square at (-1,-1), expecting exception ..." << endl;
		Square s(-1,-1);
		assert(false && "Did not get expected exception.");
	}
	catch(std::out_of_range & e){
		cout << "Got exception." << endl;

	}

	// Test whether set and what possible values are.
	cout << "Testing square for setness, expecting unset: " << endl;

	assert(!s.isSet() && "Square was set?");


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

static void testSetterConstructor(){
	cout << "\n***Testing 'setter' constructor.***" << endl;

	std::set<int> posValues;
	std::set<int> valValues;
	for(int i = -1; i<=Square::puzzle_size; ++i)
		posValues.insert(i);
	for(int i=0; i<=Square::puzzle_size; ++i)
		valValues.insert(i);

	for(auto col : posValues){
		for(auto row : posValues){
			for(auto val: valValues){
				 // Invalid positions or values  should an std::out_of_range
				if(col < 0 ||
						col >= Square::puzzle_size ||
						row < 0 ||
						row >= Square::puzzle_size ||
						val < 1 ||
						val > Square::puzzle_size){
					try{
						Square s(row, col, val);
						assert(false && "Expected exception?");
					}
					catch(std::out_of_range & e){
						// All good
					}
				}
				else{
					Square s(row, col, val);
					std::set<int> testSet({val});
					assert(row==s.getRow() && "Square's row not set correctly?");
					assert(col==s.getCol() && "Square's col not set correctly?");
					assert(val==s.getValue() &&
							"Square's value not set correctly?");
					assert(s.isSet() && "Square is not set?");
					assert(s.getPossibleValues()==testSet &&
							"possibleValues not set correctly?");
				}
			}
		}
	}
	cout << "No problems!" << endl;
}

static void testCopyConstructor(){
	cout << "\n***Testing copy constructor.***" << endl;

	for(int row = 0; row < Square::puzzle_size; ++row){
		for(int col = 0; col < Square::puzzle_size; ++col){
			Square unset(row, col);
			Square unsetCopy(unset);

			assert(unset.getRow() == unsetCopy.getRow() && "Rows not equal?");
			assert(unset.getCol() == unsetCopy.getCol() && "Cols not equal?");
			assert(unset.isSet() == unsetCopy.isSet() && "isSet not equal?");
			assert(unset.getPossibleValues() == unsetCopy.getPossibleValues()
					&& "possibleValues not equal?");

			for(int val = 1; val<=Square::puzzle_size; ++val){
				Square set(row, col, val);
				Square setCopy(set);
				assert(set.getRow() == setCopy.getRow() &&
						"Rows not equal?");
				assert(set.getCol() == setCopy.getCol() &&
						"Cols not equal?");
				assert(set.isSet() == setCopy.isSet() &&
						"isSet not equal?");
				assert(set.getValue() == setCopy.getValue() &&
						"values not equal?");
				assert(set.getPossibleValues() == setCopy.getPossibleValues()
						&& "possibleValues not equal?");
			}
		}
	}
	cout << "No problems!"<< endl;
}

static void testSetValue(){
	// If value is not in proper range, a std::out_of_range should be thrown.

	cout << "\n***Testing setValue()***" << endl;

	Square unset(0,0);
	std::set<int> badValues = {-1,0,Square::puzzle_size+1, Square::puzzle_size+2};
	for(auto badValue : badValues){
		try{
			unset.setValue(badValue);
			assert(false && "Bad value set without issue?");
		}
		catch(std::out_of_range & e){
			// No issue.
		}
	}

	// If square is already set, false should be returned.
	for(int setValue = 1; setValue <= Square::puzzle_size; ++setValue){
		Square setSquare(0,0,setValue);
		for(int attemptValue = 1; attemptValue <= Square::puzzle_size; ++attemptValue){
			bool ret = setSquare.setValue(attemptValue);
			assert(!ret && "Was able to set the value of a set square?");
		}
	}

	// If value is not in list of possible values, false should be returned.
	// TODO Don't really have a way to test this with having restrictValues
	// working.

	// Otherwise, true should be returned, square should have value set,
	// possible values should be set to that value.
	for(int setValue = 1; setValue <= Square::puzzle_size; ++setValue){
		Square unset(0,0);
		bool ret = unset.setValue(setValue);

		std::set<int> squaresPossibleValues{setValue};

		assert(ret && "Square was not set?");
		assert(setValue == unset.getValue() && "Square did get proper value?");
		assert(squaresPossibleValues==unset.getPossibleValues() &&
				"Possible values don't match up?");
	}

	cout << "No problems!" << endl;

}

static void testAssignment(){
	cout << "\n***Testing assignment operator.***" << endl;

	for(int row = 0; row < Square::puzzle_size; ++row){
		for(int col = 0; col < Square::puzzle_size; ++col){
			Square unset(row, col);
			Square assignee;
			assignee = unset;

			assert(unset.getRow() == assignee.getRow() && "Rows not equal?");
			assert(unset.getCol() == assignee.getCol() && "Cols not equal?");
			assert(unset.isSet() == assignee.isSet() && "isSet not equal?");
			assert(unset.getPossibleValues() == assignee.getPossibleValues()
					&& "possibleValues not equal?");

			for(int val = 1; val<=Square::puzzle_size; ++val){
				Square set(row, col, val);
				Square setAssignee;
				setAssignee = set;
				assert(set.getRow() == setAssignee.getRow() &&
						"Rows not equal?");
				assert(set.getCol() == setAssignee.getCol() &&
						"Cols not equal?");
				assert(set.isSet() == setAssignee.isSet() &&
						"isSet not equal?");
				assert(set.getValue() == setAssignee.getValue() &&
						"values not equal?");
				assert(set.getPossibleValues() == setAssignee.getPossibleValues()
						&& "possibleValues not equal?");
			}
		}
	}
	cout << "No problems!"<< endl;
}
