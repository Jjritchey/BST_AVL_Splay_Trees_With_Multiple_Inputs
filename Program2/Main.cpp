//Justin Ritchey - Program 2 - 11/7/2020 - Program designed to make 3 trees (BST, AVL and Splay). It will take 2 inputs and make 4 outputs

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "bst.cpp"


using namespace std;

void datCheck(string&);                                              //Funciton to check for .dat
bool fileCheck(ifstream&);                                           //function to check if the file exisits
bool fileEmpty(ifstream&);                                           //function to check if the file is empty
void secondFileCheck(ifstream&, ofstream&);                          //function to check if the second input file has the correct format
void rotations(string, ofstream&);                                   //function to check and print out the rotatations of the splay tree


int main()
{
	string filename = "";                                            //holds the name of the file before checking if the file exists
	ifstream file1;                                                  //holds the first input file
	ifstream file2;                                                  //holds the second input file
	ofstream file2_Checked;                                          //holds the second input file after it has been checked.
	file2_Checked.open("InputFile2.dat");                            //opens the file
	ifstream file2_checkIn;                                          //opening the new second file
	ofstream bstOut;                                                 //holds the output file for the BST tree
	ofstream avlOut;                                                 //holds the output file for the AVL tree
	ofstream splayOut;                                               //holds the output file for the Splay Tree
	ofstream summOut;                                                //holds the output file for the Summary page       
	string line = "";                                                //Holds the value for each line of the files
	BstTree t;                                                       //BST tree
	BstTree a;                                                       //AVL Tree
	BstTree s;                                                       //Splay tree
	int theight = 0;                                                 //holds the value of the tree height
	string rotstr = "";                                              //holds the rotations of the splay tree
	int sumArray[4][3];                                              //array to hold summary info
	int count = 0;

	                                                                 //summary variables
	int splaySearchOp =0, avlDeleteOp=0, splayDeleteOp=0, splayInsertOp = 0, bstInsertOp = 0, avlSearchOp=0, avlInsertOp=0, bstDeleteOp=0, bstSearchOp=0;


	cout << "Welcome to the BST, AVL and Splay tree program!\n\n";   //opens the program with a welcome message

	cout << "Please enter the name of the first input file: ";       //requests name of the first file
	cin >> filename;
	datCheck(filename);                                              //checks if the user entered a .dat or not. If not it will add a .dat to the name
	file1.open(filename);                                            //opens the first input file

	if (fileCheck(file1) == true)                                    //ends the program if the program cannot find the file
	{
		return 0;
	}

	cout << "Please enter the name of the second input file: ";      //requests for the name of the second input file
	cin >> filename;
	datCheck(filename);                                              //checks if the user entered a .dat or not. If not it will add a .dat to the name
	file2.open(filename);                                            //opens the second input file

	if (fileCheck(file2) == true)                                    //ends the program if the program cannot find the file
	{
		return 0;
	}

	if ((fileEmpty(file1) == true) && (fileEmpty(file2) == true))    //if both files are empty it will end the program
	{
		cout << "The files are empty, the program will be terminated";
		return 0;
	}


	cout << "Enter name for the BST tree output file: ";             //gathering name for the BST tree output file
	cin >> filename;
	datCheck(filename);
	bstOut.open(filename);

	cout << "Enter name for the AVL tree output file: ";             //Gathering name for the AVL tree output file
	cin >> filename;
	datCheck(filename);
	avlOut.open(filename);

	cout << "Enter name for the Splay tree output file: ";           //Gathering name for the Splay tree output file          
	cin >> filename;
	datCheck(filename);
	splayOut.open(filename);

	cout << "Enter name for the Suammry output file: ";              //Gathering name for the summary output file
	cin >> filename;
	datCheck(filename);
	summOut.open(filename);

	cout << endl;                                                    //putting a space after all inputs and outputs from the user
	
	while (getline(file1, line))                                     //getting each line and turning it into an integer
	{
		stringstream num(line);                                      //turning the string into an int
		int x = 0;
		num >> x; 

		cout << "Insert: " << x << "\n\n";                           //displaying the node number to be inserted
		bstOut << "Insert: " << x << "\n\n";
		t.createBstTree(x, bstInsertOp);                                          //creating the BST tree using the first file going line by line
		t.printTree(bstOut);                                         //printing the tree after each insert
		cout << "\nTree Height: " << t.treeHeight();                 //printing the tree height after each insert
		bstOut << "\nTree Height: " << t.treeHeight();

		cout <<  "\n\n-------------------------\n\n";                //formatting each tree output
		bstOut << "\n\n-------------------------\n\n";
		bstInsertOp++;

		cout << bstInsertOp;
		cout << "\n\n-------------------------\n\n";

	}                         

	cout << "First file is complete. Opening second file now: ";
	bstOut << "First file is complete. Opening second file now: ";
	cout << "\n\n-------------------------\n\n";                     //formatting each tree output
	bstOut << "\n\n-------------------------\n\n";


	
	 secondFileCheck(file2, file2_Checked);                          //Getting rid of any lines in the second file that don't start with i, d or s
	 file2_checkIn.open("InputFile2.dat");

	 while (getline(file2_checkIn, line))                            //loop to go through the second input file and sort each line
	 {
		 t.sortInputFile(line, bstOut, count);
		 cout << "\n";
		 bstOut << "\n";
		 t.printTree(bstOut);
		 cout << "\nTree Height: " << t.treeHeight();
		 bstOut << "\nTree Height: " << t.treeHeight();

		
		 if (line[0] == 'i' || line[0] == 'I')
		 {
			 bstInsertOp += count;
			 bstInsertOp++;
			 
		 }
		 else if (line[0] == 'd' || line[0] == 'D')
		 {
			 bstDeleteOp += count;
			 bstDeleteOp++;
		 }
		 else
		 {
			 bstSearchOp += count;
			 bstSearchOp++;
		 }
		 cout << "\n" << count + 1;

		 cout << "\n\n-------------------------\n\n";                 //formatting each tree output
		 bstOut << "\n\n-------------------------\n\n";

		 count = 0; 
	 }

	 cout << "\n\nStarting AVL tree: \n\n";
	 avlOut << "\n\nStarting AVL tree: \n\n";
	 cout << "\n\n-------------------------\n\n";                     //formatting each tree output
	 avlOut << "\n\n-------------------------\n\n";

	 file1.clear();
	 file1.seekg(0, std::ios::beg);

	 while (getline(file1, line))                                     //loop to make an AVL tree
	 { 
		 stringstream num(line);                                      //turning the string into an int
		 int x = 0;
		 num >> x;

		 cout << "Insert: " << x << "\n\n";                           //displaying the node number to be inserted
		 avlOut << "Insert: " << x << "\n\n";

		 a.insertAvlNode(x, avlOut, avlInsertOp);
		 a.printTree(avlOut);
		 cout << "\nTree Height: " << a.treeHeight();                 //printing the tree height after each insert
		 avlOut << "\nTree Height: " << a.treeHeight();


		 avlInsertOp++;

		 cout << "\n" << avlInsertOp;

		 cout << "\n\n-------------------------\n\n";                 //formatting each tree output
		 avlOut << "\n\n-------------------------\n\n";
	 }

	 cout << "First file is complete. Opening second file now: ";
	 avlOut << "First file is complete. Opening second file now: ";
	 cout << "\n\n-------------------------\n\n";                     //formatting each tree output
	 avlOut << "\n\n-------------------------\n\n";


	 file2_checkIn.clear();
	 file2_checkIn.seekg(0, std::ios::beg);

	 while (getline(file2_checkIn, line))                            //loop to go through the second input file and sort each line
	 {
		 a.sortAvlInputFile(line, avlOut, count);

		 cout << "\n";
		 avlOut << "\n";

		 a.printTree(avlOut);

		 if (line[0] == 'i' || line[0] == 'I')
		 {
			 avlInsertOp += count;
			 avlInsertOp++;
		 }
		 else if (line[0] == 'd' || line[0] == 'D')
		 {
			 avlDeleteOp += count;
			 avlDeleteOp++;
		 }
		 else
		 {
			 avlSearchOp += count;
			 avlSearchOp++;
		 }
		 cout << "\n" << count + 1;
		 count = 0;

		 cout << "\nTree Height: " << a.treeHeight();
		 avlOut << "\nTree Height: " << a.treeHeight();

		 cout << "\n\n-------------------------\n\n";                 //formatting each tree output
		 avlOut << "\n\n-------------------------\n\n";
	 }

	 cout << "\n\nStarting Splay tree: \n\n";
	 splayOut << "\n\nStarting Splay tree: \n\n";
	 cout << "\n\n-------------------------\n\n";                    //formatting each tree output
	 splayOut << "\n\n-------------------------\n\n"; 

	 file1.clear();
	 file1.seekg(0, std::ios::beg);

	 while (getline(file1, line))                                    //loop to make an Splay tree
	 {
		 stringstream num(line);                                     //turning the string into an int
		 int x = 0;
		 num >> x;

		 cout << "Insert: " << x << "\n\n";                        
		 splayOut << "Insert: " << x << "\n\n";

		 s.insertSplayNode(x, splayOut, rotstr, splayInsertOp);
		 s.printTree(splayOut);

		 rotations(rotstr, splayOut);
		 splayInsertOp += rotstr.length();
		 splayInsertOp++;
		 rotstr = "";

		 cout << "\nTree Height: " << a.treeHeight();
		 splayOut << "\nTree Height: " << a.treeHeight();

		 cout << "\n" << splayInsertOp;

		 cout << "\n\n-------------------------\n\n";                 //formatting each tree output
		 splayOut << "\n\n-------------------------\n\n";
	 }


	 file2_checkIn.clear();
	 file2_checkIn.seekg(0, std::ios::beg);

	 cout << "First file is complete. Opening second file now: ";
	 splayOut << "First file is complete. Opening second file now: ";
	 cout << "\n\n-------------------------\n\n";                     //formatting each tree output
	 splayOut << "\n\n-------------------------\n\n";

	 while (getline(file2_checkIn, line))                            //loop to go through the second input file and sort each line
	 {
		 s.sortSplayInputFile(line, splayOut, rotstr, count);

		 cout << "\n";
		 splayOut << "\n";

		 s.printTree(splayOut);

		 rotations(rotstr, splayOut);                                //getting rotations to print out
		 if (line[0] == 'i' || line[0] == 'I')
		 {
			 splayInsertOp += rotstr.length();
			 splayInsertOp += count;
			 splayInsertOp++;
		 }
		 else if (line[0] == 's' || line[0] == 'S')
		 {
			 splaySearchOp += rotstr.length();
			 splaySearchOp += count;
			 splaySearchOp++;
		 }
		 else
		 {
			 splayDeleteOp += rotstr.length();
			 splayDeleteOp += count;
			 splayDeleteOp++;
		 }
		 cout << "\n" << rotstr.length() + count + 1;
		 rotstr = "";
		 count = 0;

		 cout << "\nTree Height: " << s.treeHeight();
		 splayOut << "\nTree Height: " << s.treeHeight();

		 cout << "\n\n-------------------------\n\n";                 //formatting each tree output
		 splayOut << "\n\n-------------------------\n\n";
	 }

	 cout << "Trees have been completed here is the summary: \n\n";
	 summOut << "Trees have been completed here is the summary: \n\n";

	 sumArray[0][0] = bstSearchOp;                                 //assiging info to array
	 sumArray[0][1] = avlSearchOp;
	 sumArray[0][2] = splaySearchOp;
	 sumArray[1][0] = bstInsertOp;
	 sumArray[1][1] = avlInsertOp;
	 sumArray[1][2] = splayInsertOp;
	 sumArray[2][0] = bstDeleteOp;
	 sumArray[2][1] = avlDeleteOp;
	 sumArray[2][2] = splayDeleteOp;

	 sumArray[3][0] = bstInsertOp + bstDeleteOp + bstSearchOp;
	 sumArray[3][1] = avlInsertOp + avlDeleteOp + avlSearchOp;
	 sumArray[3][2] = splayDeleteOp + splayInsertOp + splaySearchOp;


	 cout << "       BST  AVL  Splay\n";
	 summOut << "      BST  AVL  Splay\n";

	 for (int i = 0; i < 4; i++)                               //printing out array
	 {
		 if (i == 0)
		 {
			 cout << "Search: ";
			 summOut << "Search: ";
		 }
		 else if (i == 1)
		 {
			 cout << "Insert: ";
			 summOut << "Insert: ";
		 }
		 else if (i == 2)
		 {
			 cout << "Delete: ";
			 summOut << "Delete: ";
		 }
		 else
		 {
			 cout << "------------------------\n";
			 cout << "Total:  ";
			 summOut << "Total:  ";
		 }
		 for (int j = 0; j < 3; j++)
		 {
			 cout << sumArray[i][j] << "   ";
			 summOut << sumArray[i][j] << "   ";
		 }
		 cout << endl;
		 summOut << endl;
	 }


	 cout << "\n\nProgram has completed.Thank you for using the BST, AVLand splay tree program!\n\n";


}

void datCheck(string& fileName)                                      //function to check if the .dat was enetered by the user
{                                                                    //if not this will add the .dat to the name entered 
	string dat = ".dat";                                             //this does not account for any "dat" in the name of the file
	int find;

	find = fileName.find(dat);                                       //searchs the string for the "dat" phrase

	if (find > 0)                                                    //if any "dat"'s were found it will return
	{
		return;
	}
	else                                                             //else it will add a .dat to the end of the string
	{
		fileName = fileName + ".dat";
	}
}                            

bool fileCheck(ifstream& file)                                        //Checks if the file opened susscufuly 
{
	bool result = false;                                              //boolean variable to be returned

	if (file.fail())                                                  //if the program did not find the file name it will terminidate and print out why
	{
		result = true;
		cout << "The input file does not exist. The program will be terminated\n";
		return result;
	}

	return result;
}

bool fileEmpty(ifstream& file)
{
	bool result = false;

	file.seekg(0, file.end);                                         //checks if the file is empty
	if (file.tellg() == 0)
	{
		result = true;
		return result;
	}
	file.seekg(0);

	return result;
}

void secondFileCheck(ifstream& file, ofstream& file2)                //checks if the file has an i I, s S, or d D and then is followed by a space
{
	string line = "";

	while (getline(file, line))
	{
		switch (line[0])
		{
		case 's':
		case 'S':
		case 'd':
		case 'D':
		case 'i':
		case 'I':
			if (line[1] == ' ')
			{
				file2 << line << endl;
				break;
			}
			break;
		}
	}
}

void rotations(string s, ofstream& file)
{
	string tmp;
	int tmp2 = s.length() - 1;

	if (s.empty())
	{
		return;
	}

	cout << "\nRotations: ";
	file << "\nRotations: ";

	if (s.length() % 2 == 0)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s.length() % 2 == 0)
			{
				tmp = s[i];
				tmp += s[i + 1];

				switch (s[i])
				{
				case 'r':
					if (s[i + 1] == 'r')
					{
						cout << "Zag-Zag ";                     //right-right case
						file << "Zag-Zag ";
						break;
					}
					else
					{
						cout << "Zag-Zig ";                     //right left case
						file << "Zag-Zig ";
						break;
					}
				case 'l':
					if (s[i + 1] == 'l')
					{
						cout << "Zig-Zig ";                     //left-left case
						file << "Zig-Zig ";
						break;
					}
					else
					{
						cout << "Zig-Zag ";                     //left-right case
						file << "Zig-Zag ";
						break;
					}
				}
				tmp = "";
				i++;
			}

		}
	}
	else
	{
		for (int i = 0; i < tmp2; i++)
		{
			if (tmp2 % 2 == 0)
			{
				tmp = s[i];
				tmp += s[i + 1];

				switch (s[i])
				{
				case 'r':
					if (s[i + 1] == 'r')
					{
						cout << "Zag-Zag ";                     //right-right case
						file << "Zag-Zag ";
						break;
					}
					else
					{
						cout << "Zag-Zig ";                     //right left case
						file << "Zag-Zig ";
						break;
					}
				case 'l':
					if (s[i + 1] == 'l')
					{
						cout << "Zig-Zig ";                     //left-left case
						file << "Zig-Zig ";
						break;
					}
					else
					{
						cout << "Zig-Zag ";                     //left-right case
						file << "Zig-Zag ";
						break;
					}
				}
			}
			tmp = "";
			i++;
		}
	}

		if (s[s.length()] == 'r')                              //if the number is odd print out the last single rotation
		{
			cout << "Zag";
			file << "Zag";
		}
		else
		{
			cout << "Zig";
			file << "Zig";
		}

		cout << "\n";
}
	

