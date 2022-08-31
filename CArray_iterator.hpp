#pragma once

#include "CArray_iterator.h"

template<class TData>
inline CArray_iterator<TData>::CArray_iterator(
    const CArray_iterator& other
)
  : value(other.value)
{
}

template<class TData>
inline CArray_iterator<TData>::CArray_iterator(
    TData* p
)
  : value(p)
{
}

template<class TData>
inline typename CArray_iterator<TData>::pointer CArray_iterator<TData>::operator->()
{
  return this->p;
}

template<class TData>
inline typename CArray_iterator<TData>::reference CArray_iterator<TData>::operator*()
{
  return *value;
}

template<class TData>
inline typename CArray_iterator<TData>& CArray_iterator<TData>::operator++()
{
  value += 1;
  return *this;
}

template<class TData>
inline typename CArray_iterator<TData>& CArray_iterator<TData>::operator--()
{
  value--;
  return *this;
}

template<class TData>
inline bool CArray_iterator<TData>::operator!=(
    const CArray_iterator& other
) const
{
  return value != other.value;
}


