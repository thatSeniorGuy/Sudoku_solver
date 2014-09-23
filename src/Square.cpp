/*
 * Square.cpp
 *
 *  Created on: 16 Sep 2014
 *      Author: Alexander Senior.
 */

#include <stdexcept>
#include <sstream>
#include "Square.h"

Square::Square(int row, int col, int value) :
	row_(row), col_(col), isSet_(true), value_(value), possibleValues_({value})
{
	try{
		validateCoordinate(row);
		validateCoordinate(col);
	}
	catch (std::exception & e) {
		throw;
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
		validateCoordinate(row);
		validateCoordinate(col);
	}
	catch (std::exception & e) {
		throw;
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
	if(newValue < 1 || newValue > puzzle_size){
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
	isSet_ = true;
	possibleValues_.clear();

	auto ret = possibleValues_.insert(value_);
	if(!ret.second)
		throw std::runtime_error("Could not insert new value into set?");

	return true;
}

void Square::setRow(int newRow){
	try{
		validateCoordinate(newRow);
		row_ = newRow;
	}
	catch(std::out_of_range & e) {
		throw;
	}
}

void Square::setCol(int newCol){
	try{
		validateCoordinate(newCol);
		col_ = newCol;
	}
	catch(std::out_of_range & e){
		throw;
	}
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
	if(!isSet_)
		throw std::logic_error("Tried to get the value of an un-set square.");

	return value_;
}

std::set<int> Square::getPossibleValues() const {
	return possibleValues_;
}

bool Square::restrictValues(std::initializer_list<int> vals){
	// If this square is already set, then there's no point in continuing.
	if(isSet_)
		return false;

	for(auto & x: vals){

		// Check that potential restrict-ee is valid.
		if(x < 1 || x > puzzle_size){
			std::ostringstream oss;
			oss << "Value of '" << x << "' is invalid.";
			throw std::out_of_range(oss.str().c_str());
		}

		/* std::set::erase() returns the number of elements erased. If 0 was
		 * returned, then the value was already not possible for this square,
		 * so there's no point in further processing _this_ value in the
		 * list. */
		if(possibleValues_.erase(x) == 0)
			continue;

		/* If there's only one possible value left, then that must be this
		 * Square's value; set this square appropriately and return. */
		if(possibleValues_.size() == 1){
			value_ = *(possibleValues_.begin());
			isSet_ = true;
			return true;
		}

		if(possibleValues_.size() == 0)
			throw std::logic_error("Square has been left with no possible values.");
	}

	return false;
}

Square & Square::operator=(const Square & other){

	// Handle self-assignment.
	if(this==&other)
		return *this;

	this->row_ = other.row_;
	this->col_ = other.col_;
	this->isSet_ = other.isSet_;
	this->value_ = other.value_;
	this->possibleValues_ = other.possibleValues_;
	return *this;
}

void Square::validateCoordinate(int coord){
	if(coord < 0 || coord >= puzzle_size){
		std::ostringstream oss;
		oss << "Invalid co-ordinate supplied (" << coord <<").";
		throw std::out_of_range(oss.str().c_str());
	}
}

void Square::validatePosition(const Position & pos){
	try{
		validateCoordinate(pos.row);
		validateCoordinate(pos.col);
	}
	catch(std::out_of_range & e){
		throw;
	}
}

std::string Square::toString() const {
	std::ostringstream oss;
	if(isSet_)
		oss << value_;
	else
		oss << "#";
	return oss.str();
}

std::ostream & operator<<(std::ostream & ostream, const Square & square){
	ostream << square.toString();
	return ostream;
}


