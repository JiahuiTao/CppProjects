#include "encoding.h"

Map<int, int> buildFrequencyTable(istream& input) {   
    Map<int, int> freqTable;
    int c = input.get();;
    while(c!= -1){
        if (freqTable.containsKey(c)){
            freqTable[c] +=1;
        }
        else {
            freqTable[c] = 1;
        }
        c = input.get();
    }
    freqTable[PSEUDO_EOF] = 1;
    return freqTable;
}


HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pqueue;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* newNode;
    for (int key:freqTable.keys()){
        newNode = new HuffmanNode {key, freqTable[key]};
        pqueue.enqueue(newNode, newNode->count);
    }
    while(pqueue.size() > 1){
        left = pqueue.dequeue();
        right = pqueue.dequeue();
        newNode = new HuffmanNode {NOT_A_CHAR, left->count + right->count, left, right};
        pqueue.enqueue(newNode, newNode->count);
    }
    HuffmanNode* result = pqueue.dequeue();
    return result;
}

void getEncoding(HuffmanNode* encodingTree, Map<int, string>& encodingMap, string code){
    if(encodingTree->character != NOT_A_CHAR){
        encodingMap[encodingTree->character] = code;
        return;
    }
    getEncoding(encodingTree->zero, encodingMap, code+'0');
    getEncoding(encodingTree->one, encodingMap, code+'1');
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    string code;
    getEncoding(encodingTree, encodingMap, code);
    return encodingMap;
}

void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    while (true){
        int c = input.get();
        if (c == -1){
            c = PSEUDO_EOF;
        }
        string code = encodingMap[c];
        for (char i:code){
            if (i == '0'){
                output.writeBit(0);
            }
            else if (i=='1'){
                output.writeBit(1);
            }

        }
        if (c == PSEUDO_EOF){
            return;
        }
    }
}

int getDecoding(ibitstream& input, HuffmanNode* encodingTree){
    if(encodingTree->character != NOT_A_CHAR){return encodingTree->character;}
    int b = input.readBit();
    if(b==0){return getDecoding(input, encodingTree->zero);}
    else {return getDecoding(input, encodingTree->one);}
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    while(true){
        int c = getDecoding(input, encodingTree);
        if (c==PSEUDO_EOF){return;}
        output.put(c);
    }
}

Map<int, int> buildFrequencyTable(istream& input);
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable);
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree);
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output);
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);

void compress(istream& input, obitstream& output) {
    Map<int, int> freqTable = buildFrequencyTable(input);
    output << freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    Map<int, string> encodingMap = buildEncodingMap(encodingTree);\
    rewindStream(input);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);
}

void decompress(ibitstream& input, ostream& output) {
    Map<int, int> freqTable;
    input >> freqTable;
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) {
    if (node == nullptr){return;}
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}
