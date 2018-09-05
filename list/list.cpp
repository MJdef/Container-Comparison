#include <iostream>
#include <random>
#include <chrono>
#include <list>

using namespace std;

void printlist(list<int> listy);

int main()
{

	//set up clock time as seed
	typedef std::chrono::system_clock clock;
	auto seed = chrono::time_point_cast<chrono::milliseconds>(clock::now()).time_since_epoch().count();;
	

	//first lets generate a random N
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,10);
	int n = distribution(generator);


	//now we need our random numbers, no repeats
	//all placed in a list
	list<int> randNumList = {};
	int temp;
	
	for(int i = 0; i < n; i++)
	{
		temp = distribution(generator);
		auto iterator = find(randNumList.begin(), randNumList.end(), temp);
		if(iterator == randNumList.end())
		{
			randNumList.push_back(temp);
		}else
		{
			i--;
		}
	}
	
	cout << "List size: " << n << endl;
	cout << "This is our random list: ";
	printlist(randNumList);

	//now insert one by one, sorting, into new list sortlist
	list<int> sortList = {};
	sortList.push_front(*(randNumList.begin())); //adding first elemet
	int tempNum; 

	//starting iterating random list from second num instead of first
	//record time here
	auto start1 = chrono::steady_clock::now();
	for(auto iter = next(randNumList.begin(),1); iter != randNumList.end(); ++iter)
	{
		tempNum = *iter;
		
		if(tempNum < *(sortList.begin()))
		{
			sortList.push_front(tempNum);
		}else
		{
			auto index = sortList.begin();
			for(auto iter2 = sortList.begin(); iter2 != sortList.end(); ++iter2)
			{
				if(tempNum > *iter2)
				{
					index = next(iter2,1); 
				}
			}
			sortList.insert(index, tempNum);
		}		
	}
	auto end1 = chrono::steady_clock::now();
	auto elaspTime1 = end1 - start1;

	cout << "This is our sorted list:";
	printlist(sortList);

	//generate a random list of positions to remove 
	//from list
	list<int> removeIndex = {};
	int tempp;
	int listLength = n;
	
	for(int i = 0; i < n;i++ )
	{
	    uniform_int_distribution<int> distri(0,listLength - 1);
		tempp = distri(generator);
		listLength-=1; //to make sure we don't pick an index out of list bounds
		removeIndex.push_back(tempp);
	}

	//remove positions in sortedList one by one according to position
	//record time
	auto start2 = chrono::steady_clock::now();
	for(auto iter = removeIndex.begin(); iter != removeIndex.end(); ++iter)
	{
		auto deleteIndex = next(sortList.begin(), *iter);
		sortList.erase(deleteIndex);
	}
	auto end2 = chrono::steady_clock::now();
	auto elaspTime2 = end2- start2;

	cout << "Duration to insert into list: "<< chrono::duration <double, milli> (elaspTime1).count() << "milliseconds\n";
	cout << "Duration to delete from list: "<< chrono::duration <double, milli> (elaspTime2).count() << "milliseconds\n"; 

	

	return 0;
}

void printlist(list<int> listy)
{
	for(auto iter = listy.begin(); iter != listy.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;
}
