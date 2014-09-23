/*
 * Puzzle.cpp
 *
 *  Created on: 20 Sep 2014
 *      Author: alex
 */

#include "Puzzle.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

Puzzle::Puzzle() :
	squares_(nullptr),
	solved_(false),
	numLeftToSolve_(puzzle_size*puzzle_size) {

	squares_ = new Square[puzzle_size*puzzle_size];

	try{
		for(int i = 0; i < puzzle_size*puzzle_size; i++){
			squares_[i].setRow(i/puzzle_size);
			squares_[i].setCol(i%puzzle_size);
		}
	}
	catch (std::out_of_range & e) {
		// The for loop above shouldn't throw any exceptions, but ...
		delete[] squares_;
		throw e;
	}

}

Puzzle::Puzzle(std::string filename) :
		squares_(nullptr),
		solved_(false),
		numLeftToSolve_(puzzle_size*puzzle_size){
	//TODO change squares_ into a std::vector<Square>. It will make things so much easier.
	//TODO make custom exception and divide this code up.
	std::ifstream inFile(filename);
	if(inFile.good()){
		squares_ = new Square[puzzle_size*puzzle_size];

		try{
			for(int i = 0; i < puzzle_size*puzzle_size; i++){
				squares_[i].setRow(i/puzzle_size);
				squares_[i].setCol(i%puzzle_size);
			}
		}
		catch (std::out_of_range & e) {
			// The for loop above shouldn't throw any exceptions, but ...
			delete[] squares_;
			throw e;
		}

		std::string line;
		int currentRow=0;
		bool success = true;

		while(!inFile.eof()){
			getline(inFile, line);
			if(static_cast<int>(line.size())!=puzzle_size){
				success = false;
				break;
			}
			int currentCol = 0;

			for(auto it = line.begin();	it!=line.end();	it++){
				char character = *it;

				if(character=='#'){
					// We would create an unset square here, but square are by
					// default unset, so we don't have to do anything.
				}
				else{
					// check if number in valid range
					int num = character - '0';
					if(num < 1 || num > puzzle_size)
						break;

					squares_[currentRow*puzzle_size+currentCol].setValue(num);
				}

				currentCol++;
			}

			if(currentCol!=puzzle_size){
				success = false;
				break;
			}

			currentRow++;
		}

		if(currentRow!=puzzle_size)
			success = false;

		if(!success){
			delete[] squares_;
			std::ostringstream oss;
			oss << "Error in processing file '" << filename << "'.";
			throw std::runtime_error(oss.str());
		}

		//TODO check if valid?
	}
	else{
		std::ostringstream oss;
		oss << "Could not open file '" << filename << "'.";
		throw std::runtime_error(oss.str());
	}

}

Puzzle::Puzzle(const Puzzle & other) :
		squares_(nullptr),
		solved_(other.solved_),
		numLeftToSolve_(other.numLeftToSolve_){
	squares_ = new Square[puzzle_size*puzzle_size];
	for(int i = 0; i < puzzle_size*puzzle_size; i++){
		squares_[i] = other.squares_[i];
	}
}

Puzzle & Puzzle::operator=(const Puzzle & other){

	// Handle self-assignment.
	if(this==&other)
		return *this;

	solved_ = other.solved_;
	numLeftToSolve_ = other.numLeftToSolve_;

	delete[] squares_;
	squares_ = nullptr;

	squares_ = new Square[puzzle_size*puzzle_size];
	for(int i = 0; i < puzzle_size*puzzle_size; i++)
		squares_[i] = other.squares_[i];

	return *this;
}

Puzzle::~Puzzle() {
	delete[] squares_;
}
