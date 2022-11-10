
#include "stack.h"

void stack::ensure_capacity( size_t c )
{
  if ( c <= current_capacity ){
  }
  else{
    unsigned int p = 10; // some random value for temporary time
    unsigned int new_capacity = 1;
    unsigned int base = 2;
    for (size_t i = 1; i <= p ; ++i){

      new_capacity = new_capacity * base;

      if ( c <= new_capacity ){
        current_capacity = new_capacity;
        break;
      }
      else{
        ++p;
        continue;
      }

    }
    double* new_data = new double[current_capacity];
    std::copy(&data[0], &data[current_size], new_data);
    delete[] data;
    data = new_data;
  }
}
   // Keep current_capacity always in powers of two.

stack::stack( ):
  current_size(0),
  current_capacity(4),
  data(new double[4])
{

}
   // Constructs empty stack.

stack::stack( const stack& s ):
  current_size(s.current_size),
  current_capacity(s.current_capacity*2)
{
  data = new double[s.current_capacity*2];
  std::copy(&s.data[0], &s.data[current_size], data);
}
   // use std::copy

const stack& stack::operator = ( const stack& s )
{
  ensure_capacity(s.current_size);
  current_size = s.current_size;

  std::copy(&s.data[0], &s.data[s.current_size], data);

  return *this;

}
   // use ensure_capacity and std::copy.

stack::~stack( )
{
  delete[] data;
}

void stack::push( double d )
{
  ensure_capacity(current_size + 1);

  data[current_size] = d;
  ++current_size;
}

stack::stack( std::initializer_list< double > init ):
  current_size(0),
  current_capacity(init.size()),
  data(new double[init.size()])
{
  for ( double val_init : init ){
    push(val_init);
  }
}
   // 1. either use push( ), or
   // 2. ensure_capacity.

void stack::pop( )
{
  if ( current_size == 0 )
    throw std::runtime_error("pop: stack is empty");
  current_size--;
}

void stack::clear( )
{
  current_size = 0;
}

void stack::reset( size_t s )
{
  if( s <= size() )
    current_size = s;
}

double stack::peek( ) const
{
  if ( current_size == 0 )
    throw std::runtime_error("peek: stack is empty");

  return data[current_size - 1];
}

size_t stack::size( ) const
{
  return current_size;
}

bool stack::empty( ) const
{
  return (current_size == 0);
}

void stack::print( std::ostream& out ) const
{
  out << "stack: ";
  for (size_t i = 0; i < current_size; ++i){
    if ( i < current_size - 1)
      out << data[i] << ", ";
    else{
      out << data[i] << std::endl;
    }
  }
}
   // make sure that printing is correct and commas are put properly
   // between the stack elements. Make sure to print into out and not
   // std::cout.
