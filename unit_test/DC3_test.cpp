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

TEST(radix_sort, each_worker)
{
    vector<int> array = {123, 321, 211, 321, 611};
    vector<int> ans = {0, 2, 1, 3, 4}; // ascending sort
    vector<Three_char_unit> tuple_array;
    
    for(int i = 0; i < array.size(); i++)
        tuple_array.emplace_back(
            array[i]/100
          , (array[i]%100)/10 
          , (array[i]%10)
          , i
        );


    int radix_pass_depth = 3;
    radix_sort(tuple_array.begin(), tuple_array.size(), radix_pass_depth);

    vector<int> result;
    for(auto i : tuple_array)
        result.emplace_back(i.idx);

    EXPECT_EQ(result, ans);
}

TEST(radix_sort, parallel)
{
    vector<int> array = {100, 300, 200, 300, 600};
    vector<int> ans = {0, 2, 1, 3, 4}; // ascending sort
    vector<Three_char_unit> tuple_array;
    constexpr unsigned int num_thread = 1;

    for(int i = 0; i < array.size(); i++)
        tuple_array.emplace_back(
            array[i]/100
          , (array[i]%100)/10 
          , (array[i]%10)
          , i
        );

    auto sorted = tuple_array;
    int radix_pass_depth = 3;
    parallel_radix_sort<num_thread>(sorted, radix_pass_depth);

    vector<int> result;
    for(auto i : sorted)
        result.emplace_back(i.idx);

    EXPECT_EQ(result, ans);
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
        
        
        auto SA = DC3<1>(v);
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


