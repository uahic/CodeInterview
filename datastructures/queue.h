#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <queue>
#include <cmath>

using std::swap;

template <typename Iterator>
Iterator get_middle ( const Iterator &begin, const Iterator &end, std::random_access_iterator_tag )
{
    Iterator middle = begin + std::floor ( ( end - begin ) / 2 );
    return middle;
}

template <typename Iterator> class MutablePriorityQueue
{
    public:
    MutablePriorityQueue ( Iterator &begin, Iterator &end )
    : _heap ( begin, end ), _positions ( _heap.size () )
    {
        make_heap( begin, end );
    }

    void pop()
    {
        swap(*_heap.begin(), *_heap.end());
        swap(*_positions.begin(), *_positions.end());
        _heap.pop_back();
        _positions.pop_back();
        sift_down( _heap.begin(), _heap.end(), _heap.begin() );
    }



    private:
    std::vector<typename std::iterator_traits<Iterator>::value_type> _heap;
    std::vector<unsigned int> _positions;

    void sift_down ( const Iterator start )
    {
        auto position = std::distance ( begin, start );
        // is equivalent to left_child = begin[ start*2 + 1];
        Iterator left_child = std::next ( start, position + 1 );
        Iterator right_child = std::next ( start, position + 2 );
        if ( right_child >= end )
            return;

        if ( *start > *left_child )
        {
            swap ( *start, *left_child );
            sift_down ( begin, end, left_child );
        }
        if ( *start > *right_child )
        {
            swap ( *start, *right_child );
            sift_down ( begin, end, right_child );
        }
    }

    void make_heap ( const Iterator &begin, const Iterator end )
    {
        Iterator middle =
        get_middle ( begin, end, typename std::iterator_traits<Iterator>::iterator_category () );
        for ( Iterator i = middle; i != end; i++ )
        {
            swap ( *i, *begin );
            sift_down ( begin, end, begin );
        }
    }
};

#endif /* ifndef QUEUE_H */
