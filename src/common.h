#ifndef COMMON_H
#define COMMON_H

template<class T> void safeDelete(T*& object)
{
    delete object;
    object = NULL;
}

template<class T> void safeDeleteArray(T*& array)
{
    delete[] array;
    array = NULL;
}

#endif // COMMON_H
