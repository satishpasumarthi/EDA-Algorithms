#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <stack>
#include <limits.h>
#include <set>

using namespace std;

     /////////////////////////////////////////////////////
    ///// A* Search Algorithm		    	    /////
   ///// Author: S Venkata Satish Kumar Pasumarthi /////
  /////////////////////////////////////////////////////

typedef pair<int,int > Pair;
typedef pair<double, pair<int,int> > pPair;

struct cell{
	Pair p;
	int dist;
};

class AStarSearch {
	public:
		int tmp;
		Pair s;
		Pair d;
		int nrow,ncol;
		vector<vector<int> > wt;
		cell **cellinfo;

		bool isValid(int r, int c) {
			if((r>=0)&&(r<nrow)&&(c>=0)&&(c<ncol)) return true;
			return false;
		}

		bool isFree(int r,int c,int x,int y) {
			if(wt[r][c]==0) {
				if(wt[x][y]==0) return true;
			}
			return false;
		}

		bool isBlocked(int r, int c) {
			if(wt[r][c] == -1) return true;
			return false;
		}	

		bool isDestination(int r,int c,Pair d){
			if(r == d.first && c == d.second) return true;
			return false;
		}

		int cal_h (int r,int c,Pair d){
			return(abs(r-d.first)+abs(c-d.second));
		}

		void printPath(cell **c,Pair d){
			cout << "The min cost path is :";
			int dx = d.first;
			int dy = d.second;
			stack<Pair> Path;
			while(!(c[dx][dy].p.first == dx && c[dx][dy].p.second == dy)){
				Path.push(make_pair(dx,dy));
				dx = c[dx][dy].p.first;
				dy = c[dx][dy].p.second;
			}
			Path.push(make_pair(dx,dy));
			while(!Path.empty()){
				pair<int,int> p = Path.top(); // Pop the top element from stack
				cout <<"(" <<p.first+1<<","<<p.second+1<<") ";
				Path.pop();
			}
			cout << endl;
			return;
		}
		//AStarSearch AS(wt,n_rows,n_columns,src,dest);
		//constructor
		AStarSearch(vector<vector<int> > weight_array,int n_rows,int n_col,Pair src,Pair dest){
			wt = weight_array;
			nrow = n_rows;
			ncol = n_col;
			s.first = src.first;
			s.second = src.second;
			d.first = dest.first;
			d.second = dest.second;
			cellinfo = new cell*[nrow];
			for (int i=0;i<nrow;i++) cellinfo[i] = new cell[ncol];
		}
		void start();
};

void AStarSearch::start(){
	
	//vector<vector<bool>,> closedList(nrow,ncol);
	vector<bool> nc(ncol,false);
	vector<vector<bool> > closedList(nrow,nc);
	//vector< vector< bool > > verified( nrow, vector<bool>( ncol, false ) );

	set<pPair> openList;
	openList.insert(make_pair(0,make_pair(s.first,s.second)));

	for (int i=0;i<nrow;i++){
		for(int j=0;j<ncol;j++){
			cellinfo[i][j].dist = INT_MAX;
			cellinfo[i][i].p.first = -1;
			cellinfo[i][j].p.second = -1;
		}
	}

	//Initializing the source
	int i = s.first;
	int j = s.second;
	cellinfo[i][j].dist = 0;
	cellinfo[i][j].p.first = i;
	cellinfo[i][j].p.second = j;
	
	//Iterate until the openList (solution space) is empty
	while(!openList.empty()){
		cout << "\n\nI am in while loop\n";
		//set always stores the values in ascending order
		pPair p = *openList.begin();	
		cout << p.second.first<<","<<p.second.second<<endl;
		openList.erase(openList.begin());
		//
		for (int k = 0; k < closedList.size(); k++)
		{
		    for (int l = 0; l < closedList[i].size(); l++)
		    {
		        cout << closedList[k][l]<< " ";
		    }
			cout <<endl;
		}
		//
		i = p.second.first;
		j = p.second.second;
		//Move the openList deleted item to closed List
		closedList[i][j] = true;
		if(isValid(i-1,j)) {
			cout << "I am in south\n";
			if(isDestination(i-1,j,d)){
				cout << "Dest reached\n";
				exit (0);
				cellinfo[i-1][j].p.first = i;
				cellinfo[i-1][j].p.second = j;
				printPath(cellinfo,d);	
				return;
			}else if(!(closedList[i-1][j]) && !(isBlocked(i-1,j))){
				if(isFree(p.second.first,p.second.second,i,j)) tmp = cellinfo[i][j].dist;
				else tmp = cellinfo[i][j].dist+1;
				if(cellinfo[i-1][j].dist == INT_MAX || cellinfo[i-1][j].dist > tmp  ) {
					cellinfo[i-1][j].dist = tmp;
					cellinfo[i-1][j].p.first = i;
					cellinfo[i-1][j].p.first = j;
					openList.insert(make_pair(tmp,make_pair(i-1,j)));
				}
			}
		}//South
		if(isValid(i+1,j)) {//North
			cout << "I am in North\n";
			if(isDestination(i+1,j,d)){
				cout << "Dest reached\n";
				exit (0);
				cellinfo[i+1][j].p.first = i;
				cellinfo[i+1][j].p.second = j;
				printPath(cellinfo,d);	
				return;
			}else if(!(closedList[i+1][j]) && !(isBlocked(i+1,j))){
				if(isFree(p.second.first,p.second.second,i,j)) tmp = cellinfo[i][j].dist;
				else tmp = cellinfo[i][j].dist+1;
				if(cellinfo[i+1][j].dist == INT_MAX || cellinfo[i+1][j].dist > tmp  ) {
					cellinfo[i+1][j].dist = tmp;
					cellinfo[i+1][j].p.first = i;
					cellinfo[i+1][j].p.first = j;
					openList.insert(make_pair(tmp,make_pair(i+1,j)));
				}
			}
		}//North
		if(isValid(i,j-1)) {//West
			cout << "I am in West\n";
			if(isDestination(i,j-1,d)){
				cout << "Dest reached\n";
				exit (0);
				cellinfo[i][j-1].p.first = i;
				cellinfo[i][j-1].p.second = j;
				printPath(cellinfo,d);	
				return;
			}else if(!(closedList[i][j-1]) && !(isBlocked(i,j-1))){
				if(isFree(p.second.first,p.second.second,i,j)) tmp = cellinfo[i][j].dist;
				else tmp = cellinfo[i][j].dist+1;
				if(cellinfo[i][j-1].dist == INT_MAX || cellinfo[i][j-1].dist > tmp  ) {
					cellinfo[i][j-1].dist = tmp;
					cellinfo[i][j-1].p.first = i;
					cellinfo[i][j-1].p.first = j-1;
					openList.insert(make_pair(tmp,make_pair(i,j-1)));
				}
			}
		}//West
		if(isValid(i,j+1)) {//East
			cout << "I am in East\n";
			if(isDestination(i,j+1,d)){
				cout << "Dest reached\n";
				exit (0);
				cellinfo[i][j+1].p.first = i;
				cellinfo[i][j+1].p.second = j+1;
				printPath(cellinfo,d);	
				return;
			}else if(!(closedList[i][j+1]) && !(isBlocked(i,j+1))){
				if(isFree(p.second.first,p.second.second,i,j)) tmp = cellinfo[i][j].dist;
				else tmp = cellinfo[i][j].dist+1;
				if(cellinfo[i][j+1].dist == INT_MAX || cellinfo[i][j+1].dist > tmp  ) {
					cellinfo[i][j+1].dist = tmp;
					cellinfo[i][j+1].p.first = i;
					cellinfo[i][j+1].p.first = j+1;
					openList.insert(make_pair(tmp,make_pair(i,j+1)));
				}
			}
		}//East
	}//while	
	
}
int main(int argc,char* argv[]) {
	string line;
	int count = 1;//initialize to count the line and detect inputs accordingly
	char* token[4] = {};// array to store values in infile	
	char oneline[100]; // need this because strtok cannot handle strings
	int val1,val2,val3,val4;

	//Input parameters
	int n_rows,n_columns; 
	int s_x,s_y,t_x,t_y;
	int bl_llx,bl_lly,bl_urx,bl_ury; //Blockage Bbox
	int fi_llx,fi_lly,fi_urx,fi_ury; //Free island Bbox
	
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
			for(int n=1; n<4;n++) {
				token[n] = strtok(NULL," ");
				if(!token[n]) break;
			}
		}
		switch(count) {
			case 1 :
				n_rows = atoi(token[0]);
				n_columns = atoi(token[1]);
				break;
			case 2:
				s_x = atoi(token[0]);
				s_y = atoi(token[1]);
				break;
			case 3:
				t_x = atoi(token[0]);
				t_y = atoi(token[1]);
				break;
			case 4:
				bl_llx = atoi(token[0]);
				bl_lly = atoi(token[1]);
				bl_urx = atoi(token[2]);
				bl_ury = atoi(token[3]);
				break;
			case 5:
				fi_llx = atoi(token[0]);
				fi_lly = atoi(token[1]);
				fi_urx = atoi(token[2]);
				fi_ury = atoi(token[3]);
				break;
		}//switch
		count++;
	}//while
	s_x--; s_y--; t_x--;t_y--;

	Pair src = make_pair(s_x,s_y);
	Pair dest = make_pair(t_x,t_y);
	vector<int> cV(n_columns,1);
	vector<vector<int> > wt(n_rows,cV);

	cout << s_x<< " "<<s_y<<endl;
	cout << n_rows<<" " <<n_columns<<endl;
	int i,j;

	//Blockage
	for (i=bl_llx-1;i< bl_urx; i++){
		for(j=bl_lly-1;j<bl_ury;j++){
			wt[i][j] = -1;
		}
	}

	//Free island
	for (i=fi_llx-1;i< fi_urx; i++){
		for(j=fi_lly-1;j<fi_ury;j++){
			wt[i][j] = 0;
		}
	}
	
	AStarSearch AS(wt,n_rows,n_columns,src,dest);
	AS.start();
}
