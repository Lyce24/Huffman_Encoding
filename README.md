Partners with Ella Ngo  
# overall Idea
Putting a file into encoder.cc, we allow the program to get each character in the file until we meet eof. With each character, we use the huffman encoding to encode it based on its frequency. The more frequent the character appears, the shorter the encoding will be. And then we create a new binary file and use bitio to write each bit into the file. We give the name of the new file as .comp.  
Then we put the .comp file as an input for BitInput, using the input_bit() method, we are able to get every bit of the file. Then passing the bit to huffman decode method to decode .comp file, we can get the original characters. Then we can output the characters we got into a new file as .comp.plaintext file, which should be identical as the original one.
The size of .comp is smaller than the original file, which can be seen as a compressed file of the original file. With the decoder, we can decode the compressed file to original file.

# huffman.cc
Basically creating an algorithm to construct a huffman tree based on certain frequency table and input. And with the codes we got from the encoding method, we are able to decode it to get original characters with decode method. All the codes are explained in the huffman.cc file.

# bitio.cc
Allowing users to read and write bits to a file or stream one at a time. All the codes are explained in the bitio.cc file.

# encoder.cc
Get each character in the file and encode all the characters with huffman encoding from huffman.cc, then write the codes from the encoding into a new compressed binary file.

# decoder.cc
Get every bit of the new compressed and pass that bit to the decoding method of huffman class. With the construction of the decoding method, we are able to get every character from the original file. Then create a new file which allows us to pass the characters we got from the decoding into the new file using put(). Finally, return the sizes of the compressed file and the decompressed file (original file).

# How to construct encoder and decoder
Firstly, enter the following codes in the command-line:  
g++ -g -std\==c++2a htree.cc hforest.cc huffman.cc bitio.cc encoder.cc -o encoder  
g++ -g -std\==c++2a htree.cc hforest.cc huffman.cc bitio.cc decoder.cc -o decoder  
./encoder filename.type  
./decoder filename.type.comp  
  
After these codes, you will find the sizes of original file and compressed file as printed in the console.  

# Test Result
I didn't change the test codes given. All tests in the test_huffman.cc and test_bitio.cc are passed.  

|    File name    | Raw file size in bytes (before compression) | Compressed file size in bytes. | Decompressed file matches raw file exactly (yes/no). |
| :--------------- | :-----------------------------------------: | :----------------------------: | ---------------------------------------------------: |
|   kobe.txt      |                 1708 bytes                  |           1029 bytes            |                                                  Yes |
|   decoder.cc    |                 1995 bytes                  |           1187 bytes           |                                                  Yes |
|    main.tex     |                 5071 bytes                  |           3256 bytes            |                                                  Yes |
| instruction.txt |                 1534 bytes                  |           1009 bytes           |                                                  Yes |
|    linux.txt    |                  421 bytes                  |           244 bytes            |                                                  Yes |
|    apple.txt    |                  531 bytes                  |           188 bytes            |                                                  Yes |


I used cmp to check each decompressed file and original file. All six files pass the test.