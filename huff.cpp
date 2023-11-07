#include <iostream>


using namespace std;



struct HuffTable
{
    int glyph = -1;
    int frequency = 0;
    int leftP = -1;
    int rightP = -1;
};

struct FileInformation 
{
    string fileName;
    int fileNameLength;
    ifstream fileStream;
    double fileStreamLength;
    int glyphsInFile;
};



int main() {
    cout << "Hello, world" << endl;
}