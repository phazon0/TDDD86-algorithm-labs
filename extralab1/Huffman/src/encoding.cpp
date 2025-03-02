#include "encoding.h"
#include "queue"

/**
 * @brief buildFrequencyTable
 * Reads the file one byte at a time and inputs the frequency of a byte
 *
 * @param input
 * insput stream of input file
 *
 * @return
 * map with key of byte and value is number of occurences
 *
 */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;

    int currentByte;
    while((currentByte = input.get()) != EOF){
        unsigned char unsignedByte = (unsigned char)currentByte;
        auto ins = freqTable.insert(make_pair(unsignedByte, 1));
        if (!ins.second) {
            ins.first->second++;
        }
    }

    freqTable[PSEUDO_EOF] = 1;

    return freqTable;
}

/**
 * @brief buildEncodingTree
 * Generates a tree by implementing a max heap
 * Uses huffman encoding algorithm described in OpenDSA
 *
 * @param freqTable
 * Frequence table of each byte and its frequence
 *
 * @return
 * Root node in the huffman tree
 */
HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    std::priority_queue<HuffmanNode> nodes;
    for (pair<int, int> element : freqTable){
        auto node = HuffmanNode(element.first, element.second, nullptr, nullptr);
        nodes.push(node);
    }
    while(nodes.size()!=1){
        //Builds the huffmanTree
        HuffmanNode left = nodes.top();
        nodes.pop();
        HuffmanNode right= nodes.top();
        nodes.pop();
        int weight = left.count + right.count;
        auto node = HuffmanNode(NOT_A_CHAR, weight, new HuffmanNode(left), new HuffmanNode(right));
        nodes.push(node);
    }
    auto node = nodes.top();
    return new HuffmanNode(node);
}

/**
 * @brief traverseTree
 * Traverses tree recrusively. If node is leaf, assigns path value to character as key. First checks left child then right.
 *
 * @param current
 * Current huffman node, starts at root
 *
 * @param path
 * Current path to the current node, from root node
 *
 * @param encodingMap
 * Encoding map for storing the path to different characters from the huffman tree.
 */
void traverseTree(HuffmanNode* current, const string& path, map<int, string>& encodingMap){
    if(current == nullptr) return;

    if(current->isLeaf()){
        encodingMap[current->character] = path;
        return;
    }
    //go left first
    traverseTree(current->zero, path+"0", encodingMap);
    //go right after
    traverseTree(current->one, path+"1", encodingMap);

}

/**
 * @brief buildEncodingMap
 * Creates an encoding map for huffman tree by traversing it using traverseTree()
 *
 * @param encodingTree
 * Root node of the huffman tree
 *
 * @return
 * Encoding map with key character and value is path encoded as string
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;

    traverseTree(encodingTree, "", encodingMap);
    return encodingMap;
}

/**
 * @brief encodeData
 * Reads an input file, byte for byte and obtains their path using the encodingMap then writes this bit sequence to output bit stream
 *
 * @param input
 * Input byte stream that of which bytes are to be encoded
 *
 * @param encodingMap
 * Encoding map used for encoding bytes to bit sequences
 *
 * @param output
 * Output bit stream, writes bit by bit to output.
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int currentByte;
    while ((currentByte = input.get()) != EOF) {
        unsigned char byteValue = (unsigned char)currentByte;
        const string& encoding = encodingMap.at(byteValue);

        for (char bit : encoding) {
            output.writeBit(bit == '1');
        }
    }
    const string& encodeEOF = encodingMap.at(PSEUDO_EOF);
        for (char bit : encodeEOF) {
            output.writeBit(bit == '1');
        }
}

/**
 * @brief decodeData
 * Decodes data that is encoded by our huffman encoding algorithm.
 * Reads bit by bit until it reaches a leaf in our encodingTree. If leaf contains character PSEUDO EOF, reading breaks.
 *
 * @param input
 * Input bit stream, streams one bit at a time
 *
 * @param encodingTree
 * Root node of our encoding tree
 *
 * @param output
 * Output stream
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* current = encodingTree;
    while(true){
          bool bit = input.readBit();
          if(bit){
              current = current->one;
          }else{
              current = current->zero;
          }
          if(current->isLeaf()){
              if(current->character == PSEUDO_EOF)
                  break;
            output.put(current->character);
            current = encodingTree;
          }
    }
}

/**
 * @brief compress
 * Method for compressing a input file into an output file
 * This is done by first obtaining the frequence table, then writing the size of the freqTable to the output
 * then writing each entry into the output file (key then value)
 *
 * Then by generating the encoding tree and encoding map, we use encodeData method to write the encoded data.
 *
 * @param input
 * input stream which in our case is input file
 *
 * @param output
 * output bit stream which for our case is output file
 */
void compress(istream& input, obitstream& output) {

    map<int, int> freqTable = buildFrequencyTable(input);
    size_t size = freqTable.size();
    output.write(reinterpret_cast<const char*>(&size), sizeof(size_t));


    for(auto entry : freqTable){
        output.write(reinterpret_cast<const char*>(&entry.first), sizeof(int));
        output.write(reinterpret_cast<const char*>(&entry.second),sizeof(int));
    }




    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    //remove flags and stuff and go to start of input file
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);


}

/**
 * @brief decompress
 * Method for decompressing files that have been compressed using our implementation of huffman encoding algorithm.
 * This is done by first reading the frequence table size then obtaining all the used bytes and their frequency.
 * An encoding tree is then constructed and used to call decodeData method.
 *
 * @param input
 * Input bit stream which in our case is input file
 *
 * @param output
 * Output bit stream which in our case is output file
 */
void decompress(ibitstream& input, ostream& output) {
    size_t freqTableSize;
    input.read(reinterpret_cast<char*>(&freqTableSize), sizeof(size_t));

    map<int, int> freqTable;
    for(size_t i = 0; i<freqTableSize; ++i){
        int character, value;
        input.read(reinterpret_cast<char*>(&character), sizeof(int));
        input.read(reinterpret_cast<char*>(&value), sizeof(int));
        freqTable[character] = value;
    }


    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

/**
 * @brief freeTree
 * Post order traverses the huffman tree recursively and deletes the nodes from the heap.
 *
 * @param node
 * Current node
 */
void freeTree(HuffmanNode* node) {
    if(node == nullptr){
        return;
    }

    freeTree(node->zero);
    freeTree(node->one);

    delete node;

}
