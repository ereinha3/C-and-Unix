#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#include "main.h"

#define MAX_FILENAME_SIZE 256
#define MAX_NUM_LENGTH 100

#define NUM_TIMERS 4
#define LOAD_TIME 0
#define CONVERT_TIME 1
#define SPMV_TIME 2
#define STORE_TIME 3


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
        fprintf(stderr, "usage: %s <matrix> <vector> <result>\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
}


/* This function prints out information about a sparse matrix
   input parameters:
       char*       fileName    name of the sparse matrix file
       MM_typecode matcode     matrix information
       int         m           # of rows
       int         n           # of columns
       int         nnz         # of non-zeros
   return paramters:
       none
 */
void print_matrix_info(char* fileName, MM_typecode matcode, 
                       int m, int n, int nnz)
{
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Matrix name:     %s\n", fileName);
    fprintf(stdout, "Matrix size:     %d x %d => %d\n", m, n, nnz);
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is matrix:       %d\n", mm_is_matrix(matcode));
    fprintf(stdout, "Is sparse:       %d\n", mm_is_sparse(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is complex:      %d\n", mm_is_complex(matcode));
    fprintf(stdout, "Is real:         %d\n", mm_is_real(matcode));
    fprintf(stdout, "Is integer:      %d\n", mm_is_integer(matcode));
    fprintf(stdout, "Is pattern only: %d\n", mm_is_pattern(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");
    fprintf(stdout, "Is general:      %d\n", mm_is_general(matcode));
    fprintf(stdout, "Is symmetric:    %d\n", mm_is_symmetric(matcode));
    fprintf(stdout, "Is skewed:       %d\n", mm_is_skew(matcode));
    fprintf(stdout, "Is hermitian:    %d\n", mm_is_hermitian(matcode));
    fprintf(stdout, "-----------------------------------------------------\n");

}


/* This function checks the return value from the matrix read function, 
   mm_read_mtx_crd(), and provides descriptive information.
   input parameters:
       int ret    return value from the mm_read_mtx_crd() function
   return paramters:
       none
 */
void check_mm_ret(int ret)
{
    switch(ret)
    {
        case MM_COULD_NOT_READ_FILE:
            fprintf(stderr, "Error reading file.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_PREMATURE_EOF:
            fprintf(stderr, "Premature EOF (not enough values in a line).\n");
            exit(EXIT_FAILURE);
            break;
        case MM_NOT_MTX:
            fprintf(stderr, "Not Matrix Market format.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_NO_HEADER:
            fprintf(stderr, "No header information.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_UNSUPPORTED_TYPE:
            fprintf(stderr, "Unsupported type (not a matrix).\n");
            exit(EXIT_FAILURE);
            break;
        case MM_LINE_TOO_LONG:
            fprintf(stderr, "Too many values in a line.\n");
            exit(EXIT_FAILURE);
            break;
        case MM_COULD_NOT_WRITE_FILE:
            fprintf(stderr, "Error writing to a file.\n");
            exit(EXIT_FAILURE);
            break;
        case 0:
            fprintf(stdout, "file loaded.\n");
            break;
        default:
            fprintf(stdout, "Error - should not be here.\n");
            exit(EXIT_FAILURE);
            break;

    }
}


/* This function reads information about a sparse matrix using the 
   mm_read_banner() function and printsout information using the
   print_matrix_info() function.
   input parameters:
       char*       fileName    name of the sparse matrix file
   return paramters:
       none
 */
void read_info(char* fileName)
{
    FILE* fp;
    MM_typecode matcode;
    int m;
    int n;
    int nnz;

    if((fp = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    if(mm_read_banner(fp, &matcode) != 0)
    {
        fprintf(stderr, "Error processing Matrix Market banner.\n");
        exit(EXIT_FAILURE);
    } 

    if(mm_read_mtx_crd_size(fp, &m, &n, &nnz) != 0) {
        fprintf(stderr, "Error reading size.\n");
        exit(EXIT_FAILURE);
    }

    print_matrix_info(fileName, matcode, m, n, nnz);

    fclose(fp);
}


/*
 */
void convert_coo_to_csr(int* row_ind, int* col_ind, double* val, 
                        int m, int n, int nnz,
                        unsigned int** csr_row_ptr, unsigned int** csr_col_ind,
                        double** csr_vals)

{
    // Temporary pointers
    unsigned int* row_ptr_;
    unsigned int* col_ind_;
    double* vals_;
    
    // We now how large the data structures should be
    // csr_row_ptr -> m + 1
    // csr_col_ind -> nnz
    // csr_vals    -> nnz
    row_ptr_ = (unsigned int*) malloc(sizeof(unsigned int) * (m + 1)); 
    assert(row_ptr_);
    col_ind_ = (unsigned int*) malloc(sizeof(unsigned int) * nnz);
    assert(col_ind_);
    vals_ = (double*) malloc(sizeof(double) * nnz);
    assert(vals_);

    // Now determine how many non-zero elements are in each row
    // Use a histogram to do this
    unsigned int* buckets = malloc(sizeof(unsigned int) * m);
    assert(buckets);
    memset(buckets, 0, sizeof(unsigned int) * m);

    for(unsigned int i = 0; i < nnz; i++) {
        // row_ind[i] - 1 because index in mtx format starts from 1 (not 0)
        buckets[row_ind[i] - 1]++;
    }

    // Now use a cumulative sum to determine the starting position of each
    // row in csr_col_ind and csr_vals - this information is also what is
    // stored in csr_row_ptr
    for(unsigned int i = 1; i < m; i++) {
        buckets[i] = buckets[i] + buckets[i - 1];
    }
    // Copy this to csr_row_ptr
    row_ptr_[0] = 0; 
    for(unsigned int i = 0; i < m; i++) {
        row_ptr_[i + 1] = buckets[i];
    }

    // We can use row_ptr_ to copy the column indices and vals to the 
    // correct positions in csr_col_ind and csr_vals
    unsigned int* tmp_row_ptr = (unsigned int*) malloc(sizeof(unsigned int) * 
                                                       m);
    assert(tmp_row_ptr);
    memcpy(tmp_row_ptr, row_ptr_, sizeof(unsigned int) * m);

    // Now go through each non-zero and copy it to its appropriate position
    for(unsigned int i = 0; i < nnz; i++)  {
        col_ind_[tmp_row_ptr[row_ind[i] - 1]] = col_ind[i] - 1;
        vals_[tmp_row_ptr[row_ind[i] - 1]] = val[i];
        tmp_row_ptr[row_ind[i] - 1]++;
    }

    // Copy the memory address to the input parameters
    *csr_row_ptr = row_ptr_;
    *csr_col_ind = col_ind_;
    *csr_vals = vals_;

    // Free memory
    free(tmp_row_ptr);
    free(buckets);
}

/*
 */
void read_vector(char* fileName, double** vector, int* vecSize)
{
    FILE* fp = fopen(fileName, "r");
    assert(fp);
    char line[MAX_NUM_LENGTH];    
    fgets(line, MAX_NUM_LENGTH, fp);
    fclose(fp);

    unsigned int vector_size = atoi(line);
    double* vector_ = (double*) malloc(sizeof(double) * vector_size);

    fp = fopen(fileName, "r");
    assert(fp); 
    // first read the first line to get the # elements
    fgets(line, MAX_NUM_LENGTH, fp);

    unsigned int index = 0;
    while(fgets(line, MAX_NUM_LENGTH, fp) != NULL) {
        vector_[index] = atof(line); 
        index++;
    }

    fclose(fp);
    assert(index == vector_size);

    *vector = vector_;
    *vecSize = vector_size;
}

/*
 */
void spmv(unsigned int* csr_row_ptr, unsigned int* csr_col_ind, 
          double* csr_vals, int m, int n, int nnz, 
          double* vector_x, double *res)
{
	unsigned int thread_num = std::max(atoi(std::getenv("OMP_NUM_THREADS")), 1);
	omp_set_num_threads(thread_num);
    // first initialize res to 0
   #pragma omp parallel for num_threads(omp_get_num_threads())
	for (int i = 0; i<m; i++) {
		res[i] = 0.0;
	}

    // calculate spmv
   #pragma omp parallel for num_threads(omp_get_num_threads())
    	for (int i = 0; i < m; i++) {
       		unsigned int row_begin = csr_row_ptr[i];
       		unsigned int row_end = csr_row_ptr[i + 1];
       		for(unsigned int j = row_begin; j < row_end; j++) {
          		res[i] += csr_vals[j] * vector_x[csr_col_ind[j]]; 
        	}
    	}
	/*
	I tested my parallelized code with 4 different thread counts: 1, 8, 16, and 32.
	The runtime with a thread count of 1 (AKA a nonparralelised version) was :
	Module	Time
	Load	0.877009
	Convert	0.027821
	SpMV	0.748299
	Store	0.035929
	The runtime with a thread count of 8 was :
	Module	Time
	Load	0.878360
	Convert	0.027710
	SpMV	0.756007
	Store	0.034092
	The runtime with a thread count of 16 was :
	Module	Time
	Load	0.875908
	Convert	0.027368
	SpMV	0.781442
	Store	0.034323
	The runtime with a thread count of 32 was :
	Module	Time
	Load	0.877235
	Convert	0.027849
	SpMV	0.763052
	Store	0.034452
	
	As is shown, the runtime results were suprising. These results were surprising because the only code that was parallelized was the SPMV function. As
	is shown, the spmv runtime actually went up with a higher thread count, showing that the compiler is already optimizing runtime. The interesting this is
	that the store function actually decreased in runtime with a higher thread count. This is suprising because I did not edit this function at all, meaning
	this function must be reliant on the output of spmv. I'm not entirely sure how this happened as I am still fairly new to code parallelizing, however I 
	found this very interesting. The way I changed the thread count was using export OMP_NUM_THREADS = number. I then read this number from the getenv standard 
	namespace and set my thread count to this number. I couldn't find anything mentioning this in the slides but I found good documentation for this on
	stackoverflow at the link provided here: https://stackoverflow.com/questions/24435759/using-the-script-variable-omp-num-threads-in-the-program-source-files.
	I would love to know why my runtime increased, so, to whoever is reading this, if you have time, feel free to write me an email if you have an explanation!
	Thanks! :)
	*/
}
void store_result(char *fileName, double* res, int m)
{
    FILE* fp = fopen(fileName, "w");
    assert(fp);

    fprintf(fp, "%d\n", m);
    for(int i = 0; i < m; i++) {
        fprintf(fp, "%0.10f\n", res[i]);
    }

    fclose(fp);
}


void print_time(double timer[])
{
    fprintf(stdout, "Module\tTime\n");
    fprintf(stdout, "Load\t");
    fprintf(stdout, "%f\n", timer[LOAD_TIME]);
    fprintf(stdout, "Convert\t");
    fprintf(stdout, "%f\n", timer[CONVERT_TIME]);
    fprintf(stdout, "SpMV\t");
    fprintf(stdout, "%f\n", timer[SPMV_TIME]);
    fprintf(stdout, "Store\t");
    fprintf(stdout, "%f\n", timer[STORE_TIME]);
}

/* This program first reads in a sparse matrix stored in matrix market format 
   (mtx). It generates a set of arrays - row_ind, col_ind, and val, which stores
   the row/column index and the value for the non-zero elements in the matrix, 
   respectively. This is also known as the co-ordinate format.

   Then, it should convert this matrix stored in co-ordinate format to the
   compressed sparse row (CSR) format.

   Then, finally it should use the CSR format to multiply the matrix with a 
   vector (i.e., calculate the sparse matrix vector multiply, or SpMV).

   The resulting vector should then be stored in a file, one value per line, 
   whose name was specified as an input to the program.
 */
int main(int argc, char** argv)
{
    usage(argc, argv);

    // Initialize timers
    double timer[NUM_TIMERS];
    uint64_t t0;
    for(unsigned int i = 0; i < NUM_TIMERS; i++) {
        timer[i] = 0.0;
    }
    InitTSC();

    // Read the sparse matrix file name
    char matrixName[MAX_FILENAME_SIZE];
    strcpy(matrixName, argv[1]);
    read_info(matrixName);

    // Read the sparse matrix and store it in row_ind, col_ind, and val,
    // also known as co-ordinate format.
    int ret;
    MM_typecode matcode;
    int m;
    int n;
    int nnz;
    int *row_ind;
    int *col_ind;
    double *val;

    fprintf(stdout, "Matrix file name: %s ... ", matrixName);

    t0 = ReadTSC();
    ret = mm_read_mtx_crd(matrixName, &m, &n, &nnz, &row_ind, &col_ind, &val, 
                          &matcode);
    timer[LOAD_TIME] += ElapsedTime(ReadTSC() - t0);

    check_mm_ret(ret);

    // Convert co-ordinate format to CSR format
    fprintf(stdout, "Converting COO to CSR...");
    unsigned int* csr_row_ptr = NULL; 
    unsigned int* csr_col_ind = NULL;  
    double* csr_vals = NULL; 
    t0 = ReadTSC();
    convert_coo_to_csr(row_ind, col_ind, val, m, n, nnz,
                       &csr_row_ptr, &csr_col_ind, &csr_vals);
    timer[CONVERT_TIME] += ElapsedTime(ReadTSC() - t0);
    fprintf(stdout, "done\n");

    // Load the vector file
    char vectorName[MAX_FILENAME_SIZE];
    strcpy(vectorName, argv[2]);
    fprintf(stdout, "Vector file name: %s ... ", vectorName);
    double* vector_x;
    unsigned int vector_size;

    t0 = ReadTSC();
    read_vector(vectorName, &vector_x, &vector_size);
    timer[LOAD_TIME] += ElapsedTime(ReadTSC() - t0);

    assert(n == vector_size);
    fprintf(stdout, "file loaded\n");

    // Calculate SpMV
    double *res = (double*) malloc(sizeof(double) * m);;
    assert(res);
    fprintf(stdout, "Calculating SpMV ... ");
   
    t0 = ReadTSC();
    for(unsigned int i = 0; i < 100; i++) {
        spmv(csr_row_ptr, csr_col_ind, csr_vals, m, n, nnz, vector_x, res);
    }
    timer[SPMV_TIME] += ElapsedTime(ReadTSC() - t0);

    fprintf(stdout, "done\n");

    // Store the calculated vector in a file, one element per line.
    char resName[MAX_FILENAME_SIZE];
    strcpy(resName, argv[3]); 
    fprintf(stdout, "Result file name: %s ... ", resName);

    t0 = ReadTSC();
    store_result(resName, res, m);
    timer[STORE_TIME] += ElapsedTime(ReadTSC() - t0);

    fprintf(stdout, "file saved\n");

    print_time(timer);

    // Free memory
    free(csr_row_ptr);
    free(csr_col_ind);
    free(csr_vals);

    free(vector_x);
    free(res);

    free(row_ind);
    free(col_ind);
    free(val);

    return 0;
}
