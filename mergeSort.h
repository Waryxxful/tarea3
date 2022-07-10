#include <iostream>
#include <cstring>
#include <string>

struct Index{
    int consultas;
    int key;
};

class SortList{
    Index *arr;
    int size;

    public:
        SortList(){
            arr = new Index[128];
            size = 0;
        };

        void Insert(Index n){
            arr[size] = n;
            size +=1;
        }

        void merge(Index *array, int left, int mid, int right){
            int subArrayOne = mid - left + 1;
            int subArrayTwo = right - mid;
        
            // Create temp arrays
            Index *leftArray = new Index[subArrayOne],
                *rightArray = new Index[subArrayTwo];
        
            // Copy data to temp arrays leftArray[] and rightArray[]
            for (auto i = 0; i < subArrayOne; i++)
                leftArray[i] = array[left + i];
            for (auto j = 0; j < subArrayTwo; j++)
                rightArray[j] = array[mid + 1 + j];
        
            int indexOfSubArrayOne = 0, // Initial index of first sub-array
                indexOfSubArrayTwo = 0; // Initial index of second sub-array
            int indexOfMergedArray = left; // Initial index of merged array
        
            // Merge the temp arrays back into array[left..right]
            while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
                if (leftArray[indexOfSubArrayOne].consultas <= rightArray[indexOfSubArrayTwo].consultas) {
                    array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                    indexOfSubArrayOne++;
                }
                else {
                    array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                    indexOfSubArrayTwo++;
                }
                indexOfMergedArray++;
            }
            // Copy the remaining elements of
            // left[], if there are any
            while (indexOfSubArrayOne < subArrayOne) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
                indexOfMergedArray++;
            }
            // Copy the remaining elements of
            // right[], if there are any
            while (indexOfSubArrayTwo < subArrayTwo) {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
                indexOfMergedArray++;
            }
        }
        
        // begin is for left index and end is
        // right index of the sub-array
        // of arr to be sorted */
        void mergeSort(Index *array, int begin, int end){
            if (begin >= end)
                return;
        
            int mid = begin + (end - begin) / 2;
            mergeSort(array, begin, mid);
            mergeSort(array, mid + 1, end);
            merge(array, begin, mid, end);
        }

        Index *sort(){
            mergeSort(arr, 0, size-1);
            return arr;
        }

        void clear(){
            delete [] arr;
        }
};

