#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include<tuple>

auto get_student(int id) 
{
    if(id == 0)
    {
        return std::make_tuple(3.8,'A',"zhangsan");
    }
    else if (id == 1)
    {
        return std::make_tuple(3.9,'A',"Lisi");
    }
    else if (id == 2)
    {
        return std::make_tuple(4.1,'A',"Wanger");
    }
    else
    {
        return std::make_tuple(4.1,'A',"NIO");
    }
}


int main(int argc, char **argv)
{


    // g++ --std=c++14 testDemo.cpp

    // std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    // std::cout << std::get<std::string>(t) << std::endl;
    // std::cout << std::get<3>(t) << std::endl;

    auto student = get_student(0);
    std::cout <<"ID:0, "
    << "GAP is " << std::get<0>(student) << ", "
    << "成绩 is " << std::get<1>(student) << ", "
    << "姓名 is " << std::get<2>(student) << ", " << std::endl;

    // double gpa;
    // char grade;
    // std::string name;

    // std::tie(gpa, grade,name) = get_student(1);

    // std::cout << "ID: 1, "
    // << "GPA: " << gpa << ", "
    // << "成绩: " << grade << ", "
    // << "姓名: " << name << '\n';

   

    // std::vector<int > v;
    // std::cout << "v size is " << v.size() << std::endl;
    // std::cout << "v capacity is " << v.capacity() << std::endl;

    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);

    // std::cout << "v size is " << v.size() << std::endl;
    // std::cout << "v capacity is " << v.capacity() << std::endl;

    // v.push_back(4);
    // v.push_back(5);

    // std::cout << "v size is " << v.size() << std::endl;
    // std::cout << "v capacity is " << v.capacity() << std::endl;

    // std::cout << "v front is " << v.front() << std::endl;
    // std::cout << "v back is " << v.back() <<std::endl;
    
    // v.pop_back();
    // std::cout << "v size is " << v.size() << std::endl;
    // std::cout << "v capacity is " << v.capacity() << std::endl;

    // v.shrink_to_fit();
    // std::cout << "v size is " << v.size() << std::endl;
    // std::cout << "v capacity is " << v.capacity() << std::endl;
    // std::unordered_map<int, std::string> uMap = {
    //     {1, "1"},
    //     {3, "3"},
    //     {2, "2"}
    // };

    // std::map<int, std::string> map = {
    //     {1, "1"},
    //     {3, "3"},
    //     {2, "2"}
    // };

    // std::cout << "std::unordered_map" << std::endl;

    // for(const auto & n : uMap)
    // {
    //      std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    // }

    // std::cout << std::endl;
    // std::cout << "std::map" << std::endl;
    // for(const auto & n : map )
    // {
    //     std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    // }


}