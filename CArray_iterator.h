#pragma once

#include <iterator>

// simple iterator
template <class TData>
class CArray_iterator
{
public:
  using iterator_type             = TData;
  using iterator_category         = std::input_iterator_tag;
  using value_type                = iterator_type;
  using difference_type           = ptrdiff_t;
  using reference                 = iterator_type&;
  using pointer                   = iterator_type*;

  iterator_type* value;

  CArray_iterator(
      const CArray_iterator& other
  );

private:

  template <class TData>
  friend class CArray;

  CArray_iterator(
      TData* p
  );

public:

  CArray_iterator::pointer operator->();
  CArray_iterator::reference operator*();
  CArray_iterator& operator++();
  CArray_iterator& operator--();

  bool operator!=(
    const CArray_iterator& other
    ) const;
};

#include "CArray_iterator.hpp"