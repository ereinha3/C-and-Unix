#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/* Since the largest number is 4294967295, we need 11 characters (including the 
   null character) to read a number from the file */
#define MAX_NUM_LENGTH 12


/* This function checks the number of input parameters to the program to make 
   sure it is correct. If the number of input parameters is incorrect, it 
   prints out a message on how to properly use the program.
   input parameters:
       int    argc
       char** argv 
    return parameters:
       none
 */
void usage(int argc, char** argv)
{
    if(argc < 4) {
        fprintf(stderr, 
                "usage: %s <input file 1> <input file 2> <output file>\n", 
                argv[0]);
        exit(EXIT_FAILURE);
    }
}


/* This function takes in the two input file names (stored in argv) and
   determines the number of integers in each file.
   If the two files both have N integers, return N, otherwise return -1.
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char** argv
   return parameters:
       -1 if the two input files have different number of integers 
       N  if the two input files both have N integers
 */
int get_num_ints(char** argv)
{
	int len1 = 0;
	int len2 = 0;
	char buffer[MAX_NUM_LENGTH];
	FILE *fp1;
	fp1 = fopen(argv[1], "r");
	FILE *fp2;
	fp2 = fopen(argv[2], "r");
	if (fp1 == NULL || fp2==NULL) {
		fclose(fp1);
		fclose(fp2);
		exit(EXIT_FAILURE);
	}
	while (fgets(buffer, MAX_NUM_LENGTH, fp1)) {
		len1++;
	}
	fclose(fp1);
	while (fgets(buffer, MAX_NUM_LENGTH, fp2)) {
		len2++;
	}
	fclose(fp2);
	if (len2 == len1) {		
		return len1;
	}
	else {
		return -1;
	}
}


/* This function allocates engough memory to the three arrays to store
   num_ints elements each.
   This function should exit with EXIT_FAILURE if the program fails to allocate
   the memory.
   input parameters:
       unsigned int*      input_one
       unsigned int*      input_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void allocate_mem(unsigned int** input_one, unsigned int** input_two, 
                  unsigned long int** output, int num_ints)
{
	*input_one = malloc(sizeof(unsigned int)*num_ints);
	*input_two = malloc(sizeof(unsigned int)*num_ints);
	*output = malloc(sizeof(unsigned long int)*num_ints);
	if (input_one == NULL || input_two == NULL || output == NULL) {
		free(*input_one);
		free(*input_two);
		free(*output);
		exit(EXIT_FAILURE);
	}
}



/* This function reads in num_ints integers from the two input files and 
   stores them in input_one (first input file) and input_two (second input
   file).
   If one or both of the files do not exist, it should exit with EXIT_FAILURE.
   input parameters:
       char**        argv
       unsigned int* input_one
       unsigned int* input_two
       int           num_ints
   return parameters:
       none

 */
void get_ints(char** argv, unsigned int* input_one, unsigned int* input_two,
              unsigned long int* output, int num_ints)
{
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");
	if (fp1 == NULL || fp2==NULL) {
		fclose(fp1);
		fclose(fp2);
		exit(EXIT_FAILURE);
	}
	char buffer[MAX_NUM_LENGTH];
	int index = 0;
	while (fgets(buffer, MAX_NUM_LENGTH, fp1)) {
		input_one[index] = (unsigned int)atoi(buffer);
		index++;
	}
	index = 0;
	while (fgets(buffer, MAX_NUM_LENGTH, fp2)) {
		input_two[index] = (unsigned int)atoi(buffer);
		index++;
	}
	fclose(fp1);
	fclose(fp2);
}

/* This function does an element-wise addition between the two input arrays 
   (input_one and input_two) of size num_ints and stores the result in the 
   output array (output).
   input parameters:
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void sum_ints(unsigned int* input_one, unsigned int* input_two, 
              unsigned long int* output, int num_ints)
{
	for (int i = 0; i<num_ints; i++) {
		output[i] = (unsigned long int)(input_one[i]) +(unsigned long int)(input_two[i]);
	}
}

/* This function saves the summed output to an output file, whose name was 
   specified with the program execution (i.e., argv[3]).
   The file should containe one integer value per line, similarly to how the
   input files were stored.
   input parameters:
       char**             argv
       unsigned int*      intput_one
       unsigned int*      intput_two
       unsigned long int* output
       int                num_ints
   return parameters:
       none
 */
void save_output(char** argv, unsigned int* input_one, unsigned int* input_two,
                 unsigned long int* output, int num_ints)
{
	FILE *fp = fopen(argv[3], "w");
	for (int i = 0; i<num_ints; i++) {
		fprintf(fp, "%ld\n", output[i]);
	}
	fclose(fp);

}

/* This program takes in three text file names as input. 
   The first two files contain N integers (where N >=0 and N <= 1,000,000)
   whose values range from 0 to 4294967295 (i.e., 32-bit unsigned integers).
   The last file is the output file that this program should generate.
   For all three files, there should be one integer per line.
  
   For each line in the two input files, read in the two integers, add them, and
   then store the sum in the output file.
   Repeat this process until all integers have been read from the input files.

   For example, if the two input files have eight integerse each
   input file 1		input file 2		output file
   --------------------------------------------------------
   1			2			3
   5			2			7
   8			5			13
   1			12			13
   2			2			4
   10			2			12
   1991			2			1993
   11231245		21235			11252480
 */
int main(int argc, char** argv)
{
    usage(argc, argv);

    // Check the number of integers in the input files
    int num_ints = get_num_ints(argv);
    if(num_ints == -1) {
        fprintf(stderr, "ERR: The two input files have different # of ints\n");
        exit(EXIT_FAILURE);
    } 

    unsigned int* input_one = NULL;
    unsigned int* input_two = NULL;
    unsigned long int* output = NULL;
    // Allocate memory to store the integers
    allocate_mem(&input_one, &input_two, &output, num_ints);
    // Read the integers from the two input files
    get_ints(argv, input_one, input_two, output, num_ints);
   
    // Sum up the numbers
    sum_ints(input_one, input_two, output, num_ints);

    // Store the result in the output file 
    save_output(argv, input_one, input_two, output, num_ints);

    free(input_one);
    free(input_two);
    free(output);

    return 0;
}
