#include <iostream>
#include <fstream>

using namespace std;

ifstream polygon("input_question_6_polygon.txt");
ifstream points("input_question_6_points.txt");
ofstream outf("output_question_6.txt");

// draw a left-directed horizontal ray l from the tested point P(xp, yp):
//		y = yp
// the answer of this question can be told by the number of intersection points between l and the given polygon m
// 	1. in general situations:
//		if m is odd: P is inside the polygon
//		else if m is even: P is outside the polygon
//	2. in special circumstances:
//		2.1 l crosses one or more polygon corners (from between the two edges of the angle)
//		2.2 l is a tangent line of the polygon (namely crosses one or more polygon corners from the same side of the two edges of the angle)
//		2.3 l coincides with one or more edges of the polygon (which indicates that these re-fitted edges are horizontal)
//	   solution to all these special situations:
//		for 2.1: 
//			***only one of the two nodes of each edge should be considered*** 
//			so that there is still only one intersection point.
//		for 2.2 and 2.3: 
//			based on the solution for 2.1 above
//			for each edge (not horizongtal), the node with bigger ordinate is counted;
//			for horizontal edges (namely the two ordinates are equal), both nodes are counted.
//				
//		

bool pointIn(float xp, float yp, // xp&yp: the abscissa and ordinate of the tested point;
			 float cnX[20], float cnY[20], // cnX&cnY: the abscissas and ordinates of the corners of the polygon;
			 float ctc){ // ctc: the count of corners of the polygon.											    														    
	bool isInside = 0;
	int i;
	int j = ctc - 1;
	for (i=0; i<ctc; i++){ // for each edge
		if (cnY[i] == cnY[j] && cnY[i] == yp){ // if the edge coincides with l
			if ((cnX[i]-xp)*(cnX[j]-xp) <= 0){ // if these two nodes are on different sides of P or one of them is the same as P
				isInside = 1; // P must be inside the polygon
				return isInside;
			}
		}
		else if ((cnY[i] < yp && cnY[j] >= yp) || (cnY[j] < yp && cnY[i] >= yp)){ // if the two nodes' ordinates are on seperate sides of P 
			//cout<<"i("<<cnX[i]<<","<<cnY[i]<<") j("<<cnX[j]<<","<<cnY[j]<<") ";
			float crossx = ((yp-cnY[i])*(cnX[i]-cnX[j])/(cnY[i]-cnY[j]) + cnX[i]); // the absciss of the intersection point
			//cout<<crossx<<" ";
			if (crossx == xp){ // if the intersection point is the same as P
				isInside = 1; // P must be inside the polygon
				return isInside;
			}
			else if(crossx<xp) { // if the intersection point is not the same as P
				isInside = !isInside;
				//cout<<isInside<<" ";
				//isInside ^= (crossx < xp);	// the answer to the equation is on the left side of the ray
			}
		}
		j = i;
	}
	return isInside;
} 

int main(){
	int ctc = 0;
	float cnX[20], cnY[20];
	while(!polygon.eof()){
		polygon>>cnX[ctc];
		polygon>>cnY[ctc];
		ctc++;
	}

	float xp, yp;
	while(points>>xp){
		points>>yp;
		bool isIn = pointIn(xp,yp,cnX,cnY,ctc);
		//cout<<"("<<xp<<","<<yp<<")";
		outf<<xp<<" "<<yp;
		if(isIn == true){
			outf<<" inside"<<endl;
		}
		else{
			outf<<" outside"<<endl;
		}
	}
	return 0;
}
