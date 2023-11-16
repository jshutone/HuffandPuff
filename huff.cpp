#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::hex;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::pow;
using std::setfill;
using std::setw;
using std::streamsize;
using std::string;
using std::swap;
using std::uppercase;
using std::setprecision;
using std::fixed;
// Functions taken from: https://stackoverflow.com/questions/25706991/appending-a-file-extension-in-a-c-progam
bool EndsWith(string const &, string const);
void AppendFileExtension(string & str, string const suffix);
// Function taken from: https://stackoverflow.com/questions/6417817/easy-way-to-remove-extension-from-a-filename
string RemoveFileExtension(const string& filename);

struct HuffTableEntry {
	int glyph;
	int left;
	int right;
	int frequency;
};

void BubbleSort(HuffTableEntry[], int);
void CreateHuffmanTable(HuffTableEntry[], int);
void GetCodes(HuffTableEntry frequency_table[], HuffTableEntry node, string& code, string codes[]);
int MarkM(HuffTableEntry[], const int, const int);
void Reheap(HuffTableEntry[], int, int);

int main() {
	int length_of_file_name;
	string input_file_name;
	string output_file_name;
    clock_t start, end;
	cout << "Please enter a file name: ";
	getline(cin, input_file_name);
	output_file_name = input_file_name;
	length_of_file_name = input_file_name.length();
	ifstream fin(input_file_name, ios::in | ios::binary);

	AppendFileExtension(output_file_name, ".huf");
	ofstream out(output_file_name, ios::out | ios::binary  );

    //Start timer
    start = clock();

	int glyph_frequency[257] = {0};
	unsigned char input;
	while (fin.read((char*)&input, 1)) {
		glyph_frequency[input]++;
	}
	glyph_frequency[256] = 1; // End of file frequency.

	HuffTableEntry frequency_table[513];
	int index = 0;
	for (int i = 0; i < 257; i++) {
		if (glyph_frequency[i] != 0) {
			frequency_table[index].glyph = i;
			frequency_table[index].frequency = glyph_frequency[i];
			frequency_table[index].left = -1;
			frequency_table[index].right = -1;
			index++;
		}
	}
	int length = index;
	// Sort the frequency table.
	BubbleSort(frequency_table, length);

	CreateHuffmanTable(frequency_table, length);

	//generate Huffman codes
	string bitcodes[257] = { "" };
	string code = "";
	GetCodes(frequency_table, frequency_table[0], code, bitcodes);

	//write the header data (length of filename, filename, #huffman entries, huffman table)
	int numEntries = (length * 2) - 1;

	out.write((char *) &length_of_file_name, sizeof(length_of_file_name));
	out.write(input_file_name.c_str(), length_of_file_name);
	out.write((char *) &numEntries, sizeof(numEntries));

	for (int i = 0; i < numEntries; i++) {
		out.write((char *) &frequency_table[i].glyph, sizeof(frequency_table[i].glyph));
		out.write((char *) &frequency_table[i].left, sizeof(frequency_table[i].left));
		out.write((char *) &frequency_table[i].right, sizeof(frequency_table[i].right));
	}

	fin.clear();
	fin.seekg(0, fin.beg);

	int bitstring_length;
	int count = 0;
	string bitstring;
	unsigned char input_byte[1];
	unsigned char output_byte = '\0';
	while (fin.read((char *)&input_byte, sizeof(output_byte))) {
	 bitstring = bitcodes[input_byte[0]];
		//encode the byte, write it out one byte at a time
		bitstring_length = bitstring.length();
		for (int i = 0; i < bitstring_length; i++) {
			if (bitstring[i] == '1') {
				output_byte = output_byte | (int)pow(2.0, count);
			}
			count++;
			if (count == 8) {
				//write the byte out to file
				out.write((char *)&output_byte, sizeof(output_byte));
				//reset the byte
				output_byte = '\0';
				count = 0;
			}
		}
	}
	
	bitstring = bitcodes[256];
	bitstring_length = bitstring.length();
	for (int i = 0; i < bitstring_length; i++) {
		if (bitstring[i] == '1') {
			output_byte = output_byte | (int)pow(2.0, count);
		}
		count++;
		if (count == 8) {
			//write the byte out to file
			out.write((char *) &output_byte, sizeof(output_byte));
			//reset the byte
			output_byte = '\0';
			count = 0;
		}
	}

	if(count != 0){
		//write out byte even if not full
		out.write((char *)&output_byte, sizeof(output_byte));
	}

	//close the files
	fin.close();
	out.close();

    end = clock();
    cout << setprecision(5) << fixed;
    cout << "The time was " << (double(end - start) / CLOCKS_PER_SEC) <<
        " seconds." << endl;
}
