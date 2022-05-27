#include <iostream>
#include <string>

using namespace std;

const int SHINGLE_SIZE = 3;

double antiPlagiarism(string text, string fragment);
bool isSeparator(char c);
void printArrayOfStrings(string text[], int size);
int getStringLength(string text);
int howMuchWords(string text);
string canonizeText(string text);
string cutTheWord(string text, int position);

int main()
{
	string text = "I am going to the shop to buy some apples";
	string fragment = "I am going to the shop to buy some bananas";
	
	cout.precision(2);
	cout << "Amount of plagiat: " << antiPlagiarism(text, fragment) * 100 << "%";
	
	return 0;
}

double antiPlagiarism(string text, string fragment)
{
	int stringMatch = 0;
	int shingleMatch = 0;
	int numberOfShingles = 0;
	int position = 0;
		
	text = canonizeText(text);
	fragment = canonizeText(fragment);
	
	int textSize = howMuchWords(text);
	int fragmentSize = howMuchWords(fragment);
	if (fragmentSize == 0 or textSize == 0) {
			return 0.0;
		}

	string wordsOfText[textSize];
	string wordsOfFragment[fragmentSize];
	
	for (int i = 0; i < textSize; i++) {
		wordsOfText[i] = cutTheWord(text, position);
		position += getStringLength(wordsOfText[i]) + 1;
	}
	position = 0;
	for (int i = 0; i < fragmentSize; i++) {
		wordsOfFragment[i] = cutTheWord(fragment, position);
		position += getStringLength(wordsOfFragment[i]) + 1;
	}
	
	if (textSize > fragmentSize) {
		numberOfShingles = fragmentSize - SHINGLE_SIZE + 1;
	}	
	else {
		numberOfShingles = textSize - SHINGLE_SIZE + 1;
	}
	
	for (int i = 0; i < numberOfShingles; i++) {
		for (int j = 0; j < SHINGLE_SIZE; j++) {
			if (wordsOfText[i + j] == wordsOfFragment[i + j]) {
				stringMatch++;
				if (stringMatch == SHINGLE_SIZE) { 
					shingleMatch++;	
				}
			}	
		}
		stringMatch = 0;
	}
	
	return 1.0 * shingleMatch / numberOfShingles; 
}

string canonizeText(string text)
{	
	string canonizedText = "";
	string word = "";
	string space = " ";
	int position = 0;
	for (int i = 0; text[i] != 0; i++) {
		word = cutTheWord(text, i);
	}
	
	return canonizedText;
}


bool isSeparator(char c)
{
	char separators[] = ".,!;?{}()[] ";
	
	for (int i = 0; separators[i] != 0; i++)
		if (separators[i] == c)
			return true;
	return false;
}

void printArrayOfStrings(string text[], int size)
{
	for (int i = 0; i < size; i++) 
		cout << text[i] << endl;	
}

int getStringLength(string text)
{
	int i = 0;
	while (text[i] != 0)
		i++;
	return i;
}

int howMuchWords(string text)
{
	int counter = 0;
	if (text[0] == 0)
		return 0;
	for (int i = 0; text[i] != 0; i++)
		if (text[i] == 32 and text[i + 1] != 32) counter++;
	return counter + 1; 
}

string cutTheWord(string text, int position)
{	
	string word = "";
	while (!isSeparator(text[position])) {
		word += text[position];
		position++;
	}
	return word;
}
