
#include "set.h"

size_t case_insensitive::hash( const std::string& s )
{
  size_t hash_value = 0;
  size_t power = 1;
  size_t n = s.size();

  for (size_t i = 0; i < n; i++)
  {
    hash_value += tolower(s[n-i-1]) * power;
    power *= 31;
  }
  return hash_value;
}

bool case_insensitive::equal( const std::string& s1, const std::string& s2 )
{
  size_t equality = 0;

  if (s1.size() == s2.size())
  {
    for (size_t i = 0; i < s1.size(); i++)
    {
      if (tolower(s1[i]) == tolower(s2[i]))
        equality++;
    }
    if (equality == s1.size())
      return true;
  }
  return false;
}

bool set::insert_norehash( const std::string& s )
{
  size_t hash_index = case_insensitive::hash(s) % buckets.size();
  for (const auto& str : buckets[hash_index])
  {
    if (case_insensitive::equal(str, s))
      return false;
  }

  buckets[hash_index].push_back(s);
  set_size++;
  return true;

}

void set::consider_rehash( )
{

  if ( loadfactor() > max_load_factor)
  {
    size_t hash_index = 0;
    
    std::vector<buckettype> new_Buckets(buckets.size()*2);

    for (const auto& copyBucket : buckets)
    {
      for (const auto& str : copyBucket)
      {
        hash_index = case_insensitive::hash(str) % new_Buckets.size();
        new_Buckets[hash_index].push_back(str);
      }
    }

    buckets = new_Buckets;
  }
  else
  {
    return;
  }

}

set::set( std::initializer_list< std::string > init,
          double max_load_factor )
   : max_load_factor( max_load_factor ),
   set_size(0),
   buckets(std::vector<buckettype> (8))
{
  for (std::string str : init)
  {
    insert(str);
  }
}

bool set::contains( const std::string& s ) const
{
  size_t hash_index = case_insensitive::hash(s) % buckets.size();
  for (const auto& str : buckets[hash_index])
  {
    if (case_insensitive::equal(str, s))
      return true;
  }

  return false;
}

bool set::insert( const std::string& s )
{
  bool isInserted = insert_norehash(s);

  if (isInserted)
    consider_rehash();

  return isInserted;
}

bool set::remove( const std::string& s )
{
  size_t hash_index = case_insensitive::hash(s) % buckets.size();
  for (auto it = buckets[hash_index].begin(); it != buckets[hash_index].end(); it++)
  {
    if (case_insensitive::equal(*it, s))
    {
      buckets[hash_index].erase(it);
      set_size--;
      return true;
    }
  }

  return false;
}

size_t set::size( ) const
{
  return set_size;
}

bool set::empty( ) const
{
  if (set_size == 0)
    return true;
  else
    return false;
}

void set::clear( )
{
  for (size_t i = 0; i < buckets.size(); i++)
  {
    buckets[i].clear();
  }
  set_size = 0;
}

void set::print( std::ostream& out ) const
{
  for (size_t i = 0; i < buckets.size(); i++)
  {
    out << "bucket[" << i << "] = {";

    bool test = true;

    for (std::string str : buckets[i])
    {
      if (test)
      {
        out << str;
        test = false;
      }
      else
      {
        out << ", " << str;
      }
    }


    out << "}" << std::endl;
  }
}
