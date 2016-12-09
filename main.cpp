#include <iostream>
#include <map> 
#include <fstream>
#include <vector>

using namespace std;



vector<string> seperate(string);


int main(){

	//vectors to store transaction
	vector<string> transaction;

	//vector to store unique modules
	vector<string> uniqueModules;

	//vectors to store the left modules
	vector<string> leftModules;

	//map to store the right modules
	map<string, int> rightModules;

	//vector to store the seperated modules 
	vector<string> seperatedModules;

	//the pair of modules fromt he inp.txt file
	string modulesPairs;

	ifstream infile ("inp.txt");
	
	bool asteriskIncountered = false;

	while (getline(infile, modulesPairs)){

		//if ** is incountered
		if (modulesPairs == "**"){
			asteriskIncountered = true;
		}
			else{
			if (asteriskIncountered == false){
					
				//seperating the two modules 
				seperatedModules = seperate(modulesPairs);

				//puting the left modules in the vector 
				leftModules.push_back(seperatedModules[0]);
				//putting the right modules in the map
				rightModules[seperatedModules[1]] = 1;
			}
			if (asteriskIncountered == true){
				 cout << "defective module: " << modulesPairs << endl;
			}
		}
	}

	cout << "all left modules" << endl;
	for(int i = 0; i < leftModules.size(); i++){		
		cout << leftModules.at(i) << endl;
	}

	cout << "transaction" << endl;

	for(int i = 0; i < leftModules.size(); i++){
		if (rightModules.find(leftModules.at(i)) == rightModules.end()){
			if (find(transaction.begin(), transaction.end(),leftModules.at(i))!=transaction.end()){
			}
			else{
				transaction.push_back(leftModules.at(i));
				cout <<leftModules.at(i)<< endl;
			}	
			
		}
	}

	cout << "unique modules"<<endl;

	for (map<string, int>::iterator it = rightModules.begin(); it != rightModules.end(); ++it) {
		cout << it->first << endl;
		
		// if (find(transaction.begin(), transaction.end(),it->first)!=transaction.end()) {
		// }
		// else{
		// 	if(find(uniqueModules.begin(), uniqueModules.end(),it->first)!=uniqueModules.end()){

		// 	}
		// 	else{
		// 		uniqueModules.push_back(it->first);
		// 		cout << it->first << endl;
		// 	}
		// }
	}


	return 0;
}




//the function to break down the modules pair to left and right modules 
vector<string> seperate(string a){
	string left, right;
	bool space = false;
	vector<string> modulesPair;

	int modulePairSize = (int)a.size();

	for (int i = 0; i< modulePairSize; i++){
		if (space){
			right += a[i];
		}

		if (a[i] == ' '){
			space = true;
		}

		if (!space){
			left += a[i];
		}

	}

	modulesPair.push_back(left);
	modulesPair.push_back(right);
	return modulesPair;
}