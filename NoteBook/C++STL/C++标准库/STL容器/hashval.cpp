#include <functional>


template <typename T>
inline void hash_combine(std::size_t& seed, const T& val) {
    seed = std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed>>2);
}


template <typename T, typename ...Types>
inline void hash_value(std::size_t& seed, const T& val, const Type& ...args) {
    hash_combine(seed, val);
    hash_value(seed, args...);
}


template <typename ...Types>
inline std::size_t hash_value(const Types& ...args) {
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}