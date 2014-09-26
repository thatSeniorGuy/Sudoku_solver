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
	// Zero out whatMessage (will be constructed when what() is called.
	for(auto & cha : whatMessage_)
		cha = '\0';

	// Zero out the rest as well.
	for(auto & cha : line_)
		cha = '\0';

	for(auto & cha : filename_)
		cha = '\0';

	/* In all cases, we want to set the filename; restrict it to the size of
	 * our fileName_ member. */
	if(filename != nullptr){
		int fileNameLength = strlen(filename);
		// Last char is for null character.
		strncpy(filename_, filename,
				fileNameLength>(STR_LEN-1) ? (STR_LEN-1) : fileNameLength);
	}
	else{
		strcpy(filename_, "Filename not provided correctly.");
	}


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
		if(line != nullptr){
			int lineLength = strlen(line);
			// Restrict to line_'s size, last char is the null character,
			strncpy(line_, line,
					lineLength>(STR_LEN-1) ? (STR_LEN-1) : lineLength);
		}
		else{
			strcpy(line_, "Line not provided correctly.");
		}
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
	strcat(whatMessage_, "The file '");
	strcat(whatMessage_, filename_);
	strcat(whatMessage_, "' ");

	switch(reason_){
	case TOO_FEW_LINES:
		strcat(whatMessage_, " had too few lines for a valid Sudoku puzzle.");
		break;

	case INVALID_LINE_LENGTH:
		strcat(whatMessage_, "had the line '");
		strcat(whatMessage_, line_);
		strcat(whatMessage_, "of length ");
		char size[10];
		snprintf(size, 9, "%d", length_);
		strcat(whatMessage_, size);
		strcat(whatMessage_, ".");
		break;

	case INVALID_VALUE:
		strcat(whatMessage_, "had the line '");
		strcat(whatMessage_, line_);
		strcat(whatMessage_, "' which contained the invalid value of '");
		char badValue[2];
		snprintf(badValue, 1, "%c", invalidValue_);
		strcat(whatMessage_, badValue);
		strcat(whatMessage_, ".");
	}

	return whatMessage_;
}

Puzzle::PuzzleFileException::PuzzleFileException(
		const PuzzleFileException & other) :
			std::runtime_error(""),
			reason_(other.reason_),
			length_(other.length_),
			invalidValue_(other.invalidValue_)
{
	// Zero out whatMessage (will be constructed when what() is called.
	for(auto & cha : whatMessage_)
		cha = '\0';

	for(int i = 0; i < STR_LEN; ++i)
			filename_[i] = other.filename_[i];

	for(int i = 0; i < STR_LEN; ++i)
		line_[i] = other.line_[i];
}

Puzzle::PuzzleFileException &
Puzzle::PuzzleFileException::operator=(
		const PuzzleFileException & other){
	// whatMessage is constructed when what() is called.
	for(auto & cha : whatMessage_)
		cha = '\0';

	reason_ = other.reason_;
	length_ = other.length_;
	invalidValue_ = other.invalidValue_;

	for(int i = 0; i < STR_LEN; ++i)
		filename_[i] = other.filename_[i];

	for(int i = 0; i < STR_LEN; ++i)
		line_[i] = other.line_[i];

	return *this;
}

Puzzle::PuzzleFileException::Reason
Puzzle::PuzzleFileException::getReason() const {
	return reason_;
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
