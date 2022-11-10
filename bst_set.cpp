
#include "set.h"

const treenode* find( const treenode* n, const std::string& s )
{
  if (n == nullptr)
  {
    return nullptr;
  }
  else
  {
    while (n != nullptr)
    {
      if (s > n-> value) // to right subtree
        n = n-> right;

      else if (s < n-> value) // to left subtree
        n = n-> left;

      else if (s == n-> value)
        return n;
    }
    return nullptr;
  }
}

treenode** find( treenode** n, const std::string& s )
{
  if (*n == nullptr)
  {
    return n;
  }
  else
  {
    while (*n != nullptr)
    {
      if ( s > (*n)-> value)
        n = &((*n)-> right);

      else if ( s < (*n)-> value)
        n = &((*n)-> left);

      else if ( s == (*n)-> value)
        return n;
    }
    return n;
  }
}

size_t size( const treenode* n )
{
  if (n == nullptr)
    return 0;
  else
    return (1 + size(n->right) + size(n->left));
}

size_t height( const treenode* n )
{
  if (n == nullptr)
    return 0;
  else
  {
    size_t ltree_height = height (n->left);
    size_t rtree_height = height (n->right);

    if (ltree_height > rtree_height)
      return 1 + ltree_height;
    else
      return 1 + rtree_height;
  }
}

void deallocate( treenode* n )
{
  if (n == nullptr)
    return;

  deallocate (n->left);
  deallocate (n->right);

  delete n;
  n = nullptr;

}

treenode* makecopy( const treenode* n )
{
  if (n == nullptr)
    return nullptr;

  treenode* new_copy = new treenode (n->value);

  new_copy -> left = makecopy(n->left);
  new_copy -> right = makecopy(n->right);

  return new_copy;

}


void print( std::ostream& out, const treenode* n, unsigned int indent )
{
   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  ";
   if(n)
   {
      out << ( n -> value ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 );
   }
   else
      out << "#\n";
}


// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent.

void checkbetween( const treenode* n,
                   const std::string* lowerbound,
                   const std::string* upperbound )
{
   while(n)
   {
      if( lowerbound && *lowerbound >= n -> value )
      {
         std::cout << "value " << ( n -> value );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" );
      }

      if( upperbound && n -> value >= *upperbound )
      {
         std::cout << "value " << ( n -> value );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );
      }

      checkbetween( n -> left, lowerbound, &( n -> value ));
      lowerbound = & ( n -> value );
      n = n -> right;
   }
}


unsigned int log_base2( size_t s )
{
  if (s == 0)
  {
    return 0;
  }
  else if (s == 1)
  {
    return 0;
  }

  return 1 + log_base2(s/2);
}

bool set::contains( const std::string& s ) const
{
  if (find(tr, s) == nullptr)
    return false;
  else
    return true;
}


bool set::insert( const std::string& s )
{
  treenode** insert_position = find (&tr, s);

  if (*insert_position == nullptr)
  {
    treenode* to_insert = new treenode(s);
    *insert_position = to_insert;

    return true; // operation succesfull
  }
  else
    return false; // operation failed

}

size_t set::size( ) const
{
  return ::size(tr);
}

size_t set::height( ) const
{
  return ::height(tr);
}

bool set::empty( ) const
{
  if (tr == nullptr)
    return true;
  else
    return false;
}

set:: ~set( )
{
  deallocate(tr);
}

void set::clear( )
{
  deallocate(tr);
  tr = nullptr;
}

set::set( const set& other )
{
  tr = makecopy(other.tr);
}


set& set::operator = ( const set& other )
{
  if (&other != this) // assignment operator works with the condition that it is not self assignment
  {
    deallocate(tr);
    tr = makecopy(other.tr);
  }
  return *this;
}



void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


void set::print( std::ostream& out, unsigned int indent ) const
{
   ::print( out, tr, indent );
}
