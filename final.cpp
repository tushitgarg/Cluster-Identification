#include <bits/stdc++.h>
using namespace std;

int rows,columns; // Declaring rows and columns variable

//*****************Vertex number calculating func***********
int vertex_number(int row, int column)
{
	return (row-1)*columns+column;
}
//***************End of Vertex number calculating func*******

//***************Printing Adjency List Function**************
void printAdjList(pair <int, vector<int>> adjList[])
{
	cout<<"\n\nOutput 1\nAdjency List\n";
	for (int i = 1; i <=rows*columns; i++) 
	{
		if(adjList[i].first==0)
		{
			continue;
		}
		cout<<"Vertex "<<i<<":";
        for (int j = 0; j <adjList[i].second.size(); j++)
        {
            cout <<"->"<<adjList[i].second[j];
        }
        cout << endl;
    }
}
//***************End of Printing Adjency List Func*************

//************************DFS func****************************
void DFS(int v, bool visited[],int *cluster_count,pair <int,vector<int>> adjList[]) 
{ 
    // Mark the current node as visited and 
    // print it 
    visited[v] = true; 
    //cout << v << " "; 
    *cluster_count = *cluster_count+1;

    // Recur for all the vertices adjacent 
    // to this vertex 

    vector<int>::iterator i; 
    for (i = adjList[v].second.begin(); i != adjList[v].second.end(); ++i)  
    {
        if (!visited[*i] && adjList[*i].first==1) 
        {
            DFS(*i,visited,cluster_count,adjList); 
        }
    }
} 
//************************End of DFS function******************

//************************Cluster Counting func****************
void identifyCluster(pair <int, vector<int>> adjList[])
{
	cout<<"\n\nIdentifying clusters\n";
	int V = rows*columns+1;
	// Declaring an array to store the visited vertices
	bool visited [V]; 

	//Marking all vertices as unvisited
    for (int i = 1; i<=V; i++) 
        visited[i] = false; 

    // Declaring variables to store the
    // cluster count and cluster number
    int cluster_number=0;
    int cluster_count=0;

    // Finding the clusters usign DFS
    for (int i = 1; i <=V; i++) 
    {
        if (visited[i] == false && adjList[i].first==1) 
        {
        	cluster_number++;
        	cluster_count=0;
            DFS(i, visited,&cluster_count,adjList); 
            cout<<"Cluster Number:"<<cluster_number<<" "<<"Number of sites="<<cluster_count<<endl;
        }
    }

}
//-----------------------------------------------------------------

//**********************Driver code*******************************
int main()
{
	cout<<"Enter the number of rows in 2d square lattice.\n";
	cin>>rows;
	// As the lattice is square
	// rows=columns
	columns = rows;

	// Declaring an array to store 
	// the lattice
	int Lattice[rows+1][columns+1];
	cout<<"Enter the lattice row wise.\n";
	for(int i = 1; i <=rows; i++)
	{
		for(int j = 1; j <=columns; j++)
		{
			cin>>Lattice[i][j];
		}
	}

	pair <int, vector<int>> adjList[rows*columns+1]; // Declaring Adjency List
	int vertex;

//-----------------------Making the Adjency List From Lattice-----------
	for(int i = 1; i <=rows; i++)
	{
		for(int j = 1; j <=columns; j++)
		{
			vertex = vertex_number(i,j);
			adjList[vertex].first = Lattice[i][j];
			if(Lattice[i][j]==1)
			{
				// Checking the nearest neighbours for current vertex.
				if(j-1>=0 && Lattice[i][j-1]==1)
					adjList[vertex].second.push_back(vertex_number(i,j-1));
				if(i+1<=rows && Lattice[i+1][j]==1)
					adjList[vertex].second.push_back(vertex_number(i+1,j));
				if(j+1>=0 && Lattice[i][j+1]==1)
					adjList[vertex].second.push_back(vertex_number(i,j+1));
				if(i-1>=0 && Lattice[i-1][j]==1)
					adjList[vertex].second.push_back(vertex_number(i-1,j));
			}
		}
	}
//----------------------------------------------------------------------

//---------------Calling the print Adjency List function----------------
    printAdjList(adjList);
//----------------------------------------------------------------------

//---------------Calling the Cluster identification function------------ 
    identifyCluster(adjList);
//----------------------------------------------------------------------
    return 0;
}
//***************End of Driver code************************************