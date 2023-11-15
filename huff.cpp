// THINGS TODO:
// 1.0 Need to open and read data from file
//  1.1: prompt user what file to open
//  1.2: open that file with a filestream object
//  1.3: create a new file with a '.huf. extenstion to write the compressed data
//  1.4: get the glyphs and freq from the data and put it in an array
// 2.0 writting to '.huf' file
//  2.1: get lenght of sourcefilename
//  2.2: write sourcefilename
//  2.3: write number of entries
//  2.4: write the huffman table (could be from an array)
//  2.5: write the compressed data
// 3.0 Huffman Table:
//  3.1 write merge algortim
//  3.2 write reheap algortim
//  3.3 put each node in the array
// 4.0:The compressed data:
//  4.1 IDK how to write the compressed data




#include <iostream>
#include <string>
#include <ctime>
#include<fstream>

using namespace std;

const int MAXTEXT = 80;
const int MAXCODE = 64;
const int MAXGLYPH = 257;
const int EOF_GLYPH = 256;

struct HuffTable
{
    int glyph;
    int frequency;
    int leftP;
    int rightP;
};

struct HUFFMANINFO {

};

struct FAKESTRING {
    char s{ MAXCODE };
};

typedef HUFFMANINFO HuffTable[2 + MAXGLYPH - 1];

typedef char BITSTRING[MAXGLYPH + 1];

HuffTable table;
CODETABLE code;

int glyphs;
char sourcefile[80];
char destfile[80];

ifstream source;
ofstream dest;

struct FileInformation 
{
    string fileName;
    int fileNameLength;
    double fileStreamLength;
    int glyphsInFile;
};

void CreateInitialTable() {

    int i;
    unsigned char buffer[MAXTEXT];

    for (i = 0; i <= MAXGLYPH; i++) {
        table[i].freq = 0;
        table[i].glyph = 0;
        table[i].left = 0;
        table[i].right = 0;
    }

    while (!source.eof()) {
        source.read((char*)buffer.MAXTEXT);
        for (i = 0; i < source.gcount(); i++) {
            table[buffer[i]].freq++
        }
        
    }

    table[EOF_GLYPH].freq = 1;

    Compact();
    SelectionSort();
}

void SelectionSort() {
    HuffTable temp;
    int i, j, small;

    for (i = 0; i <= (glyphs - 2); i++) {
        small = i;
        for(j = i +1, j<=(glyphs - 1); j++)
            if (table[j].freq < table[small].freq) {
                small = j;
            }
        temp = table[i];
        table[i] = small;
        table[small] = temp;
    }
}


void WriteTable() {
    int tableSize = 2 * glyphs - 1;
    dest.write((char*)&tablesize, sizeof(tableSize));

    for (int i = 0; i < tableSize; i++) {
        dest.write((char*)&table[i].glyph, sizeof(table[i].glyph));
        dest.write((char*)&table[i].left, sizeof(table[i].left));
        dest.write((char*)&table[i].right, sizeof(table[i].right));
    }
}


void EncodeFile() {

    unsigned char buffer[MAXTEST];
    int i;

    WriteTable();
    c = 0;
    p = 1;
    source.clear();
    source.seekg(0);
    
}

int main() {
    // get filename
    FileInformation newFile;
    cout << "Filename to compress: ";
    cin >> newFile.fileName;

    newFile.fileNameLength = sizeof(newFile.fileName);
    cout << newFile.fileNameLength << endl;
    


    // Length of sourcefilename, sourcefilename, and then number of huffman entries

    // 1. get freq and gl 4. yphs from file
    // 2. then sort array smallest to largest
    // 3. mark 'H' and 'M'
    // 4. follow instrucitons on canvas
    // 5. create reheap function to go through all entries to make sure the lowest are in 1 and 2
    // 6. crearte function to write each element in the array to the .huf file.
}
