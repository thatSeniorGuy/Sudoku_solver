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

Puzzle::PuzzleFileException::PuzzleFileException(
		Reason reason,
		char * filename,
		char * line,
		int length,
		char invalidValue) :
		reason_(reason),
		length_(length),
		invalidValue_(invalidValue)
{
	switch(reason_){
	case TOO_FEW_LINES:
		// Only thing that needs to be set is filename.

		break;

	case INVALID_LINE_LENGTH:

		break;

	case INVALID_VALUE:

		break;
	}

}

const char * Puzzle::PuzzleFileException::what(){




	return whatMessage_;
}

Puzzle::Puzzle() :
	squares_(puzzle_size*puzzle_size),
	solved_(false),
	numLeftToSolve_(puzzle_size*puzzle_size) {

	for(int i = 0; i < puzzle_size*puzzle_size; i++){
		squares_[i].setRow(i/puzzle_size);
		squares_[i].setCol(i%puzzle_size);
	}
}

Puzzle::Puzzle(std::string filename) :
		squares_(puzzle_size*puzzle_size),
		solved_(false),
		numLeftToSolve_(puzzle_size*puzzle_size){

	std::ifstream inFile(filename);
	if(inFile.good()){

		for(int i = 0; i < puzzle_size*puzzle_size; i++){
			squares_[i].setRow(i/puzzle_size);
			squares_[i].setCol(i%puzzle_size);
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
			//TODO make custom exception and divide this code up.
			std::ostringstream oss;
			oss << "Error in processing file '" << filename << "'.";
			throw std::runtime_error(oss.str());
		}
	}
	else{
		std::ostringstream oss;
		oss << "Could not open file '" << filename << "'.";
		throw std::runtime_error(oss.str());
	}

}

Puzzle::Puzzle(const Puzzle & other) :
		squares_(other.squares_),
		solved_(other.solved_),
		numLeftToSolve_(other.numLeftToSolve_)
{}

Puzzle & Puzzle::operator=(const Puzzle & other){
	// Handle self-assignment.
	if(this==&other)
		return *this;

	solved_ = other.solved_;
	numLeftToSolve_ = other.numLeftToSolve_;
	squares_ = other.squares_;
	return *this;
}
