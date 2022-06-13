// Eriksen Liu

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "huffman.hh"
#include "bitio.hh"

using namespace std;

int main(int argc, char **argv)
{
    ifstream input_file; // using ifstream to read date from a file
    Huffman huff;        // initialize a huffman instance
    int symbol;          // set types for symbol

    for (int i = 1; i < argc; ++i) // decode multiple files passed in the console
    {
        input_file.open(argv[i]); // opens the i-th file

        // create a new file to output the decoded file using ofstream
        const char *new_file = argv[i];
        const char *extension = ".plaintext";
        std::string fullname = new_file;
        fullname += extension;
        const char *actually_name = fullname.c_str();
        std::ofstream outfile(actually_name);

        // passing the compressed file as a parameter of BitInput in order to read bits from it
        BitInput biti(input_file);
        cout << "Decoding..." << endl;
        // while not eof()...
        while (!(input_file.eof()))
        {
            // decode the symbol
            symbol = huff.decode(biti.input_bit());
            // if symbol == eof, stopping write while
            if (symbol == Huffman::HEOF)
            {
                break;
            }
            // else, {if symbol exists, then put the symbol in the new file; else, keep looking for symbol.}
            else
            {
                if (symbol != -1)
                {
                    cout << char(symbol);
                    outfile.put(symbol);
                }
                symbol = -1;
            }
        }
        cout << endl;
        // indicates the plaintext file generated
        cout << "Done. A file " << actually_name << " has generated successfully." << endl;

        // close all files
        input_file.close();
        outfile.close();

        // analyze the sizes of both files to compare them using tellg() and seekg()
        cout << endl;
        streampos begin, end;
        ifstream myfile1(new_file, ios::binary);
        begin = myfile1.tellg();
        myfile1.seekg(0, ios::end);
        end = myfile1.tellg();
        myfile1.close();
        cout << "Size of compressed file (" << new_file << "): " << (end - begin) << " bytes.\n";

        ifstream myfile2(actually_name, ios::binary);
        begin = myfile2.tellg();
        myfile2.seekg(0, ios::end);
        end = myfile2.tellg();
        myfile2.close();
        cout << "Size of decompressed file (" << actually_name << "): " << (end - begin) << " bytes.\n";
    }
    return 0;
}
