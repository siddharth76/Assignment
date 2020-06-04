#include <bits/stdc++.h>
using namespace std;

int main() {

	int employees;
	cin>>employees;
	double distance[employees+1][employees+1];
	for(int i=0 ; i<=employees ; i++){
		for(int j=0 ; j<=employees ; j++){
			cin>>distance[i][j];
		}
	}
	
	vector< pair<double, vector<int>> > cost;
	// <cost of the path, path chosen>

	double costPerCab, costPerKm;
	cin>>costPerCab>>costPerKm;
	
	/*
		Lets say we have already dropped employee x,
		Also to reach y, the cost of source -> x -> y is lesser than source->x
		If we allow y to follow the path source -> x -> y because it is less costly, even though x has been dropped earlier
		Then we will perfrom Flowd Warshal First,
		
		If we cannot do this, then we wont apply Floyd Warshal Algorithm	 
	
	*/
	
	/*
	//	Floyd Warshall to find all pair shortest path
		for(int k=0 ; k<=employees ; k++){
			for(int i=0 ; i<=employees ; i++){
				for(int j=0 ; j<=employees ; j++){
					distance[i][j] = min(distance[i][j], distance[i][k]+distance[k][j]);
				}
			}
		}
	*/
	int office = 0;
	
	// Add single person in the cab
	for(int i=1 ; i<=employees ; i++){
		double distanceCovered = distance[office][i];
		double currentCost = costPerKm * distanceCovered;
		currentCost += costPerCab;
		double averageCost = currentCost/1.0;
		cost.push_back({averageCost, {i}});
	}
	
	// Add two person in the cab
	for(int i=1 ; i<=employees ; i++){
		for(int j=1 ; j<=employees ; j++){
			if(i==j)
				continue;
			double distanceCovered = distance[office][i]+distance[i][j];
			double currentCost =  costPerKm * distanceCovered;
			currentCost += costPerCab;
			double averageCost = currentCost/2.0;
			cost.push_back({averageCost, {i, j}});
		}
	}
	
	//Add three person in the cab
	for(int i=1 ; i<=employees ; i++){
		for(int j=1 ; j<=employees ; j++){
			if(i==j)
				continue;
			for(int k=1 ; k<=employees ; k++){
				if(k==j || k==i)
					continue;
				double distanceCovered = distance[office][i]+distance[i][j]+distance[j][k];
				double currentCost =  costPerKm * distanceCovered;
				currentCost += costPerCab;
				double averageCost = currentCost/3.0;
				cost.push_back({averageCost, {i, j, k}});	
			}
		}
	}
	sort(cost.begin(), cost.end());
	int visited[employees+1];
	memset(visited, 0, sizeof(visited));
	
	double totalCost = 0;
	
	vector<vector<int>> tracePath;
	for(auto optimalPath: cost){
		double curCost = optimalPath.first;
		vector<int> curPath = optimalPath.second;
	
//		cout<<curCost<<" ===> ";
//		for(auto x: curPath)
//			cout<<x<<" ";
//		cout<<endl;
		
		bool alreadyVisited = false;
		for(auto employee: curPath){
			if(visited[employee]){
				alreadyVisited = true;
				break;
			}
		}
		
		if(alreadyVisited)
			continue;
		
		totalCost += (curCost*curPath.size());
		
		vector<int> path;
		for(auto employee: curPath){
			visited[employee] = true;
			path.push_back(employee);
		}
		tracePath.push_back(path);
	}
	
	int cabRequired = tracePath.size();
	
	cout<<"Minimum cost : "<<totalCost<<"\n";
	cout<<"Total number of Cab required : "<<cabRequired<<"\n";
	cout<<"Information of Cab Path \n";
	
	for(int cab=0 ; cab<tracePath.size() ; cab++){
		cout<<"Details of Cab #"<<cab+1<<"\n";
		cout<<"Office -> ";
		for(int employee=0 ; employee<tracePath[cab].size() ; employee++){
			cout<<"Employee #"<<tracePath[cab][employee];
			if(employee+1 != tracePath[cab].size()){
				cout<<" -> ";
			}
		}
		cout<<"\n------------------------------------------\n";
	}
    return 0;
}


/*
3
0    1.5  2.0  1.8
1.8   0   1.7  2.1
2.1  1.6   0   2.2
1.7  2.2  2.1   0
300 50
*/
