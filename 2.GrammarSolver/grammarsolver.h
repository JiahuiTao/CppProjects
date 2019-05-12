/*
 * CS 106B Recursion Problems
 * This file declares necessary function prototypes, so that other files
 * are able to call the recursive functions you will write.
 */

#ifndef _recursionproblems_h
#define _recursionproblems_h

#include <iostream>
#include <string>
#include "gbufferedimage.h"
#include "gwindow.h"
#include "vector.h"

// function prototype declarations
Vector<std::string> grammarGenerate(std::istream& input, std::string symbol, int times);

#endif

