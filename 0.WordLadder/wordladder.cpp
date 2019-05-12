#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "lexicon.h"
#include "simpio.h"
#include "queue.h"
#include "stack.h"

using namespace std;

const string abc = "abcdefghijklmnopqrstuvwxyz";

void printStack(Stack<string> s);
Stack<string> wordLadder(string word1, string word2, Lexicon dict);

int main() {
    cout << "Welcome to CS 106B Word Ladder." << endl;
    cout << "Please give me two English words, and I will change the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    string prompt = "Dictionary file name?";
    string reprompt = "Unable to open that file.  Try again.";
    string filename = promptUserForFile(prompt, reprompt);
    cout << endl;
    Lexicon dict(filename);

    while (true){
        string word1 = getLine("Word #1 (or Enter to quit):");
        if (word1 == "") break;
        word1 = toLowerCase(word1);
        string word2 = getLine("Word #2 (or Enter to quit):");
        if (word2 == "") break;
        word2 = toLowerCase(word2);

        if (word1.length() != word2.length()) {cout << "The two words must be the same length." << endl;}
        else if (!(dict.contains(word1) && dict.contains(word2))) {cout << "The two words must be found in the dictionary." << endl;}
        else if (word1 == word2) {cout << "The two words must be different." << endl;}
        else {
            Stack<string> ladder = wordLadder(word1, word2, dict);
            if (ladder.isEmpty()) {cout << "No word ladder found from " << word2 << " back to " << word1 <<"." << endl;}
            else {
                cout << "A ladder from " << word2 << " back to " << word1 << ":" << endl;
                printStack(ladder);
            }
            cout << endl;
        }
    }
    cout << "Have a nice day." << endl;
    return 0;
}


void printStack(Stack<string> s){
    int size = s.size();
    for (int i = 0; i < size; i++){
        cout << s.pop() << " ";
    }
    cout << endl;
}

Stack<string> wordLadder(string word1, string word2, Lexicon dict){
    Lexicon used;
    Queue<Stack<string>> q;
    Stack<string> s;
    Stack<string> s2;
    Stack<string> empty;
    string word;
    string new_word;
    s.push(word1);
    q.enqueue(s);
    used.add(word1);
    while (!q.isEmpty()){
        s = q.dequeue();
        word = s.top();
        for (int i = 0; i < word.length(); i++){
            for (char c: abc){
                if (word[i] != c){
                   new_word = word.substr(0,i) + c + word.substr(i+1);
                   if (new_word == word2){
                       s.push(word2);
                       return s;
                       }
                    else if (dict.contains(new_word) && (!used.contains(new_word))) {
                        s2 = s;
                        s2.push(new_word);
                        q.enqueue(s2);
                        used.add(new_word);
                        }
                        }
                    }
        }
}
    return empty;
}
