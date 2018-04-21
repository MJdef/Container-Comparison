#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <string>
using namespace std;

struct Person
{
	int height = 1;
	int weight = 1;
	string name = "now one chares";
	string greeting = "hello there";
	bool eats = true;
	bool works = true;
	bool dead = false;
	bool nice = true;
	int age;	
};

void printlist(vector<struct Person> listy)
{
	for(int i = 0; i < listy.size(); i++)
	{
		cout << listy[i].age << " ";
	}

	cout << endl;

}

int findP(vector<struct Person> listy,int temp)
{
	int index = -1;
	for(int i = 0; i < listy.size(); i++)
	{
		if(listy[i].age == temp)
		{
			index = i;
			break;
		}
	}

	return index;;
}

int main()
{	
	//set up the clock time as a seed
	//set up clock time as see
	typedef chrono::system_clock clock;
	auto seed = chrono::time_point_cast<chrono::milliseconds>(clock::now()).time_since_epoch().count();

	//let's generate a random N 
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(1,10);
	int n = distribution(generator);

	//now we need our random numbers, no repeats
	//all placed in a vector of persons
	vector<Person> randomList;
	int temp;

	for(int i = 0; i < n; i++)
	{
		temp = distribution(generator);
		int index = findP(randomList,temp);
		if(index == -1) //this means that element isn't in list
		{
			struct Person johnDoe;
			johnDoe.age = temp;
			randomList.push_back(johnDoe);
		}else
		{
			i--;
		}
	}
	cout << "List size is: " << n <<endl;
	cout << "This is our random list: ";
	printlist(randomList);	

	//now we will try sorting these Persons as we insert them into a new 
	//vector, comparing them by age
	vector<struct Person> sortList;
	sortList.insert(sortList.begin(), *(randomList.begin()));

	auto start1 = chrono::steady_clock::now();
	for(int i = 1; i < n; i++)
	{
		struct Person temp = randomList[i];

		if(temp.age < sortList[0].age)
		{
			sortList.insert(sortList.begin(), temp);
		}else
		{
			int index;
			int j;
			for(j = 0; j < sortList.size(); j++)
			{
				if(temp.age > sortList[j].age)
				{
					index = j + 1;
				}
			}
			sortList.insert(next(sortList.begin(), index), temp);
		}
	}
	auto end1 = chrono::steady_clock::now();
	auto elaspTime1 = end1 - start1;
	
	cout << "This is our sorted list: ";
	printlist(sortList);

	//now generate random positions to remove from list
	//holding postions in a vector now
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

	//remove the positions
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
	


}
