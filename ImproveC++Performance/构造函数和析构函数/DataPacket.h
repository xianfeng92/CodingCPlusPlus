#ifndef DATAPACKET_H_
#define DATAPACKET_H_

class DataPacket
{
public:
    DataPacket(char *data, int sz):size(sz)
    {
        buffer = new char[sz];
        ...
    }
    ~DataPacket()
    {
        delete[] buffer;
        ...
    }
private:
    char *buffer;
};

#endif // DATAPACKET_H_
