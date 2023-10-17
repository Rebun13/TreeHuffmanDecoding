# TreeHuffmanDecoding

## Description

Huffman coding assigns variable length codewords to fixed length input characters based on their frequencies. More frequent characters are assigned shorter codewords and less frequent characters are assigned longer codewords. All edges along the path to a character contain a code digit. If they are on the left side of the tree, they will be a 0 (zero). If on the right, they'll be a 1 (one). Only the leaves will contain a letter and its frequency count. All other nodes will contain a null instead of a character, and the count of the frequency of all of it and its descendant characters.

## Output

- Output the decoded string on a single line.

## Input

- There is one line of input containing the plain string, _s_. Background code creates the Huffman tree then passes the head node and the encoded string to the function.
