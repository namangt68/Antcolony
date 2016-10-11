/*
	created by
		->Naman Gupta
		->Nimit Kalal
	algo -> Ant Colony Optimization Algorithm
*/
#include<fstream>
#include<bits/stdc++.h>
using namespace std;
/*
	defining perameter of Ant Colony Optimization Algorithm
*/
#define alpha 4
#define beta 12
#define n_ant n_nodes
#define lemda 0.005
#define q 10
#define k 4

int main()
{
	ios::sync_with_stdio(false);
	string type;
	cin>>type;
	int n_nodes,i,j,i_ant,i_node;
	cin>>n_nodes;//taking no. of nodes
	float dmatrix[n_nodes][n_nodes];// distance matrix
	int closed[n_nodes];
	int path[n_ant][n_nodes+1];
	float cost[n_ant];
	int index_optimaltour=0;
	float lastoptimaltourcost=0; 
	float tao[n_nodes][n_nodes];
	float deltatao[n_nodes][n_nodes];
	float coordinates[n_nodes][2];
	//storing coordinates of data poin	
	for(i=0;i<n_nodes;i++){
		closed[i]=0;
		cin>>coordinates[i][0];
		cin>>coordinates[i][1];
	}
	//storing distance of differnt cities from each other
	for(i=0;i<n_nodes;i++){
		for(j=0;j<n_nodes;j++){
			cin>>dmatrix[i][j];
			tao[i][j]=1;
			if(i==j)
				tao[i][j]=INT_MAX;
		}
	}

	while(1){
		srand(time(NULL));
		int dtaomatrix[n_nodes][n_nodes];
		for(i=0;i<n_nodes;i++){
			for(j=0;j<n_nodes;j++)
				dtaomatrix[i][j]=0;
		}
	// moving n_nodes no. of ant in all the cities
		for(i_ant=0;i_ant<n_ant;i_ant++){
			cost[i_ant]=0;
			int currnode=i_ant;
			int nextnode;
			srand(time(NULL));
			//finding path for each ant 
			for(i_node=0;i_node<n_nodes;i_node++){
				path[i_ant][i_node]=currnode;					
				closed[currnode]=1;
				float p_list[n_nodes];
				float p_total =0;
				//equation for  probabilistic transition rule for every point				
				for(j=0;j<n_nodes;j++){
					
					if(closed[j]==0){
						p_list[j]=pow(tao[currnode][j],alpha)*pow((k/dmatrix[currnode][j]),beta);//eta
						p_total+=p_list[j];
					}
					else{
						p_list[j]=0;	
					}
					
				}
				for(i=0;i<n_nodes;i++){
					p_list[i]/=p_total;
					if(i!=0){
						p_list[i]+=p_list[i-1];
					}
				}
				//finding next node for ant
				float p_rand=p_list[n_nodes-1]*((float)rand()/((float)RAND_MAX));//rand
				for(j=0;j<n_nodes;j++){
					if(p_list[j]>p_rand){
						nextnode=j;
						break;					
					}		
				}
				
				if(i_node==(n_nodes-1)){
					path[i_ant][i_node+1]=path[i_ant][0];
									
				}
				dtaomatrix[currnode][nextnode]++;
				currnode=nextnode;
			}
			//finding tour cost for every ant
			for(i=1;i<(n_nodes+1);i++){
				cost[i_ant]+=dmatrix[path[i_ant][i-1]][path[i_ant][i]];
			}
			//calculating pheromone amount for every node in cities
			if(i_ant!=0||lastoptimaltourcost==0){
			for(j=1;j<(n_nodes+1);j++){
				int n_tao=dtaomatrix[path[i_ant][j-1]][path[i_ant][j]] + dtaomatrix[path[i_ant][j]][path[i_ant][j-1]];
				tao[path[i_ant][j-1]][path[i_ant][j]]=(1-lemda)*tao[path[i_ant][j-1]][path[i_ant][j]]+n_tao*q/cost[index_optimaltour];
			}}
			if(i_ant!=0){
				if(cost[index_optimaltour]>cost[i_ant]){
					index_optimaltour=i_ant;				
				}		
			}
			for(i=0;i<n_nodes;i++){
				closed[i]=0;
			}
		}
		// printing path optimal path in current generation
		if(lastoptimaltourcost==0){
			lastoptimaltourcost=cost[index_optimaltour];
			
			for(i=0;i<(n_nodes);i++){
				cout<<path[index_optimaltour][i]+1<<" ";			
			}
			cout<<"\n";
			cout<<std::flush;
			
		}
		else{
			if(lastoptimaltourcost>cost[index_optimaltour]){
				lastoptimaltourcost=cost[index_optimaltour];
			
				for(i=0;i<(n_nodes);i++){
					cout<<path[index_optimaltour][i]+1<<" ";			
				}
				cout<<"\n";	
				cout<<std::flush;			
			}

		
		}		
		memset(path,0,n_ant*n_nodes*sizeof(int));
		memset(cost,0,n_ant*sizeof(float));
		index_optimaltour=0;
	}		
			
		
}











































