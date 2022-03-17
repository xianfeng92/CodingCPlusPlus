#ifndef NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_E6_A0_87_E5_87_86_E6_A8_A1_E6_9D_BF_E5_BA_93_PRINT_HPP_
#define NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_E6_A0_87_E5_87_86_E6_A8_A1_E6_9D_BF_E5_BA_93_PRINT_HPP_

#include<iostream>
#include<string>

template<typename T>
inline void PRINT_ELEMENT(const T& coll, const std::string& opstr = ""){
    std::cout << " ";
    for(const auto& elem : coll)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

#endif // NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_E6_A0_87_E5_87_86_E6_A8_A1_E6_9D_BF_E5_BA_93_PRINT_HPP_
