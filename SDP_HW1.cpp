#include<iostream>
#include<vector>
#include<fstream>
#include<iomanip>
#include<string>
#include<istream>
#include<stdio.h>
#include<cstdio>
#include<cstring>
#include<ctype.h>
#include<algorithm>


using namespace std;

int main()
{
	vector<string> anagram;
	ifstream file("input.txt", ifstream::in);
	if (!file)
	{
		cerr<< "File couldn't be opened";
		return 1;
	
	}

	string word;
	while (getline(file,word))
	{
			int lengthOfString = word.length();
			for (int i = 0; i < lengthOfString; i++)
			{
				if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
				{
					word[i] = toupper(word[i]);
				}
				else
				{
					cout << "Error";
				}
				
			}
			anagram.push_back(word);
	}

	file.close();

	sort(anagram.begin(), anagram.end());

	int lengthOfVector = anagram.size();

	for (int i = 0; i < lengthOfVector - 1; i++)
	{
		for (int j = i + 1; j < lengthOfVector; j++)
		{
			while (anagram[i].compare(anagram[j]) == 0)
			{
				cout << "anagram[" << i << "]=anagram[" << j << "]="<<anagram[i] << endl;
				for (int k = j; k < lengthOfVector-1; k++)
				{
					anagram[k] = anagram[k+1];
				}
				anagram.pop_back();
				lengthOfVector--;
			}
		}
	}

	for (int i = 0; i < lengthOfVector; i++)
	{
		string helper = anagram[i];
		sort(helper.begin(), helper.end());
		anagram[i] = helper;
	}

	int countAnagrams = 0;

	for (int i = 0; i < lengthOfVector-1; i++)
	{
		for (int j = i+1; j < lengthOfVector; j++)
		{
			if (anagram[i].compare(anagram[j]) == 0)
			{
				cout << "anagram[" << i << "]=" << anagram[i] << " = anagram[" << j << "]=" << anagram[j] << endl;
				countAnagrams++;
			}
			else
			{
				cout << "anagram[" << i << "]=" << anagram[i] << " != anagram[" << j << "]=" << anagram[j] << endl;
			}
		}
	}

	cout << "countAnagrams="<<countAnagrams;

	system("pause");
	return 0;

}
