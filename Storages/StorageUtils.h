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

   /* static int expense()
    {
        int exp = 7;
        return exp;
    }*/
};

#endif // STORAGEUTILS_H
