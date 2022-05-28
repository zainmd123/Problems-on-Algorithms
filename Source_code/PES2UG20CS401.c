//Author: Zain Muhammed
//SRN: PES2UG20CS401
//DAA Assignment-2

#include "header.h"
#include <limits.h>

// ANY STATIC FUNCTIONS ARE UP HERE


static void q1_helper(int n, const connection_t connections[n][n],int visited[], int source)
{
    visited[source] = 1;
    for(int i = 0;i<n;i++)
    {
        if(connections[source][i].distance!=0 && connections[source][i].distance != INT_MAX && visited[i]==0)
        {
            q1_helper(n,connections,visited,i);
        }
    }
}
static void q2_helper(int visited[], int n, int source, int des, const connection_t connections[n][n], int *min, int *edges)
{
    int i;
    visited[source] = 1;
    if (source == des) {
        if (*min > *edges)
            *min = *edges;
    }
    else{
        for(i=0;i<n;i++)
        {
            if (connections[source][i].distance !=0 && connections[source][i].distance != INT_MAX && visited[i]==0) {
                (*edges)++;            
                q2_helper(visited,n, i, des, connections, min, edges);
            }
        }
    }
    visited[source] = 0;
    (*edges)--;
 
}

static void q3_helper(int n, const connection_t connections[n][n], int visited[], int src)
{
    int i;
    for(i=0;i<n;i++)
    {
        if (connections[src][i].distance !=0 && connections[src][i].distance != INT_MAX && visited[i]==0) {
                visited[i] = 1;           
                q3_helper(n,connections,visited, i);
        }
    }

}

static void swap(airport_t* a, airport_t* b)
{
    airport_t t;
    t = *a;
    *a = *b;
    *b = t;
}

static int q4_helper_1(int l, int h, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[h+1])
{
    airport_t pivot = airport_list[h]; 
    int i = (l - 1); 

    for (int j = l; j < h; j++)
    {
        // If current element is smaller than the pivot
        if (predicate_func(&airport_list[j], &pivot))
        {
            i++; // increment index of smaller element
            swap(&airport_list[i], &airport_list[j]);
        }
    }
    swap(&airport_list[i + 1], &airport_list[h]);
    return i+1;
    
}

static void q4_helper_2(int l, int h, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[h+1])
{
    if (l < h)
    {
        int pi = q4_helper_1(l,h, predicate_func, airport_list);
        q4_helper_2(l, pi-1,predicate_func, airport_list);
        q4_helper_2(pi+1, h, predicate_func, airport_list);
    }
}
 
static int ascending(const airport_t *x, const airport_t *y)
{
    int i=0;
    while((x->airport_name)[i] == (y->airport_name)[i])
        i++;

    return (x->airport_name)[i] < (y->airport_name)[i];
    
}

static int prefix(const char *s1, const char *s2)
{
    int i=0,count=0;
    while(1)
    {
        if(s1[i]!=s2[i])
        {
            return count;
        }
        count++;
        i++;
    }
    
    return count;
}
static pair_t q5_helper(int n, int (*ascending)(const airport_t *, const airport_t *),airport_t airports[n])
{
    pair_t var = {-1,-1};
    int i,max=0;
        
    q4(n, ascending, airports);
    for(i=0;i<n-1;i++)
    {
        if(prefix(airports[i].airport_name,airports[i+1].airport_name)>max)
        {
            max=prefix(airports[i].airport_name,airports[i+1].airport_name);
            var.first = airports[i].num_id;
            var.second = airports[i+1].num_id;
        }
    }
    return var;

}

static int length(const char *s)
{
    int i=0;
    while(s[i]!='\0'){
        i++;
    }
    return i;
}

static void shift_table(const char *pat, int TABLE[256])
{
    int i,m;
    m = length(pat);

    for(i=0;i<256;i++)
    {
        TABLE[i] = m;
    }
    for(i=0;i<m-1;i++)
    {
        TABLE[(int)(pat[i])] = m-i-1;
    }
}

static int q7_helper(const char *T,const char *pat)
{
    int TABLE[256];
    shift_table(pat,TABLE);

    int m,n,k,i;
    m = length(pat);
    n = length(T);
    i = m-1;
    
    while(i<n)
    {
        k=0;
        while( (k<m) && (pat[m-1-k] == T[i-k]))
            k++;
        if(k==m)
            return 1;
        else
            i = i+ TABLE[(int)(T[i])];

    }
    return 0;
}

static int check_visited(int n,int visited[n])
{
    int i,count=0;
    for(i=0;i<n;i++)
    {
        if(visited[i]==1)
            count++;
    }
    return count;
}

static void q8_helper(int n, int trip_order[n - 1], int temp[n-1],const connection_t connections[n][n], int visited[n],int *cost,int src, int src_temp, int index,int *min)
{
    int i;
    int value;
    visited[src] = 1;
    

    for(i=0;i<n;i++)
    {
        if(check_visited(n,visited) == n-1)
        {
            int temp_value = connections[src][src_temp].distance;
            if(temp_value != INT_MAX)
            {
                temp[index] = src;
                *cost += temp_value;
                
                if(*cost <= *min)
                {
                    *min = *cost;
                    for(int j=0;j<n-1;j++){
                            trip_order[j] = temp[j];
                    }
                    
                        
                }                
            }
            else
                temp_value = 0;

            *cost-= temp_value;
            i = n;

        }

        else if(connections[src][i].distance !=0 && connections[src][i].distance != INT_MAX && visited[i]==0) 
        {
            value = connections[src][i].distance;
            temp[index++] = src;    
            *cost+=value;     
            q8_helper(n,trip_order,temp,connections,visited, cost,i,src_temp, index, min);
            *cost -= value;
            index--;
        }
        
    }
      
    visited[src] = 0;
    
}

static int q9_helper(int n, const connection_t connections[n][n], pair_t edges[n-1] )
{
    int i,j, u,v, min_time=0, min, visited[n], num_edges=0;

    for(i=0;i<n;i++)
        visited[i] = 0;

    visited[0] = 1;
    while(num_edges < n-1)
    {   
        
        min = INT_MAX;
        for (i=0;i<n;i++)
        {
            
            if(visited[i])
            {
                for (j=0;j<n;j++)
                {
                    if(!visited[j] && connections[i][j].time != 0 && connections[i][j].time != INT_MAX)
                    {
                        if (min > connections[i][j].time) 
                        {
                            min = connections[i][j].time;
                            u =  i;
                            v = j;
                        }
                    }
                }
            }
        }

        edges[num_edges].first = u;
        edges[num_edges].second = v;
		visited[v] = 1;
        min_time+=min;
        num_edges++;
		
    }
    return min_time;
}

static int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}

static int q10_helper(int n, const connection_t connections[n][n], int src, int dest, int visited[n]) 
{
    if (src == dest)
        return 0;
 
    visited[src] = 1;
 
    int ans = INT_MAX;

    for (int i = 0; i < n; i++) 
    {
        if (connections[src][i].time != INT_MAX && connections[src][i].time != 0 && !visited[i]) {

            int curr = q10_helper(n,connections,i, dest,visited);
 
            if (curr < INT_MAX) {
 
                ans = min(ans, connections[src][i].time + curr);
            }
        }
    }

    visited[src] = 0;
 
    return ans;
}
// YOUR SOLUTIONS BELOW


//Using dfs I traversed all the node and after every traversal I checked if there was an unvisited node.
int q1(int n, const connection_t connections[n][n])
{
    int v,i;
    int visited[n];

    for(v=0;v<n;v++)
    {

        for(i=0;i<n;i++)
            visited[i] = 0;

        q1_helper(n,connections,visited,v);
        for(i=0;i<n;i++)
        {
            if(!visited[i])
                return 0;
        }
    }
    return 1;
}

//Using dfs I counted the edges for each possible path between source and destination. I found the minimum number of edges and compared this to k.
int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])      
{
    int i, min = INT_MAX, edges = 0;
    int visited[n];

    for(i=0;i<n;i++)
        visited[i] = 0;

    q2_helper(visited,n, src->num_id, dest->num_id, connections, &min, &edges);

    return min<=k;
}

//Using dfs I marked the initial source node as unvisited and after the traversal I checked if it was still unvisited to see if there was a path back to the source.
int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int visited[n];
    int i;
    for(i=0;i<n;i++)
        visited[i] = 0;

    q3_helper(n,connections,visited, src->num_id);
    
    return visited[src->num_id];
}

//Using quick sort algorithm I sorted the list.
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    q4_helper_2(0,n-1,predicate_func,airport_list);

}

//I sorted the list in alphabetical order and found the common prefix between 2 adjacent airports.
//Then I found the length for each prefix and stored the length of the maximum prefix along with the 2 airports sharing it.
pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = q5_helper(n,ascending,airports);
    return ans;
}

//Using binary search I found the number of elements before the given key value.
int q6(int n, int amount, const int entry_fee[n])
{
    int l=0;
    int r = n-1;
    int mid, count;

    while(l<=r)
    {
        mid = (l+r)/2;
        if(entry_fee[mid] <= amount)
        {
            l = mid+1;
            count = mid+1;
        }
        else
        {
            r = mid-1;
        }                       
    }
    return count;
}

//Using horspool algorithm I created a shift table and then checked if the pattern was present in the text.
void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(q7_helper((airports[i].airport_name), pat) == 1)
            contains[i] = 1;
    }
}

//If only one node is unvisited return back to the source node and store the length of the path. 
//Find the minimum path distance and store the nodes that contain this path.
int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int visited[n];
    int lowest = INT_MAX, min = INT_MAX,i,j,index=0,cost=0;
    int temp[n-1];

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            visited[j] = 0;

        q8_helper(n,trip_order,temp,connections,visited,&cost,i,i,index,&min);

        if(min < lowest)
            lowest = min;
    
        cost = 0;
    }  
    if(min == INT_MAX)
    {
        lowest = -1;
        for(i=0;i<n-1;i++)
            trip_order[i] = -1;
    }


    return lowest;
}
//Using prims algorithm I found minimum spanning tree for the graph
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int min_time = q9_helper(n,connections, edges);
    return min_time;
}

//Using dfs I stored minimum time for each of the given destinations.
void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    int i;
    int visited[n];

    for(i=0;i<n;i++)
        visited[i] = 0;

    for(i=0;i<k;i++)
    {
        costs[i] = q10_helper(n,connections,src->num_id,destinations[i],visited);
    }
}

// END
