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

inline bool EndsWith(string const & str, string const file_extension) {
	bool flag = false;
	if (str.size() < file_extension.size()) {
		return flag;
	}
	return 0 == str.compare(str.size() - file_extension.size(),
		file_extension.size(),
		file_extension,
		0,
		file_extension.size());
}

inline void AppendFileExtension(string & input_file_name, string const file_extension)
{
	if (!EndsWith(input_file_name, file_extension)) {
		input_file_name = RemoveFileExtension(input_file_name);
		input_file_name += ".huf";
	}
}

inline string RemoveFileExtension(const string & filename)
{
	size_t last_dot = filename.find_last_of(".");
	if (last_dot == std::string::npos) {
		return filename;
	}
	return filename.substr(0, last_dot);
}

void BubbleSort(HuffTableEntry huff_table[],int n)
{
	bool did_swap = true;
	int num_pairs = n;
	HuffTableEntry temp;
	while (did_swap) {
		num_pairs--;
		did_swap = false;
		for (int index = 0; index < num_pairs; index++) {
			if (huff_table[index].frequency > huff_table[index + 1].frequency) {
				temp = huff_table[index];
				huff_table[index] = huff_table[index + 1];
				huff_table[index + 1] = temp;
				did_swap = true;
			}
		}
	}
}

void CreateHuffmanTable(HuffTableEntry frequency_table[], int length)
{
	int h = length - 1;
	int f = length;
	int m;

	do {
		if (h >= 2) {
			m = MarkM(frequency_table, 1, 2);
		}
		else if (h >= 1) {
			m = 1;
		}
		swap(frequency_table[m], frequency_table[f]);

		if (m < h) {
			swap(frequency_table[m], frequency_table[h]);
		}
		Reheap(frequency_table, m, h);

		swap(frequency_table[0], frequency_table[h]);

		// Create a new frequency node
		frequency_table[0].glyph = -1;
		frequency_table[0].frequency = frequency_table[h].frequency + frequency_table[f].frequency;
		frequency_table[0].left = h;
		frequency_table[0].right = f;

		Reheap(frequency_table, 0, h);

		h--;
		f++;
	} while (f != 2 * length - 1); 

}

inline int MarkM(HuffTableEntry table[], const int slot_one, const int slot_two)
{
	if (table[slot_one].frequency <= table[slot_two].frequency) {
		return slot_one;
	}
	else {
		return slot_two;
	}
}

void Reheap(HuffTableEntry frequency_table[], int m, int h)
{
	int head = (m - 1) / 2;
	int left_child = (m * 2) + 1;
	int right_child = (m * 2) + 2;
	if (m >= h || h == 1) {
		return;
	}
	if (frequency_table[head].frequency > frequency_table[m].frequency) {
		swap(frequency_table[head], frequency_table[m]);
		if (m != 0) {
			Reheap(frequency_table, head, h);
		}
	}
	else {
		if (right_child < h) {
			if (frequency_table[m].frequency > frequency_table[left_child].frequency &&
				frequency_table[m].frequency > frequency_table[right_child].frequency) {
				if (frequency_table[left_child].frequency <= frequency_table[right_child].frequency) {
					swap(frequency_table[m], frequency_table[left_child]);
					Reheap(frequency_table, left_child, h);
				}
				else {
					swap(frequency_table[m], frequency_table[right_child]);
					Reheap(frequency_table, right_child, h);
				}
			}
			else if (frequency_table[m].frequency > frequency_table[left_child].frequency ||
				frequency_table[m].frequency > frequency_table[right_child].frequency) {
				int minimum = MarkM(frequency_table, left_child, right_child);
				swap(frequency_table[m], frequency_table[minimum]);
				Reheap(frequency_table, minimum, h);
			}
		}
		else if (left_child < h) {
			if (frequency_table[m].frequency > frequency_table[left_child].frequency) {
				swap(frequency_table[m], frequency_table[left_child]);
			}
		}
	}
}

inline void GetCodes(HuffTableEntry frequency_table[], HuffTableEntry node, string& code, string bitcodes[]) {
	if (node.glyph != -1) {
		bitcodes[node.glyph] = code;
	}
	else {
		if (node.left != -1) {
			code.append("0");
			GetCodes(frequency_table, frequency_table[node.left], code, bitcodes);
			code.erase(code.size() - 1, 1);
		}
		if (node.right != -1) {
			code.append("1");
			GetCodes(frequency_table, frequency_table[node.right], code, bitcodes);
			code.erase(code.size() - 1, 1);
		}
	}
}