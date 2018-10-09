#include <iostream>
#include <vector>
#include <string>
#include <map>

#define L_TYPE 0
#define S_TYPE 1

using namespace std;

struct BucketIdx{
    int L_head, S_tail;

};


inline bool isLMS(int i, vector<bool> type)
{
    if(type[i] == S_TYPE && i-1 >= 0 && type[i-1] == L_TYPE)
        return true;
    return false;
}

vector<int> sais(vector<int> , int);

vector<int> sais_driver(string& str)
{
    /* map string to value */
    map<char, int> char_rank;

    for(auto& ch: str)
    {
        char_rank[ch];
    }
    int i = 0;
    for(auto& [ch, idx]: char_rank)
    {
        idx = i++;
        
    }
    
    vector<int> new_str(str.length());

    for(int i = 0; i<str.length(); i++)
    {
        new_str[i] = char_rank[ str[i] ];
        
    }

    return sais(new_str, char_rank.size());
}

void induceSAl(vector<int>& SA, vector<BucketIdx> bkt, vector<bool>& t, vector<int>& str, int& n)
{
    for(int i = 0, j; i < n; i++)
    {
        j = SA[i]-1;
        if(j>=0 && t[j] == L_TYPE)
        {
            SA[ bkt[ str[j] ].L_head++ ] = j;
        }
    }
}

void induceSAs(vector<int>& SA, vector<BucketIdx> bkt, vector<bool>& t, vector<int>& str, int& n)
{
    for(int i = n-1, j; i >= 0; i--)
    {
        j = SA[i]-1;
        if(j>=0 && t[j] == S_TYPE)
        {
            SA[ bkt[ str[j] ].S_tail-- ] = j;
        }
    }
}

vector<int> sais(vector<int> str, int K)   // K means num_of_char
{

    
    int n = str.size();

    
    /* type mapping */
    vector<bool> t(n);  
    /* type cnt */
    vector<int> char_type_cnt(K);

    t[n-1] = S_TYPE;
    char_type_cnt[ str[n-1] ]++;

    for(int i = n-2; i >= 0; --i)
    {
        if(str[i] < str[i+1])
        {
            t[i] = S_TYPE;
        }
        else if(str[i] > str[i+1])
        {
            t[i] = L_TYPE;
        }
        else
        {
            t[i] = t[i+1];
        }
        char_type_cnt[ str[i] ]++;
    }

    /* build bucket idx */
    vector<BucketIdx> bkt(K);

    for(int i = 0, cnt = 0; i < K; ++i)
    {
        /* [head, tail] */
        bkt[i].L_head = cnt;
        cnt += char_type_cnt[i];
        bkt[i].S_tail = cnt - 1;
    }

    vector<BucketIdx> cpy_bkt(bkt);
    vector<int> SA(n);

    /* sort LMS strings */
    for(int i = n-1; i>=0; --i)
    {
        if(isLMS(i, t))
            SA[ bkt[ str[i] ].S_tail-- ] = i;
    }
    bkt = cpy_bkt;
    induceSAl(SA, bkt, t, str, n);
    induceSAs(SA, bkt, t, str, n);

    int i, j;

    // compact all the sorted substrings into the first n1 items of s
    // 2*n1 must be not larger than n (proveable)
    int n1=0;
    for(i=0; i<n; i++)
      if(isLMS(SA[i], t))
        SA[n1++]=SA[i];
    
    
    // Init the name array buffer
    for(i=n1; i<n; i++) SA[i]=-1;
    
    
    // find the lexicographic names of all substrings
    int name=0, prev=-1;
    for(i=0; i<n1; i++) 
    {
        int pos=SA[i]; bool diff=false;
        for(int d=0; d<n; d++)
        {
            if(prev==-1 || pos+d==n-1 || prev+d==n-1 ||
                str[pos+d]!=str[prev+d] ||
                t[pos+d]!=t[prev+d] )
            { diff=true; break; }
            else if(d>0 && (isLMS(pos+d, t) || isLMS(prev+d, t)))
                break;
        }
        if(diff) 
            { name++; prev=pos; }
        pos=pos/2; //(pos%2==0)?pos/2:(pos-1)/2;
        SA[n1+pos]=name-1; 
    }

    vector<int> SA1(n1);
    vector<int> str1(n1);
    for(i=n-1, j=n1-1; i>=n1; i--)
	    if(SA[i]!=-1) str1[j--]=SA[i];

    // build SA1
    if(name<n1)
        SA1 = sais(str1, name);
    else
        for(i=0; i<n1; i++) SA1[str1[i]] = i;
    
    // get LMS's index of str
    for(i=1, j=0; i<n; i++)
        if(isLMS(i, t)) str1[j++] = i;
    // put origin index in SA1 (sorted by LMS substring)
    for(i=0; i<n1; i++) 
        SA1[i] = str1[SA1[i]];
    // init SA
    for(i=0; i<n; i++)
        SA[i] = -1;
    // put all S* into SA
    for(i=n1-1; i>=0; i--) {
	  j=SA1[i];
      SA[ bkt[ str[j] ].S_tail-- ]=j;
    }    

    bkt = cpy_bkt;

    induceSAl(SA, bkt, t, str, n);
    induceSAs(SA, bkt, t, str, n);
    
    return SA;
}
