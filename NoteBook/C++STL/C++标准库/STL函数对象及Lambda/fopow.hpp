#ifndef NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_STL_E5_87_BD_E6_95_B0_E5_AF_B9_E8_B1_A1_E5_8F_8ALAMBDA_FOPOW_HPP_
#define NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_STL_E5_87_BD_E6_95_B0_E5_AF_B9_E8_B1_A1_E5_8F_8ALAMBDA_FOPOW_HPP_

#include <math>

template<typename T1, typename T2>
struct fopow{
    T1 operator()(T1 base, T2 exp) const {
        return std::pow(base, exp);
    }
};

#endif // NOTEBOOK_C_2B_2BSTL_C_2B_2B_E6_A0_87_E5_87_86_E5_BA_93_STL_E5_87_BD_E6_95_B0_E5_AF_B9_E8_B1_A1_E5_8F_8ALAMBDA_FOPOW_HPP_
