#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "queue.h"
#include "stack.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "random.h"


using namespace std;

int promptUserForN();
int promptUserForL();

int main() {
    cout << "Welcome to CS 106B Random Writer ('N-Grams')." << endl;
    cout << "This program makes random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << endl;

    ifstream stream;
    string prompt = "Input file name?";
    string reprompt = "Unable to open that file.  Try again.";
    string filename = promptUserForFile(stream, prompt, reprompt);
    cout << endl;

    int n = promptUserForN();

    string word;
    Queue<string> q;
    Queue<string> first_q;
    Map<Queue<string>, Vector<string>> m;


    while (stream >> word) {
        if (q.size() < n-1) {
            q.enqueue(word);
            first_q.enqueue(word);
        }
        else {
            if (m.containsKey(q)) {m[q].add(word);}
            else {
                Vector<string> new_v;
                new_v.add(word);
                m[q] = new_v;
            }
            q.dequeue();
            q.enqueue(word);
        }
    }
    while (!first_q.isEmpty()){
        word = first_q.dequeue();
        if (m.containsKey(q)) {m[q].add(word);}
        else {
            Vector<string> new_v;
            new_v.add(word);
            m[q] = new_v;
        }
        q.dequeue();
        q.enqueue(word);
    }

    while (true) {
        cout << endl;
        int l = promptUserForL();
        if (l==0) break;
        string final;
        final = "...";
        q = m.keys()[randomInteger(0, m.size()-1)];
        Queue<string> q_copy;
        q_copy = q;
        while (!q.isEmpty()) {
            final += q.dequeue();
            final += " ";
        }
        for (int i = 0; i < l-n; i++) {
            string new_word = m[q_copy][randomInteger(0, m[q_copy].size()-1)];
            final += new_word;
            final += " ";
            q_copy.dequeue();
            q_copy.enqueue(new_word);
        }
        string new_word = m[q_copy][randomInteger(0, m[q_copy].size()-1)];
        final += new_word;
        final += "...";
        cout << final <<endl;
    }


    cout << "Exiting." << endl;
    return 0;
}

int promptUserForN(){
    string s;
    int n;
    while (true){
        s = getLine("Value of N?");
        try {
            n = stringToInteger(s);
            if (n >= 2) break;
            else { cout << "N must be 2 or greater." << endl;}
        } catch (...) {
            cout << "Illegal integer format. Try again." << endl;
        }
    }
    return n;
}

int promptUserForL(){
    string s;
    int n;
    while (true){
        s = getLine("# of random words to generate (0 to quit)?");
        try {
            n = stringToInteger(s);
            if (n == 0 || n >= 4) break;
            else { cout << "Must be at least 4 words." << endl;}
        } catch (...) {
            cout << "Illegal integer format. Try again." << endl;
        }
    }
    return n;
}
