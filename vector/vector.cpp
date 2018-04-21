#include <iostream>
#include <random>
#include <chrono>
#include <vector>
using namespace std;

void printlist(vector<int> listy);

void printlist(vector<int> listy)
{
	for(int i = 0; i < listy.size(); i++)
	{
		cout << listy[i] << " ";
	}
	cout << endl;
}

int main()
{

	//set up clock time as see
	typedef chrono::system_clock clock;
	auto seed = chrono::time_point_cast<chrono::milliseconds>(clock::now()).time_since_epoch().count();

	//let's generate a random N 
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,10);
	int n = distribution(generator);

	//now we need our random numbers, no repeats
	//all placed in a vector
	vector <int> randomList;
	int temp;

	for(int i = 0; i < n; i++)
	{
		temp = distribution(generator);
		auto iterator = find(randomList.begin(), randomList.end(), temp);
		if(iterator == randomList.end())
		{
			randomList.push_back(temp);
		}else
		{
			i--;
		}
	}
	cout << "List size is: " << n <<endl;
	cout << "This is our random list: ";
	printlist(randomList);

	//now insert one by one,sorting, into list sortList
	vector<int> sortList;
	sortList.insert(sortList.begin(), *(randomList.begin()));

	//start recording time 
	auto start1 = chrono::steady_clock::now();
	for(int i = 1; i < n; i++)
	{
		int tempNum = randomList[i];
		
		if(tempNum < sortList[0])
		{
			sortList.insert(sortList.begin(), tempNum);
		}else
		{
			int index;
			int j;
			for(j = 0; j < sortList.size(); j++)
			{
				if(tempNum > sortList[j])
				{	
					index = j + 1;
				}
			}
			sortList.insert(next(sortList.begin(), index), tempNum);
		}
	}
	auto end1 = chrono::steady_clock::now();
	auto elaspTime1 = end1 - start1;

	cout << "This is our sorted list: ";
	printlist(sortList);

	//generate a random list of position to move
	//from list
	vector<int> removeIndex;
	int tempp;
	int listlength = n;

	for(int i = 0; i < n; i++)
	{
		uniform_int_distribution<int> distri(0, listlength -1);
		tempp = distri(generator);
		listlength-= 1;
		removeIndex.push_back(tempp);
	}

	//remove positions in sortlist one by one by position
	//record time
	auto start2 = chrono::steady_clock::now();
	for(int i = 0; i < removeIndex.size(); i++)
	{
		auto deleteIndex = next(sortList.begin(), removeIndex[i]);
		sortList.erase(deleteIndex);
	}	
	auto end2 = chrono::steady_clock::now();
	auto elaspTime2 = end2 - start2;
	
	cout << "Duration to insert into list: " << chrono::duration <double, milli> (elaspTime1).count() << " milliseconds\n";
	cout << "Duration to remove from list: " << chrono::duration <double, milli> (elaspTime2).count() << " milliseconds\n";
	
	return 0;
}
