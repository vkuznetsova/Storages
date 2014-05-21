#ifndef STORAGEUTILS_H
#define STORAGEUTILS_H

class StorageUtils
{
public:
    static bool equal( int count1, int count)
    {
        return count1 == count || count1 > count;
    }

    static bool greater(int count1, int count)
    {
        return count1 > count;
    }
};

#endif // STORAGEUTILS_H
