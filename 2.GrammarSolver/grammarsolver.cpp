/*
 * This file contains grammar generating code for CS106B.
 */

#include "grammarsolver.h"
#include "strlib.h"
#include "map.h"
#include "random.h"

using namespace std;

/**
 * Generates grammar for a given symbol a certain number of times given
 * a BNF input file.
 *
 * This will be called by grammarmain.cpp.
 *
 * @param input - Input stream of BNF file.
 * @param symbol - Symbol to generate
 * @param times - Number of times grammar is generated
 * @return Vector of strings of size times with random generations of symbol
 */
string generate(Map<string, Vector<string>>&g, string symbol){
    if (g.containsKey(symbol)){
        string words = g[symbol][randomInteger(0, g[symbol].size()-1)];
        Vector<string> v = stringSplit(words, " ");
        for (int i = 0; i < v.size(); i++){
            if (g.containsKey(v[i])){
                string word = generate(g, v[i]);
                v[i] = word;
            }
        }
        string result;
        for (int i = 0; i < v.size(); i++){
            result += v[i] + ' ';
        }
        result.erase(result.size()-1,1);
        return result;
    }
    else {
        return symbol;
    }
}


Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    string line;
    Map<string, Vector<string>> grammar;
    Vector<string> result;

    while (getline(input, line)) {
        int pos = line.find("::=");
        string non_term = line.substr(0,pos);
        string g = line.substr(pos+3);
        Vector<string> v = stringSplit(g, "|");
        grammar[non_term] = v;
}
    for (int i = 0; i < times; i++){
        result.add(generate(grammar, symbol));
    }
    return result;
}

