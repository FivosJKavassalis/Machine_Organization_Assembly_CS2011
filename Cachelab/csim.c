/*
 * Fivos Kavassalis /fikavassalis
 * Theodoros Konstantopoulos /tkonstantopoulos
 */

#include "cachelab.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int numHits = 0; // number of hits

int numMisses = 0; // number of misses

int numEvictions = 0; // number of evictions

typedef struct blockStruct {
	int valid;
	int tag;
	int data;
} block;

typedef struct cacheStruct {
	int s;
	int S; // Number of sets, where S = 2^s 
	int b;
	int B; // Bytes per cache block, where B = 2^b
	int E;

	int numBlocks;
	int size;

	block* pointedBlock;

} cache;

/*
 * getAddress
 * @param address which is a pointer to an address
 * gets address from the second part of trace file
 */
char* getAddress(char* address) {
	int length = strlen(address); // address length
	char* newAddress = malloc(length * sizeof(char));

	for (int i = 0; i <= length; i++) {
		if (address[i] != ',') {
			newAddress[i] = address[i];
		} else {
			newAddress[i] = '\0';
			break;
		}
	}
	return newAddress;
}

/*
 * getSize
 * @param address which is a pointer to an address
 * gets size from the second part of trace file
 */
char* getSize(char* address) {
	int length = strlen(address); // address length
	char* size = malloc(length * sizeof(char));

	for (int i = 0; i <= length; i++) {
		if (!(address[i] != ',')) {
			size[0] = address[i + 1];
			size[1] = '\0';
			break;
		}
	}
	return size;
}

/*
 * outputHelp
 * gives guideline on input of simulation
 */

void outputHelp() {

	printf("Arguments: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
	printf("Options:\n");
	printf("  -h         Print this help message.\n");
	printf("  -v         Optional verbose flag.\n");
	printf("  -s <num>   Number of set index bits.\n");
	printf("  -E <num>   Number of lines per set.\n");
	printf("  -b <num>   Number of block offset bits.\n");
	printf("  -t <file>  Trace file.\n");
	printf("Example:\n");
	printf("linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");

	exit(0);

}

int main(int argc, char **argv) // CAREFUL HERE !!! (ARGUMENTS...)
{

	char* file;
	int option = 0;
	int vFlag = 0; // define v flag

	if (argc == 1) {

		outputHelp();

	}

	// cache
	cache aCache;

	// Parsing arguments
	while ((option = getopt(argc, argv, "hvs:E:b:t:")) != -1) {

		switch (option) {

		case 'h':
			outputHelp();
			break;
		case 'v':
			vFlag = 1;
			break;
		case 's':
			if (atoi(optarg) <= 0) {
				printf("s value can't be less or equal to 0 \n");
				outputHelp();
			}

			aCache.s = (atoi(optarg));
			aCache.S = pow(2, aCache.s);
			break;
		case 'E':
			if (atoi(optarg) <= 0) {
				printf("E value can't be less or equal to 0");
				outputHelp();
			}

			aCache.E = atoi(optarg);
			break;
		case 'b':
			if (atoi(optarg) <= 0) {
				printf("b value can't be <= 0. \n");
				outputHelp();
			}

			aCache.b = (atoi(optarg));
			aCache.B = pow(2, aCache.b);
			break;
		case 't':
			file = optarg; // name of trace file
			break;
		default:
			outputHelp();
			break;
		}
	}

	FILE *traceFile = fopen(file, "r"); // open trace file

	// Inform user if file does not exist
	if (!traceFile) {
		printf("No input file\n");
		exit(0);
	}

	int lineCounter = 1; // will be used to traverse through lines of instructions and addresses
	int maxLines = 268000;
	char instructions[maxLines][2]; // for instructions
	char addresses[maxLines][3]; // for the corresponding addresses

	aCache.numBlocks = (aCache.S * aCache.E); // num of blocks is equal to num of sets * num of lines per set

	aCache.size = (aCache.S * aCache.E * aCache.B); // size of cache is (S x E x B)

	aCache.pointedBlock = malloc(aCache.size * sizeof(block)); // allocate space

	// set every cache bit to 0
	for (int i = 0; i < aCache.numBlocks; i++) {
		aCache.pointedBlock[i].valid = 0;
		aCache.pointedBlock[i].tag = 0;
		aCache.pointedBlock[i].data = 0;

	}

	char* nullChar;

	while (fscanf(traceFile, "%s %s", *instructions, *addresses) != EOF) {

		//go through addresses array to find the actual address and size of each element
		char* newAddress = getAddress(*addresses);
		char* size = getSize(*addresses);

		int hexAddress = strtol(newAddress, &nullChar, 16); // convert address to hex

		//if string compare is not I (ignore if I?)
		if (strcmp(*instructions, "I")) {

			if (vFlag == 1) //if v flag is set print the instructions
				printf(" %s %s,%s ", *instructions, newAddress, size);


			int Tag = hexAddress >> (aCache.b + aCache.s); // shift to get the tag bits of the address
			int setIndex = (hexAddress ^ (Tag << (aCache.b + aCache.s))) >> aCache.b; // shift to get the set index bits of the address
			int isHit = 0; // will be set, if there is a hit
			int isEvict = 0; // will be set, if there is an eviction

			for (int i = 0; i < aCache.E; i++) {  // check if blocks match in the row of a set
				if (aCache.pointedBlock[(setIndex * aCache.E) + i].tag == Tag && aCache.pointedBlock[(setIndex * aCache.E) + i].valid == 1) { // if we have a hit, increment
					numHits++;
					aCache.pointedBlock[(setIndex * aCache.E) + i].data = lineCounter;
					isHit = 1; // var is set

					if (!strcmp(*instructions, "M")) { // if instruction is M, it must count hits two times, so increment one more
						numHits++;
						printf("Hit ");
					}
					printf("Hit\n");
					break;
				}
			}

			if (!isHit) { // if miss, increment misses and print
				numMisses++;
				printf("miss ");

				int evictIndex; // var to store the set index bits of the evicted block
				int inUse = 1; // check if block is in use (Will be set if it is)
				int tempLineCnt = lineCounter; // temporary line counter var

				for (int i = 0; i < aCache.E; i++) { //check for empty lines
					if (aCache.pointedBlock[(setIndex * aCache.E) + i].valid != 1) {
						evictIndex = i;
						inUse = 0;
						break;
					}
				}

				if (inUse == 1) { //if in use, evict
					for (int i = 0; i < aCache.E; i++) {
						if (aCache.pointedBlock[(setIndex * aCache.E) + i].data	< tempLineCnt) {
							tempLineCnt = aCache.pointedBlock[(setIndex * aCache.E) + i].data;
							evictIndex = i;
						}
					}
					numEvictions++;
					isEvict = 1;
				}

				aCache.pointedBlock[(setIndex * aCache.E) + evictIndex].valid = 1;
				aCache.pointedBlock[(setIndex * aCache.E) + evictIndex].tag = Tag;
				aCache.pointedBlock[(setIndex * aCache.E) + evictIndex].data = lineCounter;

				if (isEvict) { // if evicted, print
					printf("eviction ");
				}
				//M instructions have extra hit counter
				if (!strcmp(*instructions, "M")) {
					numHits++;
					printf("hit");
				}
				printf("\n");
			}

		}

		lineCounter++; // go to next line (keep going for next instruction and address until EOF)
	}

	fclose(traceFile); // close trace file after EOF

	free(aCache.pointedBlock); // free space that was allocated

	printSummary(numHits, numMisses, numEvictions); // print summary of the number of hits, misses and evictions


	return 0;
}
