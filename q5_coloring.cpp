#include <iostream>
#include <fstream>

using namespace std;

//we paint the board in levels: row1 and column1 as level1, row2and column2 as level2...
//so that the squares in each level decreases progressively 
//correspondingly, for different colors, the color with less left beads should br used later.
//	so each time a color is used, a check & switch function is run, in order to keep the order of the colors.

//ofstream outf("output_question_5_1.txt");
ofstream outf("output_question_5_2.txt");


char colors[10]; //colors
int ctc[10] = {0,0,0,0,0,0,0,0,0,0};//number of beads of corresponding colors
char grid[100][100]; //the grid

int penalty = 0;

void switchColor(int i1,int i2){ // switch the position of color[i1] and color[i2] in color[]
	char c; int tmp;
	c = colors[i1]; tmp = ctc[i1];
	colors[i1] = colors[i2]; ctc[i1]=ctc[i2];
	colors[i2]=c; ctc[i2]=tmp;
}

void sortColor(int color, char colors[10], int ctc[10]){// sort the colors, from more to less beads left
	cout<<"please input "<<color<<" colors and its amount of beads:"<<endl;
	for(int i=0; i<color; i++){
		cin>>colors[i]>>ctc[i];
	}
	char c;
	int tmp;
	for(int i=0; i<color-1; i++){
		for(int j=i+1; j<color; j++){
			if(ctc[i]<ctc[j]){
				switchColor(i, j);
			}
		}	
	}
}

void reSortColor(char c){ // everytime a color is used, check and reSort the colors to keep them in a decreasing order
					 	  // after reSorting, colors[0] will be the optimal choice everytime a bead is needed (if colors[0] is the same to a adjacent block, choose colors[1] instead)
	for(int i = 0; i<sizeof(colors)-1;i++){
		if(colors[i]==c){
			for(int j = i; j<sizeof(colors)-1;j++){
				if(ctc[j]<ctc[j+1]){
					switchColor(j, j+1);
				}
				else{
					break;
				}
			}
			break;
		}
	}
}

char fillGrid(int x, int y){ // fill grid[x][y] (x and y starts from 1)
	if(ctc[2]>0){// 3 or more colors left
		for(int i=0; i<2; i++){
			if(colors[i]!=grid[x-1][y] && colors[i]!=grid[x][y-1]){
				grid[x][y] = colors[i];
				ctc[i]--;
				reSortColor(colors[i]);
				return grid[x][y];
			}
		}
		// if it didn't fit above, colors[2] will definitly be needed
		grid[x][y] = colors[2];
		ctc[2]--;
		reSortColor(colors[2]);
		return grid[x][y];
	}
	
	else if(ctc[2]==0 && ctc[1]>0){// exactly 2 colors left
		for(int i=0; i<2; i++){
			if(colors[i]!=grid[x-1][y] && colors[i]!=grid[x][y-1]){
				grid[x][y] = colors[i];
				ctc[i]--;
				reSortColor(colors[i]);
				return grid[x][y];
			}
		}
		// if both colors[0]and[1] are infeasible, use colors[1](so that we don't need to reSortColors) and penalty++
		grid[x][y] = colors[1];
		ctc[1]--;
		penalty++;
		return grid[x][y];
	}
	
	else if(ctc[0]>0 && ctc[1]==0){ // only one color left
		grid[x][y] = colors[0];
		ctc[0]--;
		if(grid[x][y] == grid[x-1][y]) penalty++;
		if(grid[x][y] == grid[x][y-1]) penalty++;
	}
	return grid[x][y];
}

int main(){
	int color;
	int L;
	cout<<"input L:";
	cin>>L;
	cout<<"input number of colors:";
	cin>>color;
	//int penalty = 0;
	sortColor(color,colors,ctc);// sort the colors

	for(int i=1; i<=L;i++){// the true grid starts with grid[1][1]
		grid[0][i] = '0';
		grid[i][0] = '0';
	}
	
	// start filling the grid
	// grid[1][1] = colors[0]; // fill [1,1] with the color with the most beads
	//ctc[0]--;
	//reSortColor(colors[0]); // put colors[0] in the right place
	
	for(int i=1; i<=L;i++){
		for(int j=1; j<=L; j++){
			grid[i][j] = fillGrid(i,j);
			outf<<grid[i][j];
			if(j==L) outf<<endl;
			else outf<<" ";
		}
	}
	cout<<"penalty:"<<penalty;
	
	return 0;
}


