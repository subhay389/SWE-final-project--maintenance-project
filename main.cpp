#include <iostream>
#include <map> 
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>


using namespace std;

void get_all_paths(string transaction, string defective, unordered_map<string, vector<string> > module_tree, vector<string> nodes);

void print_all_paths_until(string u, string d, unordered_map<string, bool> visited, string* path, int &path_index, unordered_map<string, vector<string> > module_tree);

vector<string> seperate(string);

unordered_map<string, vector<string> > get_module_tree(string file_name);

void get_explosion(string transaction, unordered_map<string, vector<string> > module_tree, vector<string> nodes);

int main(){

	string defective;
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
	bool dt = true;
	ifstream infile ("inp.txt");
	
	bool asteriskIncountered = false;
	string defectivetransaction;
	while (getline(infile, modulesPairs)){
		defectivetransaction = modulesPairs;
		
		if (dt){
			defective = modulesPairs;
		}
		//if ** is incountered

		if (modulesPairs == "* *"){
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
				dt = false;
			}
		}
	}
	cout << "transaction for explosion: " << defectivetransaction << endl;
	cout << "defective module: " << defective << endl;

	// cout << "all left modules" << endl;
	// for(int i = 0; i < leftModules.size(); i++){		
	// 	cout << leftModules.at(i) << endl;
	// }

	cout << endl << "transactions:" <<  endl;

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

	cout <<endl<< "unique modules"<<endl;

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

	cout << endl <<"transaction and module relations" << endl;

	unordered_map<string, vector<string> > modules1;
    modules1 = get_module_tree("inp.txt");
    for(unordered_map<string, vector<string> >::const_iterator iter = modules1.begin() ; iter != modules1.end() ; iter++)
    {
        cout << iter->first << ":";
        for (vector<string>::const_iterator jter = iter->second.begin() ; jter != iter->second.end() ; jter++) {
            cout << *jter << " ";
        }
        cout << std::endl;
    }

    ///

    cout << endl<< "Path from Defective node " << defective << " to the transaction " <<defectivetransaction << endl;

    get_all_paths(defectivetransaction, defective, modules1, transaction);

    cout << endl << "explosion of transaction " << defectivetransaction << endl;

    get_explosion(defectivetransaction, modules1, transaction); 

    ///

	return 0;
}

// space between left and right module
//	key = left module value = all dependent modules 
unordered_map<string, vector<string> > get_module_tree(string file_name) {
     
    unordered_map<string, vector<string> > modules;
    vector<string> adjacency_list;
    
    ifstream file;

    string left_module, right_module;
    file.open(file_name);
    while (file) {
        file >> left_module >> right_module;

        if (left_module != "*") {
            if (left_module.size() <= 3 && right_module.size() <= 3) {
                modules[left_module].push_back(right_module);
            } else
                throw invalid_argument("invalid module entry");
        }
        else
            break;
    }
    return modules;
}

void get_all_paths(string transaction, string defective, unordered_map<string, vector<string> > module_tree, vector<string> nodes) {
	// initially all nodes = not visited
    unordered_map<string, bool> visited;
    
    // path = stores unique path
    string* path = new string[nodes.size()];
    int path_index = 0; // Initialize path[] as empty
    
    print_all_paths_until(transaction, defective, visited, path, path_index, module_tree);
}


//recursive function to find the unique path
void print_all_paths_until(string u, string d, unordered_map<string, bool> visited, string* path, int &path_index, unordered_map<string, vector<string> > module_tree) {
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    
    if (u == d)
    {
        for (int i = 0; i < path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else 
    {
        vector<string>::iterator i;
        for (i = module_tree[u].begin(); i != module_tree[u].end(); ++i)
            if (!visited[*i])
                print_all_paths_until(*i, d, visited, path, path_index, module_tree);
    }
   
    path_index--;
    visited[u] = false;
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


void get_explosion(string transaction, unordered_map<string, vector<string> > module_tree, vector<string> nodes) {
    // Mark all the vertices as not visited
    vector<string> visited;
    stack<unordered_map<string, int> > stack_modules;
    
    unordered_map<string, int> root;
    root[transaction] = 0;
    stack_modules.push(root);
    
    while (!stack_modules.empty()) {
        unordered_map<string, int> module = stack_modules.top();
        stack_modules.pop();
        string vertex;
        int space = 0;
        for (auto& x: module) {
            vertex = x.first;
            space = x.second;
        }
        // Print space and then the module name
        for (int i = 0; i < space; i++) {
            cout << ' ';
        }
        cout << vertex << endl;
        
        if (find(visited.begin(), visited.end(), vertex) == visited.end()) {
            // if vertex not in visited
            visited.push_back(vertex);
            
            unordered_map<string, vector<string> >::const_iterator has_key = module_tree.find(vertex);
            // If vertex is in module_tree
            if (has_key != module_tree.end()) {
                for (auto it = module_tree[vertex].rbegin(); it != module_tree[vertex].rend(); ++it)
                {
                    if (find(visited.begin(), visited.end(), *it) == visited.end()) {
                        // if vertex not in visited
                        unordered_map<string, int> module;
                        module[*it] = space + 1;
                        stack_modules.push(module);
                    } else {
                        // Printing session
                        for (int i = 0; i < space + 1; i++) {
                            cout << ' ';
                        }
                        cout << *it << '*' << endl;
                    }

                }
            }
        }
    }


}


