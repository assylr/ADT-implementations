
#include "queue.h"

queue::queue( ):
  queue_size(0),
  front(nullptr),
  back(nullptr)
{
}

queue::queue( const queue& q ):
  queue_size(0),
  front(nullptr),
  back(nullptr)
{
  node* temp = q.front;
  while(temp != nullptr)
  {
    push(temp -> value);
    temp = temp -> next;
  }
}

const queue& queue::operator = ( const queue& q )
{
  if (&q == this)
    std::cout << "Self assignment!!!" << std::endl;
  else
  {
    clear();
    node* temp = q.front;
    while (temp != nullptr)
    {
      push(temp -> value);
      temp = temp -> next;
    }
  }
  return *this;
}

queue::~queue( )
{
  clear();
}

queue::queue( std::initializer_list< std::string > init ):
  queue_size(0),
  front(nullptr),
  back(nullptr)
{
  for (std::string new_value : init )
  {
    push(new_value);
  }
}

void queue::push( const std::string& s )
{
  node* new_node = new node(s);

  if (!back)
  {
    front = new_node;
    back = new_node;
  }
  else
  {
    back -> next = new_node;
    back = new_node;
  }
  queue_size++;
}

void queue::pop( )
{
  if (!front)
    throw std::runtime_error("pop: queue is EMPTY\n");
  else
  {
    node* old_node = front;
    front = front -> next;
    if (!front)
      back = nullptr;
    delete old_node;
    queue_size--;
  }
}

void queue::clear( )
{
  while(queue_size != 0 )
  {
    pop();
  }
}

void queue::reset( size_t s )
{
  if(s >= queue_size)
    throw std::runtime_error("reset: queue is EMPTY\n");
  else
  {
    while (queue_size != s)
      pop();
  }
}

const std::string& queue::peek( ) const
{
  if (queue_size == 0)
    throw std::runtime_error("peek: queue is EMPTY\n");
  return front -> value;
}

size_t queue::size( ) const
{
  return queue_size;
}

bool queue::empty( ) const
{
  return (queue_size == 0);
}

void queue::print( std::ostream& out ) const
{
  node* temp = front;
  out << "queue: ";
  if (!front)
  {
    out << "";
  }
  else
  {
    while (temp != nullptr)
    {
      if ( temp -> next != nullptr )
        out << temp -> value << ", ";
      else
        out << temp -> value << "";
      temp = temp -> next;
    }
  }
}
