#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Author: @git-hulk
 * Date: 2014-07-19
 * This file is to KMP String Match Algorithm, a fast string match algorithm.
 * To see what is KMP:
 *  http://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 */ 

#define NOT_FOUND -1

/*
 * desc: To pre compute partial match table.
 */ 
int *kmpPreprocess(const char * str, int len) {
    if(len <= 0){
        return NULL;
    }
    
    int i = 0, j = -1;
    int *partialMatchTable = (int *) malloc(len * sizeof(int));
    partialMatchTable[0] = j;
    while(i < len) {
        while(j >= 0 && str[i] != str[j]) {
            j = partialMatchTable[j];    
        }
        i++;
        j++;
		// improve next array
        if(str[i] == str[j])
			partialMatchTable[i] = partialMatchTable[j];
		else
			partialMatchTable[i] = j;
    }
    return partialMatchTable;
}

/*
 * desc: kmp search algorithm.
 * preprocess need O(m) step, so kmp searching require O(n+m) steps.
 * as m << n, it require O(n)
 * as m == n, it require O(2n)
 */
int kmpStringMacth(const char *searchString, int sLen, const char* word, int wLen) {
    if(sLen <= 0 || wLen <= 0 || sLen < wLen) {
        return NOT_FOUND;
    }

    int *partialMT = kmpPreprocess(word, wLen);
    int i = 0, j = 0;
    while(i < sLen) {
        while(j >= 0 && searchString[i] != word[j]) {
            j = partialMT[j];
        }
        i++;
        j++;
        if(j == wLen) {
            return i - j;
        }
    }
    free(partialMT);
    return NOT_FOUND;
}

int main(int argc, char **argv) {
    assert(0 == kmpStringMacth("abcabcdabcdc", 12, "abcabcd", 7));
    assert(0 == kmpStringMacth("abcdabdabc", 10, "abc", 3));
    assert(7 == kmpStringMacth("abcdabdmbc", 10, "mbc", 3));
    assert(NOT_FOUND == kmpStringMacth("abcdabdmbc", 10, "abca", 4));
    return 0;
}
