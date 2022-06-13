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
    ifstream input_file; // using ifstream to read character from a file
    Huffman hfm;
    for (int i = 1; i < argc; ++i) // encoding multiple files passing from the console
    {
        input_file.open(argv[i]); // opens the i-th file

        // initialize a binary file by adding .comp to the original file using ofstream
        const char *new_file = argv[i];
        const char *extension = ".comp";
        std::string fullname = new_file;
        fullname += extension;
        const char *actually_name = fullname.c_str();
        std::ofstream outfile(actually_name);

        // passing the .comp file to bito in order to write bit one at a time into the file
        BitOutput bito(outfile);

        if (!input_file)
        { // file couldn't be opened
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }

        cout << "Reading and encoding..." << endl;
        // while not eof()
        while (!input_file.eof())
        {
            // getting character from the file
            char c = input_file.get();
            // if equal to eof()
            if (int(c) == -1)
            {
                //  encode with 256 as the Huffman::HEOF
                for (const auto &e : hfm.encode(256))
                {
                    // iterate the bool value of hfm.encode(int(c)) as it returns a vector with bool in it.
                    bito.output_bit(e);
                }
            }
            // else,
            else
            {
                // encode the character from its ascii number
                cout << c;
                for (const auto &e : hfm.encode(int(c)))
                {
                    // iterate the bool value of hfm.encode(int(c)) as it returns a vector with bool in it.
                    bito.output_bit(e);
                }
            }
        }
        cout << endl;
        // indicates that the compression works well
        cout << "Done. A file " << actually_name << " has generated successfully." << endl;
        // flush the extra bits into the output filer
        bito.~BitOutput();

        // close both files
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
        cout << "Size of original file (" << new_file << "): " << (end - begin) << " bytes.\n";

        ifstream myfile2(actually_name, ios::binary);
        begin = myfile2.tellg();
        myfile2.seekg(0, ios::end);
        end = myfile2.tellg();
        myfile2.close();
        cout << "Size of compressed file (" << actually_name << "): " << (end - begin) << " bytes.\n";
    }
    return 0;
}