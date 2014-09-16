/*
 * Square.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: alex
 */

#include <stdexcept>
#include <sstream>
#include "Square.h"

Square::Square(int row, int col, int value) :
	row_(row), col_(col), isSet_(true), value_(value), possibleValues_(value)
{
	try{
		validatePosition(row, col);
	}
	catch (std::exception & e) {
		throw e;
	}

	if(value < 1 || value > puzzle_size){
		std::ostringstream oss;
		oss << "Invalid value supplied (" << value <<").";
		throw std::out_of_range(oss.str().c_str());
	}
}

Square::Square(int row, int col) :
		row_(row), col_(col), isSet_(false), value_(-1), possibleValues_()
{
	try{
		validatePosition(row, col);
	}
	catch (std::exception * e) {
		throw e;
	}

	for(int i = 1; i<=puzzle_size; i++){
		auto ret = possibleValues_.insert(i);
		if(!ret.second)
			throw std::runtime_error("Couldn't insert values into set?");
	}
}

Square::Square(const Square & other) :
		row_(other.row_), col_(other.col_), isSet_(other.isSet_),
		value_(other.value_), possibleValues_(other.possibleValues_)
{}

bool Square::setValue(int newValue){
	//TODO mixing bools and exceptions seems wrong.
	if(newValue < 0 || newValue > puzzle_size){
		std::ostringstream oss;
		oss << "Invalid new value (" << newValue << ") supplied.";
		throw std::out_of_range(oss.str().c_str());
	}

	// Can't set a square if it's already set.
	if(isSet_)
		return false;

	// Can't set a square if the given value isn't allowed.
	if(possibleValues_.count(newValue) == 0)
		return false;

	value_ = newValue;
	possibleValues_.clear();

	auto ret = possibleValues_.insert(value_);
	if(!ret.second)
		throw std::runtime_error("Could not insert new value into set?");

	return true;
}

int Square::getRow() const {
	return row_;
}

int Square::getCol() const {
	return col_;
}

Position Square::getPosition() const{
	Position pos(row_, col_);
	return pos;
}

bool Square::isSet() const {
	return isSet_;
}

int Square::getValue() const {
	//TODO should throw an exception here if this square is not set.

	return value_;
}

std::set<int> Square::getPossibleValues() const {
	return possibleValues_;
}

Square & Square::operator=(const Square & other){
	this->row_ = other.row_;
	this->col_ = other.col_;
	this->isSet_ = other.isSet_;
	this->possibleValues_ = other.possibleValues_;
	return *this;
}

static void Square::validatePosition(int row, int col){
	if(row < 0 || row >= puzzle_size){
		std::ostringstream oss;
		oss << "Invalid row supplied (" << row <<").";
		throw std::out_of_range(oss.str().c_str());
	}

	if(col < 0 || col >= puzzle_size){
		std::ostringstream oss;
		oss << "Invalid col supplied (" << col <<").";
		throw std::out_of_range(oss.str().c_str());
	}
}


