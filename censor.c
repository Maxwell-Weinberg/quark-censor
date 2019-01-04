/* Copies a file with the exception of undesired words */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#define MAX_WORD_LENGTH 81

/* Opens a file and returns a file pointer. Exits the program if the file is unavailable.
Filename is a string of the file's name.
rwa is to specify the type of I/O. r = read, w = write */
FILE *open(char *filename, char *rwa) {
  FILE *fp;
  if ((fp = fopen(filename, rwa)) == NULL) {
    printf("Cannot open %s for %s.\n", filename, rwa);
    exit(1);
  }
  return fp;
}

int main (int argc, char *argv[]) {
  
  char *input = argv[1];
  char *config = argv[2];
  char *output = argv[3];
  char word[MAX_WORD_LENGTH]; //temporarily holds strings
  char c = ' '; //used to read file char by char
  FILE *open(char *filename, char *rwa);
  FILE *inp, *conp, *outp;//file pointers for input, config, and output
  regex_t regex; //temporary holds regular expressions
  regex_t *reg; //array of regular expression for dirty words
  int reti; //Indicator of successful regex compilation and for regex matches
  int rcount = 0; //Number of regular expressions found in config
  int wi = 0; //word iterator
  int ri = 0; //reg iterator

  inp = open (input, "r");
  conp = open(config, "r");
  outp = open(output, "w");

  /* Counts the number of newline characters in config to determine how many regular expressions we are testing */
  while (fscanf(conp, "%80s", word) != EOF) {
    rcount++;
  }
  fclose(conp);

  //allocate space for array of regular expressions
  reg = (regex_t *)calloc(sizeof(regex_t), rcount);

  //Places regular expressions from config into reg
  conp = open(config, "r");
  while (fscanf(conp, "%80s", word) != EOF) {
    reti = regcomp(&regex, word, 0);
    if (reti) {
      printf("Could not compile regex: %s\n", word);
      exit(1);
    }
    reg[ri] = regex;
    ri++;
  }

  c = ' '; //resets c
  while (c != EOF) {
    c = getc(inp);
    if (c == ' '|| c == '\n' || wi == MAX_WORD_LENGTH-1) {
      word[wi] = '\0'; //Null terminate our word
      for (ri = 0; ri < rcount; ri++) { //checks our word against reg
	reti = regexec(&reg[ri], word, 0, NULL, 0);
	if (!reti) { //a regular expression matched
	  break;
	}
	
      }
      if (reti && wi) { //no match and word is at least 1 character
	fputs(word, outp);
      }
      putc(c, outp);
      wi = 0;
    } else { //have not reached whitespace yet
      word[wi] = c;
      wi++;
    }
  }
  
  free(reg);
  fclose(inp);
  fclose(conp);
  fclose(outp);
  printf("File has been copied.\n");
  return 0;
}

