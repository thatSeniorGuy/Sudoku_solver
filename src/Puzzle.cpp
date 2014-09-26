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
#include <cstring>

Puzzle::PuzzleFileException::PuzzleFileException(
		Reason reason,
		const char * filename,
		const char * line,
		int length,
		char invalidValue) :
		std::runtime_error(""),
		reason_(reason),
		length_(length),
		invalidValue_(invalidValue)
{
	// Zero-out all of our char arrays.
	for(auto & cha : whatMessage_)
		cha = '\0';

	for(auto & cha : line_)
		cha = '\0';

	for(auto & cha : filename_)
		cha = '\0';

	/* In all cases, we want to set the filename; restrict it to the size of
	 * our fileName_ member. */
	int fileNameLength = strlen(filename);
	// Last char is for null character.
	strncpy(filename_, filename, fileNameLength>59 ? 59 : fileNameLength);

	switch(reason_){
	case TOO_FEW_LINES:
		// Filename is the only thing that needs to be set, so don't have to
		// do anything.
		break;

	case INVALID_LINE_LENGTH:
	case INVALID_VALUE:

		// Both cases need to set line_.
		// For INVALID_LINE_LENGTH, need to set length (done in member
		// initialisation), and  for INVALID_VALUE, need to set need to set
		// invalid value (also done in member initialisation).
		int lineLength = strlen(line);
		// Restrict to line_'s size, last char is the null character,
		strncpy(line_, line, lineLength>59 ? 59 : lineLength);
		break;
	}
}

Puzzle::PuzzleFileException Puzzle::PuzzleFileException::tooFewLines(
		const char * fileName) {
	return PuzzleFileException(TOO_FEW_LINES, fileName);
}

Puzzle::PuzzleFileException
Puzzle::PuzzleFileException::invalidLineLength(
		const char * filename, const char * line, int lineLength){
	return PuzzleFileException(
			INVALID_LINE_LENGTH, filename, line, lineLength);
}

Puzzle::PuzzleFileException
Puzzle::PuzzleFileException::invalidValue(
		const char * filename, const char * line, char invalidValue){
	return PuzzleFileException(INVALID_VALUE, filename, line, 0, invalidValue);
}

const char * Puzzle::PuzzleFileException::what(){
	//TODO




	return whatMessage_;
}

Puzzle::Puzzle() :
	//squares_(puzzle_size*puzzle_size),
	solved_(false),
	numLeftToSolve_(puzzle_size*puzzle_size) {

	for(int i = 0; i < puzzle_size*puzzle_size; i++){
		squares_[i].setRow(i/puzzle_size);
		squares_[i].setCol(i%puzzle_size);
	}
}

Puzzle::Puzzle(std::string filename) :
		//squares_(puzzle_size*puzzle_size),
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
	for(int i = 0; i < puzzle_size*puzzle_size; ++i)
		squares_[i] = other.squares_[i];

	return *this;
}
