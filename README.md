CENSOR ver 1.0 1/4/2019

Copies a text file into another text file, while removing any "dirty words" provided through regular expressions in a config file.

Compiling/Building:
Censor is compiled using gcc. Use the "make" command to get a runnable program.

Running:
Censor takes 3 command line arguments. First argument is a text file for input (what you plan to censor), second is a text configuration file with regular expressions separated by newline, and third is the name of the file you want to output your result to.

Example:
./censor inputfile.txt configfile.txt outputfile.txt
