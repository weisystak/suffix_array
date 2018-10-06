#include <DC3.hpp>
#include <gtest/gtest.h>
#include <fstream>
#include <streambuf>

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
        
        auto sa = DC3(v);

        str[str.length()-1] = '$';

        cout<<str<<endl;
        
        for(auto i:sa)
        {
            cout<<str.substr(i, 20)<<endl;
        }
    }
    
}