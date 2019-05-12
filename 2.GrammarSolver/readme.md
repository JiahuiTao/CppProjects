This folder contains the code of generating random sentences from what linguists, programmers, and logicians refer to as a “grammar.” 

Let’s begin with some definitions. A formal language is a set of words and/or symbols along with a set of rules, collectively called the syntax of the language, that define how those symbols may be used together—programming languages like Java and C++ are formal languages, as are certain mathematical or logical notations. 

A grammar, in this context, is a way of describing the syntax and symbols of a formal language. All programming languages then have grammars.

This function accepts a reference to an input file representing a language’s grammar, along with a symbol to randomly generate, and the number of times to generate it. The function will generate the given number of random expansions of the given symbol and return them as a Vector of strings.
