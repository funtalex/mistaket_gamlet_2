#include "my_sort.h"
#include <ctype.h>
#include <string.h>

//typedef struct{
//	char* pointer;
//	int length;
//} line;
struct line {
	char* pointer = NULL;
	int length = 0;
};



/*!
	\author Alex Sergeechev aka funtalex
	\version 1.0
	\brief This function compares two lines from the start ignoring punctuation
	\param[in] first - first line to compare
	\param[in] second - second line to compare

	This function returns: 
	1)positive number if first line stands after second in lexical order,
	2)negative number if second line stands after first in lexical order,
	3)zero if first and second lines are equal

	\return integer number showing order of lines
*/
int cmp_str_start(struct line first, struct line second) {
	int i = 0, j = 0;
	while (i < first.length && j < second.length) {
		if (!isalpha(first.pointer[i])) {
			i++;
		}
		else if (!isalpha(second.pointer[j])) {
			j++;
		}
		else if (first.pointer[i] != second.pointer[j]) {
			return first.pointer[i] - second.pointer[j];
		}
		else {
			i++;
			j++;
		}
	}
	if (i == first.length && j == second.length) {
		return 0;
	}
	if (i != first.length) {
		return 1;
	}
	return -1;
}


/*!
	\author Alex Sergeechev aka funtalex
	\version 1.0
	\brief This function compares two lines from the end ignoring punctuation
	\param[in] first - first line to compare
	\param[in] second - second line to compare

	This function returns:
	1)positive number if first reversed line stands after second reversed in lexical order,
	2)negative number if second reversed line stands after first reversed in lexical order,
	3)zero if first and second lines are equal

	\return integer number showing order of lines
*/
int cmp_str_end(struct line first, struct line second) {
	int i = first.length - 1;
	int j = second.length - 1;
	while (i >= 0 && j >= 0) {
		if (!isalpha(first.pointer[i])) {
			i--;
		}
		else if (!isalpha(second.pointer[j])) {
			j--;
		}
		else if (first.pointer[i] != second.pointer[j]) {
			return first.pointer[i] - second.pointer[j];
		}
		else {
			i--;
			j--;
		}
	}
	if (i == 0 && j == 0) {
		return 0;
	}
	if (i != first.length) {
		return 1;
	}
	return -1;
}


/*!
	\author Alex Sergeechev aka funtalex
	\version 1.0
	\brief This function sorts array of lines 
	\param[in] low - minimal index of array
	\param[in] high - maximal index of array
	\param[in] cmp - comparator showing the way we sort
	\param[out] arr - pointers on lines in order
*/
void my_sort(struct line* arr, int low, int high, int cmp) {
	int i = low;
	int j = high;
	int pivot = (j + i) / 2;
	int temp;

	while (i <= j) {
		while (cmp(arr[i].pointer, arr[pivot].pointer) < 0) {
			i++;
		}
		while (cmp(arr[j].pointer, arr[pivot].pointer) > 0) {
			j--;
		}
		if (i >= j) {
			break;
		}
		else {
			struct line temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	if (j > low) {
		my_sort(arr, low, j);
	}
	if (i < high) {
		my_sort(arr, i, high)
	}
}
