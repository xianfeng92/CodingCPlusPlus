#ifndef AA54AFB5_903A_4C1E_A3BC_82D053866997
#define AA54AFB5_903A_4C1E_A3BC_82D053866997
template <typename T>
class TooBig
{
private:
    T cutoff;
public:
    TooBig(const T &t) : cutoff(t){}
    bool operator()(const T &v) {return v > cutoff;}
};

#endif /* AA54AFB5_903A_4C1E_A3BC_82D053866997 */
