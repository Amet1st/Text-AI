#include <iostream>
#include <string>

using namespace std;

const int SHINGLE_SIZE = 1;

double antiPlagiarism(string text, string fragment);
bool isSeparator(char c);
void printArrayOfStrings(string text[], int size);
int getStringLength(string text);
int howMuchWords(string text);
string canonizeText(string text);
string cutTheWord(string text, int position);
int howMuchSeparatorsBeforeWord(string text, int position);
bool isForbiddenWord(string text);
string wordToLowerCase(string text);

int main()
{
	string text = "I really like vaping on my way to university. And if it's an important event, I'll definitely have a cup of coffee.";
	string fragment = "I really like vaping on my way to university. And if it's an important event, I'll definitely have a cup of tea.";
	
	cout << "Amount of plagiat: " << antiPlagiarism(text, fragment) * 100 << "%" << endl;	
	
	return 0;
}

double antiPlagiarism(string text, string fragment)
{
	int wordMatch = 0;
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
				wordMatch++;
				if (wordMatch == SHINGLE_SIZE) { 
					shingleMatch++;	
				}
			}	
		}
		wordMatch = 0;
	}
	
	return 1.0 * shingleMatch / numberOfShingles; 
}

string canonizeText(string text)
{	
	string canonizedText = "";
	string space = " ";
	string word = "";
	
	for (int i = 0; text[i] != 0; i++) {
		if (!isSeparator(text[i])) {
			word += text[i];
			if (isSeparator(text[i + 1])) {
				if (!isForbiddenWord(word))
					canonizedText = canonizedText + wordToLowerCase(word) + space;
					word = "";
			}
			if (text[i + 1] == 0) {
				if (!isForbiddenWord(word))
					canonizedText = canonizedText + wordToLowerCase(word);
			}
		}
	}
	
	return canonizedText;
}


bool isSeparator(char c)
{
	char separators[] = "~`!@#$%^&*-_=+,./({[<>]})?\n0123456789 ";
	
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
	while (text[position] != 32 and text[position] != 0) {
		word += text[position];
		position++;	
	}
	return word;
}

bool isForbiddenWord(string text)
{	
	const int N = 12;
	string forbiddenWords[N] = {"the", "with", "under", "and", "for", "from", "between", "into", "out", "over", "that", "among"};
	for (int i = 0; i < N; i++)
		if (text == forbiddenWords[i])
			return true;
	if (getStringLength(text) < 3)
		return true;
	return false;
}

string wordToLowerCase(string text)
{
	for (int i = 0; i < getStringLength(text); i++) {
		if (text[i] >= 65 and text[i] <= 90) {
			text[i] = text[i] + 32;
		}
	}
	return text;
}


