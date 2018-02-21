#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

     /////////////////////////////////////////////////////
    ///// Kernighan-Lin (KL) Algorithm    	    /////
   ///// Author: S Venkata Satish Kumar Pasumarthi /////
  /////////////////////////////////////////////////////


//Function to check if an edge exists in the input edge list
//returns true or false
bool find_in_list(int val,list<int>& set){
	if(find(set.begin(),set.end(),val) == set.end()){
		return false;
	}else{
		return true;
	}
}

//Update the cut list, when the nodes are swapped in a particular pass
void find_cut_list(vector< pair<int,int> > el,list<int> sa,list<int> sb,vector< pair<int,int> >& cl){
	cl.clear();
	for (int i=0; i < el.size() ; i++) {
		int ele1 = el[i].first;
		int ele2 = el[i].second;
		if(!((find_in_list(ele1,sa) && find_in_list(ele2,sa)) || (find_in_list(ele1,sb) && find_in_list(ele2,sb)))) {
			for(int i=0;i<el.size();i++){
				if((el[i].first== ele1 && el[i].second==ele2 )|| (el[i].first==ele2 && el[i].second==ele1)){
					cl.push_back(make_pair(ele1,ele2));
				}
			}
		}
	}
}

//Update D values for nodes
void get_D_values(vector< pair<int,int> > el,vector< pair<int,int> > cl,map<int,int>& nf){
	map<int,int>::const_iterator miter;
	int node;
	for(miter=nf.begin();miter!=nf.end();miter++){
		node = miter->first;
		nf[miter->first] = 0;
		
		for(int i=0;i<cl.size();i++){
			if(cl[i].first == node || cl[i].second == node) {
				nf[miter->first] += 2;
			}
		}
	
		for(int i=0;i<el.size();i++){
			if(el[i].first == node || el[i].second == node) {
				nf[miter->first] -= 1;
			}
		}	
	}	
	
}

// function to check if an edge exists in the Graph if vertices are given
// return true if edge exists
bool check_if_edge_exists(vector<pair<int,int> >el,int v1,int v2){
	for (int i=0;i<el.size();i++){
		if((el[i].first==v1 && el[i].second == v2 )|| (el[i].first==v2 && el[i].second==v1)) {
			return true;
		}
	}
	return false;
}

//Function to swap the nodes in the sets
void swap_nodes(list<int>& l1,list<int>& l2,int n1,int n2){
	list<int>::iterator vliter;
	for(vliter=l1.begin();vliter!=l1.end();++vliter){
		if(*vliter == n1) {
			*vliter = n2;
		}
	}		
	for(vliter=l2.begin();vliter!=l2.end();++vliter){
		if(*vliter == n2) {
			*vliter = n1;
		}
	}		
}

int main(int argc,char* argv[]){
	string line;
	int count = 0;//initialize to count the line and detect inputs accordingly
	int edge_count,node_count;
	char* token[2] = {};// array to store values in infile	
	char oneline[100]; // need this because strtok cannot handle strings
	vector < pair<int,int> > edge_list;
	vector < pair<int,int> > cut_list;
	vector < pair<int,int> > tmp_cut_list;
	vector < pair<int,int> > tmp_fixed_list;
	vector < pair<pair<int,int>,int> > info;
	map<int,int> tmp_not_fixed_list;
	list<int> nodes;
	list<int> setA;
	list<int> setB;
	list<int> tmp_setA;
	list<int> tmp_setB;
	list<int> fnodes;//Fixed nodes
	list<int> nfnodes;//Not fixed nodes
	int val1,val2;
	list<int>::const_iterator liter;//list iterator
	list<int>::iterator vliter;//list iterator
	list<int>::const_iterator liter1;//list iterator
	map<int,int>::const_iterator miter;//map iterator
	
	//Input arguments check
	if (argc < 2) {
		cout << "Atleast one argument is expected\n";
		cout << "Exiting...\n";
		cout << "Usage: " << argv[0] << " <input_file>\n";
		exit (1);
	}

	//Input file check
	ifstream infile;
	infile.open(argv[1]);//open the input file
	if(infile.fail()){
		cout << "Failed to open the input file\n";
		cout << "Please the file permissions\n";
		cout << "Exiting...\n";
		exit (1);
	}
	if(!infile.good()) {
		cout << "Input file doesn't exist. Please check..\n";
		cout << "Exiting...\n";
		exit (1); //exit if file not found
	}

	//Looping through input file
	while(getline(infile,line)){
		strcpy(oneline,line.c_str());
		token[0] = strtok(oneline," ");
		if(token[0]) {//zero if line is blank
			for(int n=1; n<2;n++) {
				token[n] = strtok(NULL," ");
				if(!token[n]) break;
			}
		}
		val1 = atoi(token[0]);
		val2 = atoi(token[1]);
		if(count!=0) {
			edge_list.push_back(make_pair(val1,val2));
			//edge_list.push_back(make_pair(val2,val1));
			if(nodes.size() < node_count) {	
				if(find(nodes.begin(),nodes.end(),val1) == nodes.end()){
					nodes.push_back(val1);
					tmp_not_fixed_list[val1]=0;
				}
				if(find(nodes.begin(),nodes.end(),val2) == nodes.end()){
					nodes.push_back(val2);
					tmp_not_fixed_list[val2]=0;
				}
			}
		}else{
			node_count = val1;
			edge_count = val2;
		}
		count++;
	}

	//split the nodes into two groups
	for (int i = 1; i <= node_count; i++){
		if(i<= node_count/2){
			setA.push_back(i);
		}else{
			setB.push_back(i);
		}
	}
	tmp_setA = setA;
	tmp_setB = setB;

	//Print Initial stats
	cout << "\n~*~*~*~*~*~*~*Summary*~*~*~*~*~*~* \n";
	cout << "No.of input nodes: " << node_count<<endl;
	cout << "No.of input edges: " << edge_count<<endl;
	cout <<"\nInitial setA: { ";
	for(liter = setA.begin(); liter!=setA.end(); ++liter){
		cout <<*liter << " ";
	}
	cout << "}\nInitial setB: { ";
	for(liter = setB.begin(); liter!=setB.end(); ++liter){
		cout << *liter << " ";
	}
	cout << "}"<<endl;

	//figure out cut list (initially from edge_list)
	find_cut_list(edge_list,setA,setB,cut_list);	
	cout << "Initial Cut Edge Pairs: { ";
	for (int i=0; i < cut_list.size() ; i++) {
		cout << "("<<cut_list[i].first<<","<<cut_list[i].second << ") ";
	}
	cout << "}\nInitial Cut size: "<<cut_list.size()<<endl;

	//initially D values for all the nodes is 0

	//get the initial D values
	get_D_values(edge_list,cut_list,tmp_not_fixed_list);
	int iter = 1;
	int gain,prev_gain,hit_gain,prev_loop_gain,loop_gain = 0;
	int v1,v2;
	while(hit_gain > 0 || tmp_not_fixed_list.size() != 0){
		prev_gain = -10000;
		loop_gain = -10000;
		for(liter=tmp_setA.begin();liter!=tmp_setA.end();++liter){		
			for(liter1=tmp_setB.begin();liter1!=tmp_setB.end();++liter1){
				if(tmp_not_fixed_list.find(*liter) !=tmp_not_fixed_list.end() && tmp_not_fixed_list.find(*liter1) !=tmp_not_fixed_list.end() )	{
					if(check_if_edge_exists(edge_list,*liter,*liter1)){
						gain = tmp_not_fixed_list[*liter]+tmp_not_fixed_list[*liter1]-2;
					}else{	
						gain = tmp_not_fixed_list[*liter]+tmp_not_fixed_list[*liter1];
					}
					//choose nodes only when the gain is higher
					if(gain > loop_gain){
						v1 = *liter;
						v2 = *liter1;
						loop_gain = gain;
					}
					prev_gain = gain;	
				}
			}
		}
		if(prev_loop_gain+loop_gain >= 0){
			hit_gain = prev_loop_gain+loop_gain;	
		}else{
			goto test;
		}
		prev_loop_gain = hit_gain;
		//info is a datastructure which consists of iteration,node1,node2,gain
		//iter->((v1,v2),g)
		info.push_back(make_pair(make_pair(v1,v2), hit_gain) );
		//updating setA and setB by swapping the vertices temporarily
		swap_nodes(tmp_setA,tmp_setB,v1,v2);
		//removing the fixed nodes from the not_fixed_list
		tmp_not_fixed_list.erase(v1);
		tmp_not_fixed_list.erase(v2);
		//updating the cut list
		find_cut_list(edge_list,tmp_setA,tmp_setB,tmp_cut_list);	
		//updating the D values for not_fixed_nodes
		get_D_values(edge_list,tmp_cut_list,tmp_not_fixed_list);
		iter++;
	}//end of while
	test:
	int max_gain_iter = -1;
	int max_gain = 0;
	//find the max gain occurence index
	for(int i=0;i<info.size();i++){
		if(info[i].second > max_gain){
			max_gain = info[i].second;
			max_gain_iter = i;
		}
	}
	//swap the nodes till the point of max gain
	if(max_gain_iter != -1){
		for(int i=0;i <= max_gain_iter;i++){
			swap_nodes(setA,setB,(info[i].first).first,(info[i].first).second);
		}
	}
	cout << "\nAfter Partioning with Kernighan-Lin Algorithm ::\n";
	cout << "\nFinal setA: { ";
	for(liter = setA.begin(); liter!=setA.end(); ++liter){
		cout <<*liter<<" ";
	}
	cout << "}\nFinal setB: { ";
	for(liter = setB.begin(); liter!=setB.end(); ++liter){
		cout << *liter<<" ";
	}
	cout << "}"<<endl;
	cout << "Final Cut Edge Pairs: {";
	find_cut_list(edge_list,setA,setB,cut_list);	
	for (int i=0; i < cut_list.size() ; i++) {
		cout << " ("<<cut_list[i].first<<","<<cut_list[i].second << ") ";
	}
	cout << "}\nFinal Cut size: "<<cut_list.size()<<endl;
	cout << "\n~*~*~*~*~*~*End of Summary*~*~*~*~*~* \n\n";

}//End of main
