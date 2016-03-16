#include "linkedList.h"

struct linkedListItem
{
    int node_id;
    linkedListItem * next;

    linkedListItem( int node_id, linkedListItem* next )
        : node_id( node_id )
        , next( next )
    {}

    linkedListItem()
        : node_id( -1 )
        , next( NULL )
    {}

};

class LinkedList
{
    public:
        LinkedList()
            : anchor_( new linkedListItem( -1, NULL ) )
            , end_( anchor_ )
        {}

        linkedListItem * first() const
        {
            return anchor_;
        }

        linkedListItem * last() const
        {
            return end_;
        }


        void append( linkedListItem * item )
        {
            end_->next = item;       
            linkedListItem * k = item;
            while( k->next != NULL )
                k = k->next;
            end_ = k;
        }

        void prepend( linkedListItem * item )
        {
            linkedListItem * k = item;
            while( k->next != NULL )
                k = k->next;
            k->next = anchor_->next;
            anchor_->next = item;
        }

};

