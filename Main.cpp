#include <iostream>
#include <string>

void RotateArray(int pArr[], int pLowInd, int pHighInd);
void PrintArray(int pArr[], int length);
void SolveProblemForN(int pN);
void PrintArrayBasedOnTeamMatchups(int pArr[], int length, int indOfTeam1, int numParticipants);


int main()
{
	int N;
	std::cin >> N; 
	SolveProblemForN(N);
}


void SolveProblemForN(int pN)
{
	if(pN>1)
	{
		int lengthOfArr = (pN%2 == 0)? pN: pN+1;
		int Arr[lengthOfArr];
		Arr[lengthOfArr-1] = -1;



		for(int i=0; i<pN; i++)
		{
			Arr[i] = i+1;
		}
		std::cout<< 1 << ":";
 		int indOfTeam1 = 0;
		PrintArrayBasedOnTeamMatchups(Arr, lengthOfArr, indOfTeam1, pN);
		for(int i = 1; i<lengthOfArr-1; i++)
		{
			RotateArray(Arr, 0, lengthOfArr-2);
			indOfTeam1++;
			//TODO: Method that writes the matchups here, uses indofTeam1
			std::cout<< i+1 << ":";
			//PrintArray(Arr, lengthOfArr);
			PrintArrayBasedOnTeamMatchups(Arr, lengthOfArr, indOfTeam1, pN);
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


void PrintArray(int pArr[], int length)
{
	for(int i = 0; i< length; i++)
	{
		std::cout << pArr[i] << ((i<length-1)? (", "): ("") );
	}
	std::cout << std::endl;
}



void PrintArrayBasedOnTeamMatchups(int pArr[], int length, int indOfTeam1, int numParticipants)
{
	int curInd = indOfTeam1;
	int mirroredInd;
	int mirroredVal;
	for(int displace = 0; displace< numParticipants; displace++)
	{
		curInd = ((indOfTeam1+displace)%(length-1));
		mirroredInd = (length-1)-curInd;
		mirroredVal = pArr[mirroredInd];
		if(mirroredVal != -1)std::cout << mirroredVal;
		else std::cout << "-";
		if(displace != numParticipants-1) std::cout<< ":";
	}
	std::cout << std::endl;
}
