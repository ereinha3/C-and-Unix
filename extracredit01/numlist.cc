#include "numlist.h"
#include <algorithm>
#include <vector>

using namespace std;

// Partitioning functions
// Serial partition
unsigned int NumList::partition(vector<int>& keys, unsigned int low, 
                                unsigned int high)
{
    // Use the last element as the pivot
    int pivot = keys[high];
    int start = low - 1;
    int tmp;
    for (unsigned int i = low; i<high; i++) {
	    if (keys[i]<pivot) {
		    start++;
		    tmp = keys[i];
		    keys[i] = keys[start];
		    keys[start] = tmp;
	    }
    }
    tmp = keys[start+1];
    keys[start+1] = keys[high];
    keys[high] = tmp;
    return start+1;
		    
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot
    int size = (int)(high-low);
    int pivot = keys[high];
    vector<int> result(size+1, 0);
    vector<int> great(size, 0);
    vector<int> less(size, 0);
    vector<int> gp(size, 0);
    vector<int> lp(size, 0);
#pragma omp parallel for
    for (unsigned int i=low; i<high; i++) {
	    if (keys[i]<pivot) {
		    less[i-low] = 1;
	    }
	    else {
		    great[i-low] = 1;
	    }
    }
    lp[0] = less[0];
    gp[0] = great[0];
    for (int i = 1; i<size; i++) {
	    lp[i] = lp[i-1] + less[i];
	    gp[i] = gp[i-1] + great[i];
    }
    result[lp[size-1]] = pivot;
    pivot = lp[size-1];
#pragma omp parallel for
    for (int i = 0; i<size; i++) {
	    if (less[i] == 1) {
		    result[lp[i]-1] = keys[low + i];
	    }
	    else {
		    result[pivot+gp[i]] = keys[low + i];
	    }
    }
#pragma omp parallel for
    for (int i = 0; i<size+1; i++){
	    keys[low+i] = result[i];
    }
    return low+pivot;
}

// Actual qsort that recursively calls itself with particular partitioning
// strategy to sort the list
void NumList::qsort(vector<int>& keys, int low, int high, ImplType opt)
{
    if(low < high) {
        unsigned int pi;
        if(opt == serial) {
            pi = partition(keys, low, high);
        } else {
            pi = partition_par(keys, low, high);
        }
        qsort(keys, low, pi - 1, opt);
        qsort(keys, pi + 1, high, opt);
    }
}

// wrapper for calling qsort
void NumList::my_qsort(ImplType opt)
{
    /* Initiate the quick sort from this function */
    qsort(list, 0, list.size() - 1, opt);
}
// Default constructor
// This should "create" an empty list
NumList::NumList() {
    /* do nothing */
    /* you will have an empty vector */
}
// Contructor
// Pass in a vector and the partitioning strategy to use
NumList::NumList(vector<int> in, ImplType opt) {
    list = in;
    my_qsort(opt);
}
// Destructor
NumList::~NumList() {
    /* do nothing */
    /* vector will be cleaned up automatically by its destructor */
}
// Get the element at index
int NumList::get_elem(unsigned int index)
{
    return list[index];
}
// Print the list
void NumList::print(ostream& os)
{
    for(unsigned int i = 0; i < list.size(); i++) {
        os << i << ":\t" << list[i] << endl;
    }
}
