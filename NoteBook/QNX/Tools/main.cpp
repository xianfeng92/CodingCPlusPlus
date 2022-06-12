#include "zip_utils.h"

using namespace std;

int main(int argc, char **argv){
    ZIP_UTILS::CompressDirectory("hello_world.zip", "../../speech/data_enu_write");
    return 0;
}