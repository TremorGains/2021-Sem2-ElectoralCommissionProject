#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <vector>
using namespace std;
using std::ofstream;

class Candidate //Ryan 103600322: Using a class object to store data allows for an easy way to keep related data close by.
{
public:
	int ID;
	string symbol;
	string name;
	int age;
	string gender;
	string email;
	string address;
	string suburb;
	int postcode;
	int voteCount;
public:
	Candidate() : ID(), symbol(), name(), age(), gender(), email(), address(), suburb(), postcode(), voteCount() {} //Ryan 103600322: Allows for arrays and vectors to be made using class objects
	Candidate(int, string, string, int, string, string, string, string, int, int);
	int addVote();
	void showCandidate();

};
//Class Implementation section
Candidate::Candidate(int id, string party, string fullname, int age, string sex, string businessEmail, string address, string suburb, int pcode, int count) //Ryan 103600322: Candidate Class Constructor Function
{
	ID = id;
	symbol = party;
	name = fullname;
	Candidate::age = age;
	gender = sex;
	email = businessEmail;
	Candidate::address = address;
	Candidate::suburb = suburb;
	postcode = pcode;
	voteCount = count;
}


int Candidate::addVote() //Riley 102332352: Class function to update the vote count for a specific candidate
{
	cout << voteCount << endl;
	int newVote;
	cout << "Enter number of votes\n"; //Riley 102332352: Save new votes and add them to current votes, return that to add_candidate_votes function
	cin >> newVote;
	int newvoteCount = newVote + voteCount;
	cout << newvoteCount << endl;
	return newvoteCount;
}

void Candidate::showCandidate() //Ryan 103600322: Class function that shows the candidate's ID, name, and vote count
{
	cout << "Candidate " << ID << ": " << name << " has a total vote count of " << voteCount << endl;
}

void write_new_votes(vector<Candidate>&);
void print_candidate_num(vector<Candidate>);
void add_candidate_votes(vector<Candidate>&, vector<Candidate>);
void print_candidate_num(vector<Candidate>);
void display_smallest(vector<Candidate>&);
void display_largest(vector<Candidate>&);
Candidate getCandidates(int);


int main()
{

	unsigned char choice;
	int cont = 0;
	while (cont == 0) {
		vector<Candidate> candidates(10); //Ryan 103600322: Passing a vector with all the data from the text-file allows for the functions to easily access any information when needed
		for (int i = 0; i < 10; i++)
		{
			candidates[i] = getCandidates(i); //Ryan 103600322: Passing the integer variable i allows for the function to know how many lines in the file to skip before getting to the next candidates data
		}
		//Riley 102332352: Displaye the menu options in terminal, using a switch statement run various functions
		cout << "Enter your choice:";
		cout << "\nP :Display the votes for a Candidate";
		cout << "\nA :Add Votes to a Candidate";
		cout << "\nS :Display the Candidate with the smallest number of votes";
		cout << "\nL :Display the Candidate with the largest number of votes";
		cout << "\nQ: Exit" << endl;
		cin >> choice;
		choice = toupper(choice);  //Riley 102332352: Convert choice to upper case so both lower and upper characters can be used as inputs

		switch (choice) {
		case 'P':
			print_candidate_num(candidates); //Tim 103595473: Passing the Vector to the functions so that the data is accessible
			break;
		case 'A':
			add_candidate_votes(candidates, candidates);
			break;
		case 'S':
			display_smallest(candidates);
			break;
		case 'L':
			display_largest(candidates);
			break;
		default:
			cout << "Goodbye\n";
			cont = 1;

		}

	}

	return 0;
}

void print_candidate_num(vector<Candidate> candidate) { //Tim 103595473: Function for display the number of votes for a given candidate
	string name;
	int nameIndex;
	for (int i = 1; i < 11; i++)
	{
		cout << (i) << ": " << candidate[(i - 1)].name << endl; //Tim 103595473: cycles through the vector to list and display each candidate with an index number

	}
	cout << "Please Choose a Candidate by their Index Number: " << endl;
	cin >> nameIndex; //Tim 103595473: User input is stored in variable
	name = candidate[nameIndex - 1].name; //Tim 103595473: because the index begins with 1 but the vector count starts with 0, the values the user gave must be deducted by 1
	for (int i = 1; i < 11; i++) //Tim 103595473: For loop to cycle through the vector until the correct candidate is found.
	{
		if (candidate[i - 1].name == name) {
			candidate[i - 1].showCandidate();//Tim 103595473: When the if statment is true, the function will call the class function "showCandidate" which will display the candidate object's candidate ID, Name and Current Vote Total
			cout << endl;
		}
	}

}


void add_candidate_votes(vector<Candidate>& voteCount, vector<Candidate> candidate) { //Riley 102332352: Function for finding candidate and writing new votes to file
	string name;
	int nameIndex;
	int updatedVote;
	for (int i = 1; i < 11; i++) //Riley 102332352: Print candidates to terminal
	{
		cout << (i) << ": " << candidate[(i - 1)].name << endl;

	}
	cout << "Please Choose a Candidate by their Index Number: " << endl;
	cin >> nameIndex;
	name = candidate[nameIndex - 1].name;
	for (int i = 1; i < 11; i++) //Riley 102332352: Search for matching candidate, if one is found set updateVote to the value returned from addVote
	{
		if (candidate[i - 1].name == name) {
			updatedVote = voteCount[i - 1].addVote();
		}
	}
	ofstream file;
	file.open("Candidate_Table.txt");

	if (file.fail())
	{
		cout << "File was not opened correctly\n";
		exit(1);
	}
	else
	{
		cout << "Writing file, please wait a moment\n";
		for (int j = 1; j < 11; j++) //Riley 102332352: Update vote count in file matching the previous layout
		{
			file << "Candidate_ID: " << candidate[j - 1].ID << endl;
			file << "Symbol: " << candidate[j - 1].symbol << endl;
			file << "Name: " << candidate[j - 1].name << endl;
			file << "Age: " << candidate[j - 1].age << endl;
			file << "Gender: " << candidate[j - 1].gender << endl;
			file << "Buisiness_Email: " << candidate[j - 1].email << endl;
			file << "Address: " << candidate[j - 1].address << endl;
			file << "Suburb: " << candidate[j - 1].suburb << endl;
			file << "Postcode: " << candidate[j - 1].postcode << endl;
			if (candidate[j - 1].name == name) //Riley 102332352: If candidate name is the one chosen write the new vote to the file
			{
				file << "Vote_Count: " << updatedVote << endl;
			}
			else
			{
				file << "Vote_Count: " << candidate[j - 1].voteCount << endl;
			}
			file << "\n";
		}
		file.close();
	}
}

void display_smallest(vector<Candidate>& candidates) //Ryan 103600322: This functions compares the vote counts of each candidate and only keeps the ID of the candidate with least votes in the comparison, and then displaying the candidate after all the comparisons
{
	int smallestID;
	int smallestVotes;
	int tempID;
	int tempVotes;
	/*
		Ryan 103600322:
		The temp variables are used in order to obtain the latest candidate data and if the temp votes are smaller than the current value
		in the smallestVotes variable then smallestVotes would take the value from tempVotes and smallestID takes the value from tempID
	*/
	smallestID = candidates[0].ID;
	smallestVotes = candidates[0].voteCount;

	for (int i = 1; i < 10; i++)
	{
		tempID = candidates[i].ID;
		tempVotes = candidates[i].voteCount;

		if (smallestVotes > tempVotes)
		{
			smallestID = tempID;
			smallestVotes = tempVotes;
		}
	}

	cout << "Now displaying candidate with the least votes: \n";
	candidates[smallestID - 1].showCandidate();
	cout << endl;
}

void display_largest(vector<Candidate>& candidates) //Ryan Faraone: This function has essentially the same concepts as display_smallest() except for the comparison operator in the if statement, allowing for the candidate with the most votes to be displayed
{
	int largestID;
	int largestVotes;
	int tempID;
	int tempVotes;
	/*
		Ryan 103600322:
		The temp variables are used in order to obtain the latest candidate data and if the temp votes are larger than the current value
		in the largestVotes variable then largestVotes would take the value from tempVotes and largestID takes the value from tempID
	*/
	largestID = candidates[0].ID;
	largestVotes = candidates[0].voteCount;

	for (int i = 1; i < 10; i++)
	{
		tempID = candidates[i].ID;
		tempVotes = candidates[i].voteCount;

		if (largestVotes < tempVotes)
		{
			largestID = tempID;
			largestVotes = tempVotes;
		}
	}

	cout << "Now displaying candidate with the most votes: \n";
	candidates[largestID - 1].showCandidate();
	cout << endl;
}

Candidate getCandidates(int j) //Ryan 103600322: The purpose of this function is to collect all the useful data from the text-file and then assigne them to an object and return the value into a vecotr used to hold all the candidate objects
{
	Candidate candidate;
	string temp;
	int id;
	string symbol;
	string name;
	int age;
	string gender;
	string email;
	string address;
	string suburb;
	int postcode;
	int voteCount;
	ifstream file;

	/*
		Ryan 103600322:
		These variables are all used in order to collect data from the candidate text-file and put it into a class object.
		The string variable temp allows for any characters we don't need in the class objects to be stored somewhere out of the way from our main variables.
		Using an input fstream allows for the function to read in any data we require.
	*/

	file.open("Candidate_Table.txt");

	if (file.fail())
	{
		cout << "File was not opened correctly\n";
		exit(1);
	}

	j = j * 11;

	if (j != 0)
	{
		for (int i = 0; i < j; i++)
		{
			getline(file, temp);
		}
	}

	file >> temp >> id;
	file >> temp >> symbol;
	file >> temp;
	getline(file, name);
	file >> temp >> age;
	file >> temp >> gender;
	file >> temp >> email;
	file >> temp;
	getline(file, address);
	file >> temp >> suburb;
	file >> temp >> postcode;
	file >> temp >> voteCount;
	getline(file, temp);
	file.close();
	candidate = Candidate(id, symbol, name, age, gender, email, address, suburb, postcode, voteCount);

	return candidate;
}