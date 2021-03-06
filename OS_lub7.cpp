#include <stdio.h>
#include <vector>;
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <iostream>
#include <fcntl.h>


int n = -1;

class Str {
	int startPos;
	int numLet;
public:
	Str() {
    	startPos = 0;
    	numLet = 0;
	}

	Str(int a, int b) {
    	startPos = a;
    	numLet = b;
	}

	void SetPos(int a) {
    	startPos = a;
	}

	void SetNum(int b) {
    	numLet = b;
	}

	int GetPos() {
    	return startPos;
	}

	int GetNum() {
    	return numLet;
	}
};

void FindLine(std::vector<Str>* arr, char *map) {
	int s = 0;
	for (int j = 0; j < size; j++)
	{
    		if (map[j] == '\n') {
        		(*arr).insert((*arr).end(), Str(s, (j - s)));
        		s = j;
    		}
	}
}

void FromFileToMem(int input_file, char *map) {
	//PROT_READ pages may be read
	if ((map = (char*)mmap(0, lseek(input_file, 0, SEEK_END), PROT_READ, MAP_SHARED, input_file, 0)) == MAP_FAILED)
	{
    	printf("Error mapping file.\n");
    	exit(1);
	}
}

void printFile(char *map) {

	std::cout << std::endl;
	for (int j = 0; j < size; j++)
	{
    	std::cout << map[j];
	}
	std::cout << std::endl;
}

void  ALARMhandler(int sig)
{
	signal(SIGALRM, SIG_IGN);      	/* ignore this signal   	*/
	//printFile(char *map);
	n = 0;
	signal(SIGALRM, ALARMhandler); 	/* reinstall the handler	*/
	//exit(1);
}

int Process(std::vector<Str> arr) {
	int n;
	if (scanf("%d", &n) != EOF)
	{
    	if (n<0 || n> arr.size()) {
        	std::cout << "We are sorry" << std::endl;
        	exit(1);
    	}
    	if (n == 0) {
        	std::cout << "The end" << std::endl;
        	exit(1);
    	}
    for (int i = arr[n - 1].GetPos(); i < (arr[n - 1].GetPos()+arr[n - 1].GetNum()); i++) {
        	std::cout << map[i];
    	}
	}
	return n;
}

int main(int argc, char* argv[])
{
	std::vector<Str> arr;
	char *map;
	int s = 0;
	int input_file;
	if ((input_file = open("in.txt", O_RDONLY)) == (-1))
	{
    		printf("failed to open");
    		exit(1);
	}
	FromFileToMem( input_file, map);
	FindLine( &arr, map);
	while (n != 0) {
    		signal(SIGALRM, ALARMhandler);
    		std::cout << "Enter number of string from 1 for " << arr.size() << " (you have 5 sec): ";
    		alarm(5);
    		n = Process(arr);
	}
	printFile(char *map);
	close(input_file);
	return 0;
}
