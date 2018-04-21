#include <iostream>
#include <random>
#include <chrono>
#include <map>
using namespace std;

void printmap(map<int, int>listy);

void printmap(map<int, int> listy)
{
	for(auto iter = listy.begin(); iter != listy.end(); ++iter)
	{
		cout << iter->first << " ";
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

	//now we insert into map as keys, should sort automatically
	map <int, int> sortList;

	auto start1 = chrono::steady_clock::now();
	for(int i = 0; i < randomList.size(); i++)
	{
		//key is random num and value will always be
		//zero
		sortList[randomList[i]] = 0;
	}
	auto end1 = chrono::steady_clock::now();
	auto elaspTime1 =end1 -start1;
	
	cout << "This is our sorted list: ";
	printmap(sortList);

	//now generate a random list of position to remove from list
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

    //remove positions in sortlist one by one recording time	
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
