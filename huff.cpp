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
