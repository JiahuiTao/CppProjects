/*
 * CS 106B Huffman Encoding
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include "bitstream.h"
#include "HuffmanNode.h"
#include "map.h"
#include "pqueue.h"
#include "filelib.h"
using namespace std;


Map<int, int> buildFrequencyTable(istream& input);
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable);
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output);
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);
void compress(istream& input, obitstream& output);
void decompress(ibitstream& input, ostream& output);
void freeTree(HuffmanNode* node);

void getEncoding(HuffmanNode* encodingTree, Map<int, string> &encodingMap, string code);
int getDecoding(ibitstream& input, HuffmanNode* encodingTree);
#endif
