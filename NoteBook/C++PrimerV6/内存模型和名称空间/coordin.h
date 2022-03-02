#ifndef EA333AF0_BFEF_4F3A_8AE2_39C444BF1E82
#define EA333AF0_BFEF_4F3A_8AE2_39C444BF1E82

struct polar
{
    double distance;
    double angle;
};

struct rect
{
    double x;
    double y;
};

// prototype
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);

#endif 
/* EA333AF0_BFEF_4F3A_8AE2_39C444BF1E82 */
