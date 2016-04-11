#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H

#include <vector>
#include <cstddef>

class UnionFind
{
    public:
    UnionFind ( size_t N ) : _size ( N ), _roots ( N ), _ranks ( N, 1 )
    {
        for ( size_t i = 0; i < N; i++ )
        {
            _roots[i] = i;
        }
    }

    unsigned int find ( unsigned int a )
    {
        return get_root_path_compression ( a );
    }

    bool is_connected ( unsigned int a, unsigned int b )
    {
        return find ( a ) == find ( b );
    }

    void unite ( unsigned int a, unsigned int b )
    {
        unsigned int root_a = find ( a );
        unsigned int root_b = find ( b );
        if ( _ranks[root_a] < _ranks[root_b] )
        {

            _roots[root_a] = root_b;
        }
        else if ( _ranks[root_a] > _ranks[root_b] )
        {
            _roots[root_b] = root_a;
        }
        else
        {
            _roots[root_a] = root_b;
            _ranks[root_b] += 1;
        }
    }
    std::vector<unsigned int> _roots;
    std::vector<unsigned int> _ranks;

    private:
    size_t _size;

    unsigned int get_root_path_compression ( unsigned int a )
    {
        if ( _roots[a] == a )
        {
            return a;
        }
        const unsigned int root = get_root_path_compression ( _roots[a] );
        _roots[a] = root;
        return root;
    }

};

#endif /* DISJOINT_SETS_H */
