#pragma once

#include "CArray_iterator.h"

template<typename TData>
class CArray
{
public:
  // iterators
  using iterator = CArray_iterator<TData>;
  using const_iterator = CArray_iterator<TData>;

  CArray();

  CArray(
      const CArray& _array
  );

  CArray(
      CArray&& _array
  );

  ~CArray();

  void push_back(
      const TData& _value
  );

  void push_back(
      TData&& _value
  );

  void insert(
      unsigned int _index,
      const TData& _value
  );

  void erase(
      unsigned int _index
  );

  void erase(
      const_iterator _it
  );

  void clear();

  unsigned int size() const;

  TData& operator[](
      unsigned int _index
  );

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

private:

  void add_memory(
      unsigned int _additional_size = 0
  );

  TData* alloc_space(
      unsigned int _size
  );


protected:
  TData* buffer_;
  unsigned int size_;
  unsigned int cap_;
};

#include "CArray.hpp"