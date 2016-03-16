#ifndef linked_list_H
#define linked_list_H

struct linkedListItem
{
    linkedListItem * next;
    int node_id;

    linkedListItem( int node_id, linkedListItem* next )
        : node_id( node_id )
        , next( next )
    {}

    linkedListItem();

};

class LinkedList
{
    public:
        LinkedList();
        linkedListItem* first();
        linkedListItem* last();
        void append( linkedListItem * );
        void prepend( linkedListItem * );

    private:
        linkedListItem * anchor_;
        linkedListItem * end_;
};

std::ostream& operator<<( std::ostream& os, const LinkedList& ll )
{
   linkedListItem * k = ll.first();
   while( k->next != NULL )
   {
       os << k->node_id << " ";
       k = k->next;
   }
   return os;
}
#endif
