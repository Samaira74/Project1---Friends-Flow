#include <bits/stdc++.h>
#include <chrono>
#include <thread>

#define inf 99999
#define V 5
using namespace std;

int unique_id = 0;



// Function to find the mutual followers between two users
void mutual_followers(string user_1, string user_2, map<string, int> &db, map<int, string> &temp_db, vector<int> adj[])
{
    if (db.find(user_1) != db.end() && db.find(user_2) != db.end())
    {
        cout << "Mutual Followers of " << user_1 << " with respect to " << user_2 << " : \n";
        for (auto i : adj[db[user_1]])
        {
            for (auto j : adj[db[user_2]])
            {
                if (i == j)
                {
                    cout << temp_db[i] << endl;
                }
            }
        }
    }
    else
    {
        cout << "The user name doesn't exist\n";
    }
}



// Function to find the number of mutual followers between two users
void no_of_mutual_followers(string user_1, string user_2, map<string, int> &db, map<int, string> &temp_db, vector<int> adj[])
{
    if (db.find(user_1) != db.end() && db.find(user_2) != db.end())
    {
        int cnt = 0;
        cout << "Number of Mutual Followers of " << user_1 << " with respect to " << user_2 << " : \n";
        for (auto i : adj[db[user_1]])
        {
            for (auto j : adj[db[user_2]])
            {
                if (i == j)
                {
                    cnt++;
                }
            }
        }
        cout << cnt << endl;
    }
    else
    {
        cout << "\nThe user name doesn't exist";
    }
}



// Function to find the number of friends of an user
void no_of_friends(string user_1, map<string, int> &db, vector<int> adj[])
{
    if (db.find(user_1) != db.end())
    {
        cout << "The number of friends " << user_1 << " got is " << adj[db[user_1]].size() << endl;
    }
    else
    {
        cout << "\nThe user name doesn't exists";
    }
}



// Function to display the friends list of an user
void display_friends_list(string user_1, map<string, int> &db, map<int, string> &temp_db, vector<int> adj[],map<string,vector<string>> list)
{
    if (db.find(user_1) != db.end())
    {
        cout << "\n Friends List of " << user_1 << " : ";    
        // both sided friendship    
        vector<string> v = list[user_1];
        for(int i=0; i<v.size(); i++) {
            vector<string> aa = list[v[i]];
            for(int j=0; j<aa.size(); j++) {
                if(aa[j] == user_1) {
                    cout<< v[i] << " ";
                }
            }
        }
        cout<<endl;
    }
    else
    {
        cout << "\nThe user name doesn't exists";
    }
    
}



// Function to recommend friends from the graph
void recommend(string user_1, map<string, int> &db, map<int, string> &temp_db, vector<int> adj[])
{

    if (db.find(user_1) != db.end())
    {
        cout << "\nRecommended Friends : \n"
             << endl;
        unordered_set<int> check_set;
        for (auto i : adj[db[user_1]])
        {
            check_set.insert(i);
        }
        for (auto i : adj[db[user_1]])
        {
            for (auto j : adj[i])
            {
                if (j != db[user_1] && check_set.find(j) == check_set.end())
                {
                    cout << temp_db[j] << endl;
                    check_set.insert(j);
                }
            }
        }
    }
    else
    {
        cout << "\nThe user name doesn't exists";
    }

}



// Function to open the file and check whether it has opened correctly or not
void openFile(ifstream &inFile, string fname)
{
    inFile.open(fname);
    if (inFile.is_open())
    {
        cout << "\nSuccessfully opened the file" << endl;
    }
    else
    {
        cout << "\nFailed to open file" << endl;
        exit(-1);
    }

}



// Fumction implementing dijksta's algorithm to check connection strength between all the users


// ERROR 
void dijkstra(string u, int n, map<string, int> &db, vector<pair<int, int>> g[], map<int, string> &temp_db)
{

    // n denotes the no of users
    // map<string,int> & db denotes the map which holds the name:ID values


    if (db.find(u) != db.end())
    {

        int source = db[u];
        // cout<<"Source is   "<<source<<endl;
        //  cin >> source;

        // Dijkstra's algorithm begins from here
        priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
        // min-heap ; In pair => (dist,from)

        // 1-indexed array for calculating shortest paths;
        vector<int> distTo(n, 99999991);
        distTo[source] = 0;
        pq.push(make_pair(0, source)); // (dist,from)

        while (!pq.empty())
        {
            int dist = pq.top().first;
            int prev = pq.top().second;
            pq.pop();

            vector<pair<int, int>>::iterator it;
            for (it = g[prev].begin(); it != g[prev].end(); it++)
            {
                int next = it->first;
                int nextDist = it->second;
                if (distTo[next] > distTo[prev] + nextDist)
                {
                    distTo[next] = distTo[prev] + nextDist;
                    pq.push(make_pair(distTo[next], next));
                }
            }
        }

        cout << "The Connection Strength of user, " << u << " are : \n";
        for (int i = 0; i < n; i++)
        {
            if (i != source)
            {
                cout << temp_db[i] << " => " << 100/(distTo[i]) << " %" << endl;
            }
        }

    }
    else
    {
        cout << "\nThe user name doesn't exists";
    }

}


// Function to find an user with maximum number of friends
void max_friends(vector<int> adj[], map<int, string> &temp_db)
{

    int maxi = 0;
    int ans;
    for (auto it = temp_db.begin(); it != temp_db.end(); it++)
    {
        // cout<<adj[it->first].size()<<endl;
        if ((adj[it->first].size()) > maxi)
        {
            maxi = adj[it->first].size();
            // cout<<maxi<<endl;
            ans = it->first;
            // cout<<ans<<endl;
        }
    }

    // Output the name of one user with maximum number of friends
    cout << "User with maximum number of friends : " << temp_db[ans] << endl;

}


// Function to find an user with minimum number of friends
void min_friends(vector<int> adj[], map<int, string> &temp_db)
{

    int mini = INT_MAX;
    int ans;
    for (auto it = temp_db.begin(); it != temp_db.end(); it++)
    {
        // cout<<adj[it->first].size()<<endl;;
        if ((adj[it->first].size()) < mini)
        {
            mini = adj[it->first].size();
            // cout<<maxi<<endl;
            ans = it->first;
            // cout<<ans<<endl;
        }
    }

    // Output the name of one user with minimum number of friends
    cout << "User with minimum number of friends : " << temp_db[ans] << endl;

}



// ERROR IN THIS 
void spreadtime(map<string,vector<string>> list, map<string,int> db, map<int,string> temp_db) {
    
    // greedy approach 
    // find the user with maximum connections

    int time = 0;
    vector<bool> vis(db.size(),false);
    vector<string> ans;

    
    int max_val=0;
    string max_user;
    for(auto i: list){
        vector<string> v = i.second;
        if(v.size() > max_val){ 
            max_val = v.size();
            max_user = i.first;   
        }
    }

    // cout<< max_user << " -- "<<endl;
    // cout<< max_val << " -- "<<endl;

    // clear -- sahi hai yaha tak 
    
    vis[db[max_user]] = true;
    ans.push_back(max_user);
    string max_user1 = max_user;
    cout<<endl;

    // cout << ans.size() << "----" <<endl;
    // cout<< db.size() << endl;

    while(ans.size() < db.size()){ 

        vector<string> adj = list[max_user1];
        int max_val1=0;
    
        for(int i=0; i<adj.size(); i++) {
            string user = adj[i];
            if(max_val1 < list[user].size()){ 
                max_val1 = list[user].size();
                max_user1 = user;
            }
        }

        // ans.push_back(max_user1);

        for(int i=0; i<adj.size(); i++) {
            if(vis[db[adj[i]]] == false) {
                vis[db[adj[i]]] = true;
                ans.push_back(adj[i]);
            }
        }

        time++;
        
    }

    cout<< "Minimum Spread Time is: " << time << " sec !" <<endl;
    cout<< "Sequence of virality is: "<<endl;
    for(int i=0; i<db.size(); i++) {
        if(i == db.size()-1) {
            cout<< ans[i];
        }
        else{
            cout<< ans[i] << " -- ";
        }
        
    }cout<<endl;
}


void details(string user, map<string,vector<string>> list, map<string,int> db, map<int,string> temp_db
,vector<pair<int, int>> g[21]) {

    // number of following, number of followers

    // following 
    vector<string> v = list[user];
    cout<< "Following: " << v.size() <<endl;    

    int flwr=0;
    vector<string> flwrlist;
    for(auto i: list) {
        vector<string> v = i.second;
        for(int j=0; j<v.size(); j++) {
            if(v[j] == user) {
                flwr++;
                flwrlist.push_back(i.first);
            }
        }
    }

    cout<< "Followers: "<< flwr << endl;

    dijkstra(user,db.size(), db, g, temp_db);



    int op;
    cout<< "Press 1 if you want to see follower list: ";
    cin >> op;

    if(op == 1) {
        for(auto i: flwrlist) {
            cout<< i << " ";
        }cout<<endl;
    }

}

void printSolution(int dist[][V])
{
    cout << "The following matrix shows the shortest "
    "distances between every pair of friends \n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == inf)
                cout << "INF"
                     << " ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
}


// floyd warshall
void allPairShortestPath(int dist[][V]) {

    int i, j, k;

    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < V; j++) {
                // If vertex k is on the shortest path from
                // i to j, then update the value of
                // dist[i][j]
                if ( dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != inf && dist[i][k] != inf)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
                    
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
    

}




int main()
{
    system("color 3B");

    cout << setw(50) << setfill('=') << "" << endl;
    cout << "\t\tFRIENDS FLOW " << endl;
    cout << setw(50) << setfill('=') << "" << endl << endl;

    map<string,vector<string>> list;

    // map to store the user's name
    map<string, int> db;

    // map to store the user's name and for accessing
    map<int, string> temp_db;

    // Adjacency list to represent the graph
    vector<int> adj[1000];

    vector<pair<int, int>> g[1000];
    // for dijkstra

    int dist[5][5] = {

        {0, 1, inf, inf, inf},
        {1, 0, 1, 1, inf},
        {inf, inf, 0, 1, inf},
        {inf, inf, 1, 0, 1},
        {1, inf, inf, inf, 0}

    };


    
    cout << "\n1 . User Input";
    cout << "\n2 . Input from File\n";
    cout << "\nEnter your choice : ";
    int start_choice;

    cin >> start_choice;

    // Get Graph Input from File(network.txt,friends.txt)
    if (start_choice == 2)
    {

        // network.txt => contains all the names of the users

        ifstream inFile;
        openFile(inFile, "network.txt");

        string user_name;
        while (!inFile.eof())
        {
            getline(inFile, user_name);

            // adding the user names in the map
            if (db.find(user_name) == db.end())
            {
                // cout<< "username: "<< user_name << " added to db" <<endl;
                vector<string> v;
                list[user_name] = v;
                db[user_name] = unique_id;
                temp_db[unique_id] = user_name;
                unique_id++;
            }
            else
            {
                cout << "\nThe user name already exists";
            }
        }

        inFile.close();

        cout << "network.txt closed" << endl;

        // friends.txt => contains the friends name of the users in network.txt

        inFile;
        openFile(inFile, "friends.txt");

        // 2.process the file
        // read line by line from the file
        string temp_user_name;
        string following_name;
        istringstream iss;
        for (auto it = db.begin(); it != db.end(); it++)
        {
            while (!inFile.eof())
            {

                // read word by word from each line

                getline(inFile, temp_user_name);
                // cout<< "temp_user_name: " << temp_user_name <<endl;

                if (inFile.good())
                {
                    iss.clear();
                    iss.str(temp_user_name);
                    while (iss.good())
                    {
                        iss >> following_name;
                        // cout<< "following name: " <<following_name <<endl;
                        // cout<< "it->first: " <<it -> first <<endl;

                        // adding in the adjacency list to create a graph

                        if (following_name != it->first && db.find(following_name) != db.end())
                        {
                            adj[db[it->first]].push_back(db[following_name]);
                            // adj[db[following_name]].push_back(db[it->first]); // if the graph is undirected
                            list[it->first].push_back(following_name);
                            list[it->first].shrink_to_fit();
                            // for dijkstra
                            g[db[it->first]].push_back(make_pair(db[following_name], 1));
                        }
                        // else
                        // {
                        //     cout << "The name doesn't exist"<<endl;
                        // }
                    }
                    break;
                }
            }
        }

        // 3.close the file friends.txt
        inFile.close();
        cout << "friends.txt file closed" << endl;
    }

    // Menu driven to get user details from output terminal
    else if (start_choice == 1)
    {

        // Input to get number of users
        int no_of_users;

        // Input to get user names
        string user_name;

        cout << "Enter the number of users : ";
        cin >> no_of_users;

        // Input user names
        for (int i = 0; i < no_of_users;)
        {
            cout << "\nEnter User " << i + 1 << " name : ";
            cin >> user_name;

            // adding in the map

            if (db.find(user_name) == db.end())
            {   
                vector<string> v;
                list[user_name] = v;
                db[user_name] = i;
                temp_db[i] = user_name;
                i++;
            }
            else
            {
                cout << "\nThe user name already exists";
            }
        }


        // Input friends name from the user
        cout << "\n Enter Following List ( -1 to complete ) : ";
        for (auto it = db.begin(); it != db.end(); it++)
        {
            cout << "\n"
                 << it->first << " : \n";

            // Input friends name for each user
            string following_name;

            while (1)
            {
                cin >> following_name;

                if (following_name == "-1")
                    break;

                // adding in the adjacency list to create the graph

                else if (following_name != it->first && db.find(following_name) != db.end())
                {
                    adj[db[it->first]].push_back(db[following_name]);
                    // adj[db[following_name]].push_back(db[it->first]);

                    list[it->first].push_back(following_name);
                    list[it->first].shrink_to_fit();

                    // for dijkstra
                    g[db[it->first]].push_back(make_pair(db[following_name], 1));
                }
                else
                {
                    cout << "\nThe name doesn't exist";
                }
            }
        }
    }
    else
    {
        cout << "\n Invalid Input";
        exit(-1);
    }


    cout<< "printing list" <<endl;
    for(auto i: list) {
        cout<< i.first << " : ";
        vector<string> v = i.second;
        for(auto j: v) {
            cout<< j << " ";
        }cout<<endl;
    }

    cout<< "printing db " <<endl;
    for(auto i: db){ 
        cout<< i.first << i.second << endl;
    }

    cout<< "printing tem_db" <<endl;
    for(auto i: temp_db) {
        cout<< i.first << i.second << endl;
    }


    while (1)
    {   

        // To get option number from the user
        int option;

        // Menu driven options
        cout << "\n1 . Check Mutual Followers";
        cout << "\n2 . Number of Mutual Followers";
        cout << "\n3 . Number of Friends List";
        cout << "\n4 . Display Friends List";
        cout << "\n5 . Recommend new Friends";
        cout << "\n6 . Check Connections Strength";
        cout << "\n7 . Users with maximum number of Friends";
        cout << "\n8 . Users with minimum number of Friends";
        cout << "\n9 . Spread Time";
        cout << "\n10. Details of User";
        cout << "\n11. How Far The Friends are ?";


        cout << "\nEnter your choice : ";
        cin >> option;

        // sample variables to get user names
        string user_1, user_2;
        string det_user;
        string u;

        switch (option)
        {

        // Check Mutual Followers
        case 1:
            cout << "\nEnter the user name : ";
            cin >> user_1;
            cout << "\nEnter the name of the user to check mutual Followers : ";
            cin >> user_2;
            mutual_followers(user_1, user_2, db, temp_db, adj);
            break;

        // Number of Mutual Followers
        case 2:
            cout << "\nEnter the user name : ";
            cin >> user_1;
            cout << "\nEnter the name of the user to check mutual Followers : ";
            cin >> user_2;
            no_of_mutual_followers(user_1, user_2, db, temp_db, adj);
            break;

        // Number of Friends List
        case 3:
            cout << "\nEnter the user name : ";
            cin >> user_1;
            no_of_friends(user_1, db, adj);
            break;

        // Display Friends List
        case 4:
            cout << "\nEnter the user name : ";
            cin >> user_1;
            display_friends_list(user_1, db, temp_db, adj,list);
            break;

        // Recommend new Friends
        case 5:
            cout << "\nEnter the user name : ";
            cin >> user_1;
            recommend(user_1, db, temp_db, adj);
            break;

        // Check Connections Strength (Dijkstra's algorithm)
        case 6:
            cout << "\nEnter user name to find its connection strength : ";
            cin >> u;
            dijkstra(u,db.size(), db, g, temp_db);
            break;

        // Users with maximum number of Friends
        case 7:
            max_friends(adj, temp_db);
            break;

        // Users with minimum number of Friends
        case 8:
            min_friends(adj, temp_db);
            break;

            case 9:
            spreadtime(list,db,temp_db);
            break; 

        case 10:
            cout<< "Enter User: ";
            cin >> det_user;
            details(det_user, list,db,temp_db,g);
            break;
            
        case 11: 
            allPairShortestPath(dist);
            break;

        default:
            exit(0);
        }

        int m;
            cout<< "enter 0 to clear screen: ";
            cin >> m;
            if(m==0) system("cls");

    }

    return 0;

}