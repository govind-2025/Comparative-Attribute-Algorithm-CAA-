#include <bits/stdc++.h>
using namespace std;

// 1 graph printing
// 2 print Unsorted list into text file
// 3 print sorted list into text file
// 4 adding adges to graph
// 5 insert into vector of pair
// 6 mergefunction
// 7 meerge sort
/*********************    Graph printing     ***********************/
void printgraphVP(vector<pair<int, vector<int>>> vv)
{
    for (auto p : vv)
    {
        cout << "    " << p.first << " -> ";
        for (auto pp : p.second)
            cout << pp << " ";
        cout << endl;
    }
}

/*****************   Unsorted Task into txt file ******************/
void printBinG(vector<pair<int, vector<int>>> vv)
{
    ofstream obj("UT.txt");
    obj.close();
    fstream out;
    out.open("UT.txt", ios::out);
    out << "***************   Unsorted List  **********************\n";
    for (auto p : vv)
    {
        out << "    " << p.first << " -> ";
        for (auto pp : p.second)
            out << pp << " ";
        out << endl;
    }
    out.close();
}

/*****************   Unsorted Task into txt file ******************/
void printAinG(vector<pair<int, vector<int>>> vv)
{
    ofstream obj("ST.txt");
    obj.close();
    fstream out;
    out.open("ST.txt", ios::out);
    out << "***************   Sorted List  **********************\n";
    for (auto p : vv)
    {
        out << "    " << p.first << " -> ";
        for (auto pp : p.second)
            out << pp << " ";
        out << endl;
    }
    out.close();
}

/**************   Adding edges to graph    *****************/
void addadj(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
}

/*******************    Inserting into vector of pair for dependencies  *********************/
//
void insertintopairofvector(vector<int> adj[], int v, vector<pair<int, vector<int>>> &vv)
{
    for (int i = 0; i < v; i++)
        vv.push_back({i, adj[i]});
}

/************************  Merge Function according to Comparative Attribute Algorithm  ****************************/

void merge(vector<pair<int, vector<int>>> &UT, int l, int mid, int r, vector<int> noofrequests, vector<int> workload, int MNR, int WM, vector<int> &dependency)
{
    vector<pair<int, vector<int>>> UT1, UT2;
    for (int i = l; i <= mid; i++)
        UT1.push_back(UT[i]);

    for (int i = mid + 1; i <= r; i++)
        UT2.push_back(UT[i]);

    int i = l, l1 = 0, l2 = 0, r1 = UT1.size(), r2 = UT2.size();

    while (l1 < r1 && l2 < r2)
    {
        pair<int, vector<int>> Tu = UT1[l1], Tv = UT2[l2], P;

        if (find(Tu.second.begin(), Tu.second.end(), Tv.first) != Tu.second.end())
        {
            P = Tu;
            l1++;
        }
        else if (find(Tv.second.begin(), Tv.second.end(), Tu.first) != Tv.second.end())
        {
            P = Tv;
            l2++;
        }
        else
        {
            // int Du = accumulate(Tu.second.begin(), Tu.second.end(), 0);
            // int Dv = accumulate(Tv.second.begin(), Tv.second.end(), 0);
            int Du = dependency[Tu.first];
            int Dv = dependency[Tv.first];
            if (Du > Dv)
            {
                P = Tu;
                l1++;
            }
            else if (Du < Dv)
            {
                P = Tv;
                l2++;
            }
            else
            {
                float NRRu = noofrequests[Tu.first] / float(MNR);
                float NRRv = noofrequests[Tv.first] / float(MNR);
                if (NRRu > NRRv)
                {
                    P = Tu;
                    l1++;
                }
                else if (NRRu < NRRv)
                {
                    P = Tv;
                    l2++;
                }
                else
                {
                    float WLRu = workload[Tu.first] / float(WM);
                    float WLRv = workload[Tv.first] / float(WM);
                    if (WLRu > WLRv)
                    {
                        P = Tv;
                        l2++;
                    }
                    else
                    {
                        P = Tu;
                        l1++;
                    }
                }
            }
        }

        UT[i] = P;
        i++;
    }

    while (l1 < r1)
    {
        UT[i] = UT1[l1++];
        i++;
    }
    while (l2 < r2)
    {
        UT[i] = UT2[l2++];
        i++;
    }
}

/******************   Merge Sort  ******************/

void mergesort(vector<pair<int, vector<int>>> &UT, int l, int r, vector<int> noofrequests, vector<int> workload, int MNR, int WM, vector<int> &dependency)
{
    if (l >= r)
        return;

    int mid = l + (r - l) / 2;
    mergesort(UT, l, mid, noofrequests, workload, MNR, WM, dependency);
    mergesort(UT, mid + 1, r, noofrequests, workload, MNR, WM, dependency);

    merge(UT, l, mid, r, noofrequests, workload, MNR, WM, dependency);
}

int main()
{

    /*************************************************************/
    srand(time(0));
    // cout << "Jay Shree Ram\n";
    cout << "Enter the number of vertices(tasks)\n";
    int n;
    cin >> n;
    vector<int> adj[n];
    vector<int> dependency(n, 0);
    int no_ofedges = rand() % ((n * (n - 1)));
    // int no_ofedges = 3;
    // cout<<"Number of edges is "<<no_ofedges<<endl;
    int cnt = 0;
    for (int i = 0; i < no_ofedges; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        // int x, y;
        // cin >> x >> y;

        if (x != y)
        {
            if (find(adj[x].begin(), adj[x].end(), y) == adj[x].end())
            {
                dependency[y]++;
                adj[x].push_back(y);
                cnt++;
            }
        }
    }
    cout << "Number of edges is " << cnt << endl;
    cout << endl;
    /*********************************************/
    vector<pair<int, vector<int>>> UT;  // UT sorted List of Task
    insertintopairofvector(adj, n, UT); // pair of int and vector<int>

    vector<int> noofrequests(n);
    vector<int> workload(n);
    // vector<int> noofrequests{3, 5, 4, 3};        //   request
    // vector<int> workload{1000, 1700, 500, 1250}; // workload
    // vector<int> noofrequests(n), workload(n); // two vector's for number of workload and noofrequests  of task size;

    int no_of_r = 10; // no_of_r is range from 0 to no_of_r  requests
    // int no_of_r;
    cout << "Enter maximum number of request\n";
    cin >> no_of_r;
    for (int i = 0; i < n; i++)
    {
        noofrequests[i] = (rand() % no_of_r) + 1; // i added 1 because if we divide any number by 0 then it gives infinite value
                                                  // request is from 1 to 10
    }

    // int work_l = 10;                     // workload is from 1 to work_l
    int work_l;
    cout << "Enter workload from 4 to 1024   (it is in KB) \n";
    cin >> work_l;
    for (int i = 0; i < n; i++)
    {
        workload[i] = (rand() % work_l) + 1; // i added 1 because if we divide any number by 0 then it gives infinite value
    }

    int MNR = *min_element(noofrequests.begin(), noofrequests.end()); // minimum no. of request

    int WM = *min_element(workload.begin(), workload.end()); // minimum workload

    cout << "************************ Before Comparative Attribute Algorithm(CAA) ******************************\n";
    printgraphVP(UT);
    printBinG(UT); // for printing unsorted task into text file
    cout << endl;

    /*********************Camparative attribute Algorithm ****************************/

    int si = UT.size() - 1;
    mergesort(UT, 0, si, noofrequests, workload, MNR, WM, dependency); // here we get Sorted list of tasks

    /*****************************************************************************/
    cout << "************************ After Comparative Attribute Algorithm(CAA) ******************************\n";
    printgraphVP(UT);
    printAinG(UT); // for printing sorted task into text file
    cout << endl;  /*I use two diffrent function for printing into graph because i
                      take both task list sorted and unsorted into different file */
}