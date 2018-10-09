#include <DC3.hpp>
#include <gtest/gtest.h>
#include <fstream>

vector<string> get_all_sorted_rotate(string& str)
{
    vector<string> all_rotate;
    for(int i = 0; i< str.length(); ++i)
    {
        all_rotate.push_back(str);
        rotate(begin(str), begin(str)+1, end(str));
    }
    sort(begin(all_rotate), end(all_rotate));

    return all_rotate;
}

string get_L_via_all_rotate(string& str)
{
    auto all_rotate = get_all_sorted_rotate(str);
    string L;
    for(auto a: all_rotate)
    {
        if(*rbegin(a) == 0)
            L += '$';
        else
            L += *rbegin(a);
    }
    return L;
}

string get_L_via_SA(vector<int>& SA, string& str)
{
    string L;
    for(int& i: SA)
        if(i == 0)
            L += '$';
        else
            L += str[i-1];
    return L;
}

TEST(DC3, file)
{
    ifstream ifs("unit_test/test_data/strings.txt");
    string str;

    while(getline(ifs, str))
    {

        str.push_back(0);

        vector<int> v;
        for(auto c:str)
            v.push_back(c);
        
        
        auto SA = DC3(v);
        string L1 = get_L_via_SA(SA, str);
        string L2 = get_L_via_all_rotate(str);
        
        /*
        *rbegin(str) = '$';
        cout<<"L1******************************************"<<endl;
        for(auto i:SA)
        {
            cout<<str.substr(i, 150)<<endl;
        }

        cout<<"L2******************************************"<<endl;
        auto a = get_all_sorted_rotate(str);
        for(auto b:a)
        {
            cout<<b.substr(0, 150)<<endl;
        }
        */
        EXPECT_EQ(L1, L2);

        
    }
    
}