#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX 100
#define DELIM "," // CSV delimiter

char *ifile, *ofile;
unsigned filter_age_max;
FILE *istream, *ostream;

const char USAGE[] =
    "Filters CSV rows, keeping only those with provided maximum age\n"
    "%1$s max-age [input-file] [output-file]\n"
    "\n"
    "Example: \n"
    "%1$s max-age 17 input.csv output.csv\n"
    "%1$s max-age 10 input.csv (outputs to stdout)\n"
    "%1$s max-age 54           (inputs from stdin, outputs to stdout)\n";

void filter_stream(FILE *istream, FILE *ostream) {
  char line[LINE_MAX];
  char *fgets_return;
  char *name, *age_str;
  size_t line_no = 0;
// read the lines from the input stream untill it has reached the EOF
  while ((fgets_return = fgets(line, LINE_MAX, istream)) != NULL) {
    ++line_no;
// running a if loop to check is the line from the input stream is empty
    if (fgets_return && *fgets_return != '\n') {
      if (strlen(line) > 1) {
        // Assign `name` and `age_str` using `strtok`
        // YOUR CODE HERE
        // creating two different tokens, one for the name read from the input stream
        // and on for the age read from the input stream
name = strtok(fgets_return, DELIM);
age_str = strtok(NULL, "\n");
        // Alternative to strtok:
        // sscanf(line, "%*[^,],%d", &age);

        if (!age_str) {
          // Error message
          // YOUR CODE HERE
          // prints a error message to the terminal if there is no age token
    printf("There is no age assigned to the line,\n");
    printf("is has therefore been skipped\n");
          continue;
        }
      }
    } else {
      // Error message
      // YOUR CODE HERE
      // pritns a message to the terminal if no token was created
      printf("This line is empty or there was a error reading it, and it has\n");
      printf("therefore been skipped\n");
      continue;
    }

    // Age processing
    unsigned age;
    int recognized_count = sscanf(age_str, "%d", &age);
    if (recognized_count == 1) {
      if (age <= filter_age_max) {
        // Forward input line to `ostream`
        // YOUR CODE HERE
        // prints out the name and age token if the age is within the 
        // user provided age limit, it prints it out to the given output stream
        fprintf(ostream, "%s,%s\n", name, age_str);
      }
    } else {
      // Error message
      // YOUR CODE HERE
      // pritns a error message if the age tokens are outside of the user scope
      printf("The age is outside of the scope you wanted\n");
    }
  }
}

int main(int argc, char *argv[]) {
  switch (argc) {
  case 4:
    // max-age ifile ofile
    ofile = argv[3];
  case 3:
    // max-age ifile
    ifile = argv[2];
  case 2:
    // max-age
    if (!sscanf(argv[1], "%d", &filter_age_max)) {
      puts("First argument is not an age.");
      exit(EXIT_FAILURE);
    }
    break;
  default:
    printf(USAGE, argv[0]);
    return EXIT_SUCCESS;
  }

  if (ifile) {
    // Open `ifile` and assign it to `istream`
    // YOUR CODE HERE
    // opens the input file given in reading mode
istream = fopen(ifile, "r");
    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
    // if no input file is provided or if there is a error opening it
    // then it will print out a error message to the terminal and exit
    if (istream == NULL) {
        printf("Unable to open the file \n");
        return 1;
    }
  } else {
    // Set `istream` if no file provided
    // YOUR CODE HERE
    ifile="src/ifile.csv"; // making the csv file provided a default
    // so that is program is easier to test
    // opens the provided user input file in reading mode
    istream = fopen(ifile, "r");
    if (istream == NULL) {
        printf("There was a error with the inputted file\n");
        return 1;
    }
  }

  if (ofile) {
    // Open `ofile` and assign it to `ostream`
    // YOUR CODE HERE
    // open the output file in writing mode
ostream = fopen(ofile, "w");
    // Exit program with an error message if file cannot be opened
    // YOUR CODE HERE
    // if there is a error opening the ouput file it will print out a 
    // error message to the terminal and exit
    if (ostream == NULL) {
        printf("unable to open file\n");
        return 1;
    }
  } else {
    // Set `ostream` if no file provided
    // YOUR CODE HERE
    // creates a dafault output file called ofile.csv
    // also tells the user where that output file is located and its name
    // 
    printf("The content from the CSV input file has been outputted to src/ofile.csv\n");
    printf("because you failed to provide an output file\n");
    // opens the output file in writing mode
    ostream = fopen("src/ofile.csv", "w");
    if (ostream == NULL) {
        printf("Unable to create the output file\n");
        return 1;
    }
  }
  
  filter_stream(istream, ostream);
  // close the input and output streams since the program is finished
  fclose(istream);
  fclose(ostream);
}