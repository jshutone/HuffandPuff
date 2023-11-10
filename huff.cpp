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

using namespace std;

struct HuffTable
{
    int glyph;
    int frequency;
    int leftP;
    int rightP;
};

struct FileInformation 
{
    string fileName;
    int fileNameLength;
    double fileStreamLength;
    int glyphsInFile;
};



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
