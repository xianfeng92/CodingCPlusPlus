#include <iostream>
#include "dma.h"

int main()
{
    using std::cout;
    using std::endl;

    baseDMA shirt("Protable",8);
    lacksDMA ballon("red","Blipo",4);
    hasDMA map("Mercator","Buffloa Keys", 5);

    cout << "Display base DMA object:\n";
    cout << shirt << endl;

    cout << "Lacks DMA object:\n";
    cout << ballon << endl;

    cout << "has DMA object:\n";
    cout << map << endl;

    lacksDMA ballon2(ballon);
    cout << "The result of Lacks DMA Copy:\n";
    cout << ballon2 << endl;
    hasDMA map2;
    map2 = map;
    cout << "The result of hasDMA Assignment:\n";
    cout << map2 << endl;
    return 0;
}
