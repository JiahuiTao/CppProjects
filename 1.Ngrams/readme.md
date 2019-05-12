This folder contains the source code of a program that takes in a text file and then (randomly) generates new text in the same style. 

The program accomplishes the task of imitating a text’s style by building and relying on a large data structure of word groups called "N-grams." A collection of N-grams will serve as the basis for the program to randomly generate new text that sounds like it came from the same author as the input file.

What, you may ask, is an N-gram? If you make a collection of all groups of N-1 words along with their possible following words, you can use this to select an Nth word given the preceding N-1 words. The higher your choice of N, the more similar the new random text will be to the original data source. 
