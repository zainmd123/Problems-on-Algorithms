#include "header.h"
#include <limits.h>

// ANY STATIC FUNCTIONS ARE UP HERE


static void func1(int n, const connection_t connections[n][n],int selected[], int source)
{
    selected[source] = 1;
    for(int i = 0;i<n;i++)
    {
        if(connections[source][i].distance!=0 && connections[source][i].distance != INT_MAX && selected[i]==0)
        {
            func1(n,connections,selected,i);
        }
    }
}
static void func2(int selected[], int n, int source, int des, const connection_t connections[n][n], int *min, int *edges)
{
    int i;
    selected[source] = 1;
    if (source == des) {
        if (*min > *edges)
            *min = *edges;
    }
    else{
        for(i=0;i<n;i++)
        {
            if (connections[source][i].distance !=0 && connections[source][i].distance != INT_MAX && selected[i]==0) {
                (*edges)++;            
                func2(selected,n, i, des, connections, min, edges);
            }
        }
    }
    selected[source] = 0;
    (*edges)--;
 
}

static void func3(int n, const connection_t connections[n][n], int selected[], int src)
{
    int i;
    for(i=0;i<n;i++)
    {
        if (connections[src][i].distance !=0 && connections[src][i].distance != INT_MAX && selected[i]==0) {
                selected[i] = 1;           
                func3(n,connections,selected, i);
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

static int func4_a(int l, int h, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[h+1])
{
    airport_t pivot = airport_list[h]; 
    int i = (l - 1); 

    for (int j = l; j < h; j++)
    {
        if (predicate_func(&airport_list[j], &pivot))
        {
            i++; // increment index of smaller element
            swap(&airport_list[i], &airport_list[j]);
        }
    }
    swap(&airport_list[i + 1], &airport_list[h]);
    return i+1;
    
}

static void func4_b(int l, int h, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[h+1])
{
    if (l < h)
    {
        int pi = func4_a(l,h, predicate_func, airport_list);
        func4_b(l, pi-1,predicate_func, airport_list);
        func4_b(pi+1, h, predicate_func, airport_list);
    }
}
 
static int sort(const airport_t *x, const airport_t *y)
{
    int i=0;
    while((x->airport_name)[i] == (y->airport_name)[i])
        i++;

    return (x->airport_name)[i] < (y->airport_name)[i];
    
}

static int len_prefix(const char *s1, const char *s2)
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
static pair_t func5(int n, int (*sort)(const airport_t *, const airport_t *),airport_t airports[n])
{
    pair_t var = {-1,-1};
    int i,max=0;
        
    q4(n, sort, airports);
    for(i=0;i<n-1;i++)
    {
        if(len_prefix(airports[i].airport_name,airports[i+1].airport_name)>max)
        {
            max=len_prefix(airports[i].airport_name,airports[i+1].airport_name);
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

static void func7_a(const char *pat, int TABLE[256])
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

static int func7_b(const char *T,const char *pat)
{
    int TABLE[256];
    func7_a(pat,TABLE);

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

static int func8_a(int n,int selected[n])
{
    int i,count=0;
    for(i=0;i<n;i++)
    {
        if(selected[i]==1)
            count++;
    }
    return count;
}

static void func8_b(int n, int trip_order[n - 1], int temp[n-1],const connection_t connections[n][n], int selected[n],int *cost,int src, int src_temp, int index,int *min)
{
    int i;
    int value;
    selected[src] = 1;
    

    for(i=0;i<n;i++)
    {
        if(func8_a(n,selected) == n-1)
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

        else if(connections[src][i].distance !=0 && connections[src][i].distance != INT_MAX && selected[i]==0) 
        {
            value = connections[src][i].distance;
            temp[index++] = src;    
            *cost+=value;     
            func8_b(n,trip_order,temp,connections,selected, cost,i,src_temp, index, min);
            *cost -= value;
            index--;
        }
        
    }
      
    selected[src] = 0;
    
}

static int func9(int n, const connection_t connections[n][n], pair_t edges[n-1] )
{
    int i,j, u,v, min_time=0, min, selected[n], ne=0;

    for(i=0;i<n;i++)
        selected[i] = 0;

    selected[0] = 1;
    while(ne < n-1)
    {   
        
        min = INT_MAX;
        for (i=0;i<n;i++)
        {
            
            if(selected[i])
            {
                for (j=0;j<n;j++)
                {
                    if(!selected[j] && connections[i][j].time != 0 && connections[i][j].time != INT_MAX)
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

        edges[ne].first = u;
        edges[ne].second = v;
		selected[v] = 1;
        min_time+=min;
        ne++;
		
    }
    return min_time;
}

static int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}

static int func10(int n, const connection_t connections[n][n], int src, int dest, int selected[n]) 
{
    if (src == dest)
        return 0;
 
    selected[src] = 1;
 
    int ans = INT_MAX;

    for (int i = 0; i < n; i++) 
    {
        if (connections[src][i].time != INT_MAX && connections[src][i].time != 0 && !selected[i]) {

            int curr = func10(n,connections,i, dest,selected);
 
            if (curr < INT_MAX) {
 
                ans = min(ans, connections[src][i].time + curr);
            }
        }
    }

    selected[src] = 0;
 
    return ans;
}
// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n])
{
    int v,i;
    int selected[n];

    for(v=0;v<n;v++)
    {

        for(i=0;i<n;i++)
            selected[i] = 0;

        func1(n,connections,selected,v);
        for(i=0;i<n;i++)
        {
            if(!selected[i])
                return 0;
        }
    }
    return 1;
}


int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])      
{
    int i, min = INT_MAX, edges = 0;
    int selected[n];

    for(i=0;i<n;i++)
        selected[i] = 0;

    func2(selected,n, src->num_id, dest->num_id, connections, &min, &edges);

    return min<=k;
}


int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    int selected[n];
    int i;
    for(i=0;i<n;i++)
        selected[i] = 0;

    func3(n,connections,selected, src->num_id);
    
    return selected[src->num_id];
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
    func4_b(0,n-1,predicate_func,airport_list);

}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = func5(n,sort,airports);
    return ans;
}


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


void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{
    int i;
    for(i=0;i<n;i++)
    {
        if(func7_b((airports[i].airport_name), pat) == 1)
            contains[i] = 1;
    }
}


int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    int selected[n];
    int lowest = INT_MAX, min = INT_MAX,i,j,index=0,cost=0;
    int temp[n-1];

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            selected[j] = 0;

        func8_b(n,trip_order,temp,connections,selected,&cost,i,i,index,&min);

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

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    int min_time = func9(n,connections, edges);
    return min_time;
}


void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
    int i;
    int selected[n];

    for(i=0;i<n;i++)
        selected[i] = 0;

    for(i=0;i<k;i++)
    {
        costs[i] = func10(n,connections,src->num_id,destinations[i],selected);
    }
}

// END
