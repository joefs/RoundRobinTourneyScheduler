#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

void RotateArray(int pArr[], int pLowInd, int pHighInd);
void PrintArray(int pArr[], int length);
void SolveProblemForN(int pN, std::ofstream* oS, std::ifstream* iF);
void PrintArrayBasedOnTeamMatchups(int pArr[], int length, int indOfTeam1, int numParticipants, std::ofstream* oSPtr);
void SolveAndWrite(int pArr[], int length, int numParticipants, std::ofstream* oSPtr);
void LoopThroughInputFile();
void DeleteDefaultOutputFile();

static bool hasWrittentoFileBefore;


int main()
{
	bool bIsRunning = true;
	char initialCommand = 'I';
	while(bIsRunning)
	{
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		std::cout << "HELLO, AND WELCOME TO THE PROGRAM. PLEASE SELECT AMONGST THE FOLLOWING OPTIONS:" << std::endl;
		std::cout << '\t' << "F: RUN FROM FILE" << std::endl;
		std::cout << '\t' << "C: RUN FROM CONSOLE" << std::endl;
		std::cout << '\t' << "Q: QUIT" << std::endl;
		initialCommand= (std::cin.get());
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		std::cout << ">             " << std::endl;
		hasWrittentoFileBefore = false;
		switch(initialCommand)
		{
			case 'F':
			case 'f':
				LoopThroughInputFile(); // will yield to multiple cases of SolveProblemForN();
				break;
			case 'C':
			case 'c':
					std::cout << "Please enter a number of tournament participants" << std::endl;
					int N;
					std::cin >> N;
					SolveProblemForN(N, NULL, NULL);
				break;
			case 'Q':
			case 'q':
					bIsRunning = false;
				break;
			default:
					std::cout << "I'm sorry I didn't understand? Please repeat." << std::endl;
				break;

		}
		std::cin.ignore(10000, '\n');
	}
		std::cout<< "ADIOS. Enter any key to quit." << std::endl;
		std::cin.get();
}


void SolveProblemForN(int pN, std::ofstream* oS, std::ifstream* iF)
{
	if(pN>1)
	{
		int lengthOfArr = (pN%2 == 0)? pN: pN+1;
		int Arr[lengthOfArr];
		//
		Arr[lengthOfArr-1] = -1;
		for(int i=0; i<pN; i++)Arr[i] = i+1;
		if(pN<11)
		{
			SolveAndWrite(Arr, lengthOfArr, pN, oS);
		}
		else
		{
			std::cout << "WRITING TO OUTPUT.TXT" << std::endl; //HighNumberSolution
			// FIGURE OUT IF THE OSTREAM ALREADY EXISTS AND DO STUFF WITH MYFILE IF IT WASNT INITIALIZED PREVIOUSLY
			std::ofstream myfile;
			myfile.open ("output.txt", std::ios_base::app);
			oS = &myfile;
			SolveAndWrite(Arr, lengthOfArr, pN, oS);
			oS->close();
			hasWrittentoFileBefore = true;
		}
	}
}


void RotateArray(int pArr[], int pLowInd, int pHighInd)
{
	if(pHighInd> pLowInd)
	{
		int toMoveForward = pArr[pHighInd];
		int temp;
		for(int i = pLowInd; i<= pHighInd; i++)
		{
			temp = pArr[i];
			pArr[i] = toMoveForward;
			toMoveForward = temp;
		}
	}
}



void PrintArrayBasedOnTeamMatchups(int pArr[], int length, int indOfTeam1, int numParticipants, std::ofstream* oSPtr)
{
	int curInd = indOfTeam1;
	int mirroredInd;
	int mirroredVal;
	for(int displace = 0; displace< numParticipants; displace++)
	{
		curInd = ((indOfTeam1+displace)%((length-1)));
		if((displace== numParticipants - 1)&&(numParticipants%2==0)) curInd = numParticipants-1; 
		mirroredInd = (length-1)-curInd;
		mirroredVal = pArr[mirroredInd];
		if(mirroredVal != -1)
		{
			((oSPtr==NULL)? std::cout : (*oSPtr))<< mirroredVal;
		}
		else
		{
			((oSPtr==NULL)? std::cout : (*oSPtr))<< "-";
		}
		if(displace != numParticipants-1)
		{
			((oSPtr==NULL)? std::cout : (*oSPtr))<< ":";
		}
	}
	((oSPtr==NULL)? std::cout : (*oSPtr))<< std::endl;
}


void SolveAndWrite(int pArr[], int length, int numParticipants, std::ofstream* oSPtr)
{
	bool bIsConsole = (numParticipants<11);
	// if the file is not empty then print 2*n # chars
	if(!bIsConsole && hasWrittentoFileBefore)
	{
		for(int i = 0; i< numParticipants*2 ; i++)
		{
			*oSPtr << '#';
		}
		*oSPtr << std::endl;
	}
	((bIsConsole)? std::cout : (*oSPtr))<< 1 << ":";
	int indOfTeam1 = 0;
	PrintArrayBasedOnTeamMatchups(pArr, length, indOfTeam1, numParticipants, oSPtr);
	//
	for(int i = 1; i<length-1; i++)
	{
		RotateArray(pArr, 0, length-2);
		indOfTeam1++;
		((bIsConsole)? std::cout : (*oSPtr))<< i+1 << ":";
		PrintArrayBasedOnTeamMatchups(pArr, length, indOfTeam1, numParticipants, oSPtr);
	}
}







void LoopThroughInputFile()
{
	bool isValid = false;
	std::string fileString;
	while(!isValid)
	{
		std::cout<< "Please provide a VALID input file name."<< std::endl;
		std::cin >> fileString;
		struct stat buffer;   
 		isValid = (stat (fileString.c_str(), &buffer) == 0);
	}

	DeleteDefaultOutputFile();



	std::ifstream myReadFile;
	myReadFile.open(fileString.c_str());
	int currentN;
	if (myReadFile.is_open()) {
		std::cout<< "ITS OPEN" << std::endl;
		 while (!myReadFile.eof()) {
		    myReadFile >> currentN;
		    //IF ITS GREATER PASS IN THE OUTPUT FILE AND 
			SolveProblemForN(currentN, NULL, NULL);
		 }
		 // IF OFILE IS OPEN, CLOSE IT NOW
	}
	myReadFile.close();
}












void PrintArray(int pArr[], int length)
{
	for(int i = 0; i< length; i++)
	{
		std::cout << pArr[i] << ((i<length-1)? (", "): ("") );
	}
	std::cout << std::endl;
}

void DeleteDefaultOutputFile()
{
	bool EXISTS = false;
	struct stat buffer;   
	std::string fileString = "Output.txt";
	EXISTS = (stat (fileString.c_str(), &buffer) == 0);
	if(EXISTS)
	{
		if( remove( fileString.c_str() ) != 0 ) perror( "Error deleting file" );
	}
}