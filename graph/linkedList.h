#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
struct SLLItem
{
    T data;
    SLLItem<T> * next;
    SLLItem()
        : next( NULL )
        , data()
    {}
    SLLItem( T data )
        : next( NULL )
        , data( data )
    {}
};

template <typename T>
struct LinkedList
{
    SLLItem<T> * first;
    SLLItem<T> * last;

    LinkedList()
        : first( NULL )
        , last( NULL )
    {}

    void push_back( T data )
    {
        SLLItem<T> * item = new SLLItem<T>( data );
        if( last == NULL )
        {
            last = item;
            first = item;
        }
        else
        {
            last->next = item;
            last = item;
        }
    }


    bool is_empty()
    {
        if( last == NULL )
            return true;
        return false;
    }

    T pop_front()
    {
        SLLItem<T> * old_first = first;
        if(old_first != NULL)
            first = first->next;
        
        return old_first->data;
    }

};

#endif
