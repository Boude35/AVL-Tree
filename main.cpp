#include "SplayNode.hpp"
#include "SplayTree.hpp"
#include "AVLTree.hpp"
#include "AVLNode.hpp"

#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[])
{
	AVLTree Atree; // new AVl tree
	SplayTree Stree;//new SPlay tree
	SoccerTeam equipo;//new SoccerTeam
	string myFile;//striing that will store the file name
	int totalavl = 0;//total count of nodes (AVL)
	int totalsplay = 0;//total countof nodes(SPLAY)
	cout<<"Welcome To PolyCalc!"<<endl;
	char prompt;//store Posible imputs
	do// ask continiuly for a promp until it is equal to Q
	{
		cout<< ">>> ";
		cin >> prompt;//ask the user 
		switch(prompt)
		{
		
			case 'F':
				{
					cout<< "Please Insert the name of your File: ";//ask the user for the name
					cin >> myFile;//ask for the name
					ifstream theReader( myFile.c_str() );//create the reader
					theReader >> equipo;//pass the first value
					while(theReader)//while it has values
					{
						Atree.insert(equipo);//insert to the avl tree
						Stree.insert(equipo);//insert to the splay tree
						theReader >> equipo;//pass the next value
					
					}
					theReader.close();//close the reader
				break;
				}
			case 'L':
				{
					SoccerTeam patata;//new soccerTeam
					cin >> patata.name();//ask for a name to this Team
					//totalsplay += Stree.visited2(patata);// calculate the node visited during the search of this soccerTeam in the splay
					Stree.lookup(patata);//look up for this value in the splay tree
					totalavl += Atree.visited2(patata);// calculate the node visited during the search of this soccerTeam in the splay
					cout << "Total AVL nodes accessed during searches: " << totalavl << endl;
					cout << "Total Splay nodes accessed during searches: " << totalsplay << endl;
					
				}
				break;	
			case 'Q'://quit
				cout<<"Thank you, Have a good day!"<<endl;
				break;
				
			default://other values that is not one of the above
			cout<<"Invalid Character"<<endl;
		}
	}while(prompt != 'Q');
	return 0;
}
