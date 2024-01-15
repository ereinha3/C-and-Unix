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
    int truth = 1;
    vector<int> result;
    while (truth) {
	    vector<int> front;
	    vector<int> equal;
	    vector<int> back;
	    for (size_t i = 0; i<keys.size(); i++) {
		    if (keys[i] < pivot) {
			    front.push_back(keys[i]);
		    }
		    if (keys[i] == pivot) {
			    equal.push_back(keys[i]);
		    }
		    if (keys[i] > pivot) {
			    back.push_back(keys[i]);
		    }
	    }
	    result.clear();
	    result.insert(result.end(), front.begin(), front.end());
	    result.insert(result.end(), equal.begin(), equal.end());
	    result.insert(result.end(), back.begin(), back.end());
	    int tmp_truth = 1;
	    for (size_t i = 0; i<(keys.size()-1); i++) {
		    if (keys[i+1] < keys[i]){
			    tmp_truth = 0;
		    }
	    }
	    if (tmp_truth) {
		    truth = 0;
	    }
    }
    for (size_t i = 0; i<keys.size(); i++) {
	    if (pivot==keys[i]) {
		    return i;
	    }
    }
    return -1;
}

// Parallel partition
unsigned int NumList:: partition_par(vector<int>& keys, unsigned int low,
                                     unsigned int high)
{
    // Use the last element as the pivot
    int partsize = (int)keys.size();
    int pivot = keys[high];
    vector<int> result;
    vector<int> gt(partsize+1, 0);
    vector<int> lt(partsize, 0);
    vector<int> gtp(partsize, 0);
    vector<int> ltp(partsize, 0);
#pragma omp parallel for
    for (int i=low; i<high; i++) {
	    if (keys[i]<pivot) {
		    lt[i-low] = 1;
	    }
	    else {
		    gt[i-low] = 1;
	    }
    }
    ltp[0] = lt[0];
    gtp[0] = gt[0];
    for (int i = 1; i<partsize; i++) {
	    ltp[i] = ltp[i-1] + lt[i];
	    gtp[i] = gtp[i-1] + gt[i];
    }
    result[ltp[partsize-1]] = pivot;
    pivot = ltp[partsize-1];
#pragma omp parallel for
    for (int i = 0; i<partsize; i++) {
	    if (lt[i] == 1) {
		    result[ltp[i]-1] = keys[low + i];
	    }
	    else {
		    result[pivot+gtp[i]] = keys[low + i];
	    }
    }
#pragma omp parallel for
    for (int i = 0; i<partsize+1; i++){
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
