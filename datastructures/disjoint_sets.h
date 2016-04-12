#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H 

template <typename T>
class UnionFind
{
    public:
    UnionFind( size_t size )
        : _size( size )
    {}

    bool find( T& a, T& b)
    {
    }

    void unite( T& a, T& b)
    {
    }

    private:
        size_t _size;
};
#endif /* DISJOINT_SETS_H */
