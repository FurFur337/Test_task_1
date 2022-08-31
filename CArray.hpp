#pragma once

#include "CArray.h"
#include "CArray_iterator.h"

#include <cstring>
#include <cstdio>
#include <algorithm>

template<typename TData>
inline CArray<TData>::CArray()
  : buffer_(nullptr)
  , size_(0)
  , cap_(0)
{
}

template<typename TData>
inline CArray<TData>::CArray(
    const CArray& _array
)
  : buffer_(nullptr)
  , size_(_array.size_)
  , cap_(_array.cap_)
{
  TData* new_buffer = this->alloc_space(_array.size_);

  // call copy constructor for each element, since we don't use proper allocator right now
  for (int i = 0; i < _array.size_; i++)
    new(new_buffer + i) TData(_array.buffer_[i]);

  this->buffer_ = new_buffer;
}

template<typename TData>
inline CArray<TData>::CArray(
    CArray&& _array
)
  : buffer_(_array.buffer_)
  , size_(_array.size_)
  , cap_(_array.cap_)
{
  _array.buffer_ = nullptr;
  _array.size_ = 0;
  _array.cap_ = 0;
}

template<typename TData>
inline CArray<TData>::~CArray()
{
  this->clear();
}

template<typename TData>
inline void CArray<TData>::push_back(
    const TData& _value
)
{
  if (this->size_ == this->cap_)
    this->add_memory();

  // new placement copy constructor
  new(buffer_ + size_++) TData(_value);
}

template<typename TData>
inline void CArray<TData>::push_back(
    TData&& _value
)
{
  if (this->size_ == this->cap_)
    this->add_memory();

  // new placement move constructor
  new(buffer_ + size_++) TData(std::move(_value));
}

template<typename TData>
inline void CArray<TData>::insert(
    unsigned int _index,
    const TData& _value
)
{
  if (_index == this->size_ + 1)
  {
    this->push_back(_value);
    return;
  }

  // Если индекс больше нашего размера,
  // то нам необходимо заполнить свободное пространство дефолтными конструкторами
  // todo exceptions
  if (_index > this->size_)
  {
    if (_index > this->cap_)
    {
      this->add_memory(_index - this->cap_);
    }

    int cond = _index - 1;
    while (this->size_ < cond)
    {
      this->push_back(TData());
    }

    this->push_back(_value);
    return;
  }

  TData* new_buffer = this->alloc_space(++this->cap_);

  if (_index != 0)
  {
    std::memcpy(new_buffer, this->buffer_, _index * sizeof(TData));
  }

  new(new_buffer + _index) TData(_value);

  std::memcpy(&new_buffer[_index + 1], &this->buffer_[_index], sizeof(TData) * (this->size_++ - _index));

  std::free(this->buffer_);
  this->buffer_ = new_buffer;
}

template<typename TData>
inline void CArray<TData>::erase(
    unsigned int _index
)
{
  if (_index >= this->size_)
    return;

  // we can erase last index for 'free'
  if (_index == this->size_-1)
  {
    this->buffer_[_index].~TData();
    this->size_--;
    return;
  }

  // resize with any other reason
  TData* new_buffer = this->alloc_space(this->cap_);

  if (_index != 0)
  {
    std::memcpy(new_buffer, this->buffer_, _index * sizeof(TData));
  }

  std::memcpy(&new_buffer[_index], &this->buffer_[_index + 1], sizeof(TData) * (this->size_ - _index));

  this->size_--;
  this->buffer_[_index].~TData();

  std::free(this->buffer_);
  this->buffer_ = new_buffer;
}

template<typename TData>
inline void CArray<TData>::erase(
    const_iterator _it
)
{
  int index = std::distance(this->begin(), _it);
  this->erase(index);
}

template<typename TData>
inline void CArray<TData>::clear()
{
  if (this->buffer_ == nullptr)
    return;

  for (int i = 0; i < this->size_; i++)
  {
    this->buffer_[i].~TData();
  }

  std::free(this->buffer_);

  this->buffer_ = nullptr;
  this->size_ = 0;
  this->cap_ = 0;
}

template<typename TData>
inline unsigned int CArray<TData>::size() const
{
  return this->size_;
}

template<typename TData>
inline TData& CArray<TData>::operator[](
    unsigned int _index
)
{
  return this->buffer_[_index];
}

template<typename TData>
inline typename CArray<TData>::iterator CArray<TData>::begin()
{
  return iterator(&this->buffer_[0]);
}

template<typename TData>
inline typename CArray<TData>::iterator CArray<TData>::end()
{
  return iterator(&this->buffer_[this->size_]);
}

template<typename TData>
inline typename CArray<TData>::const_iterator CArray<TData>::begin() const
{
  return const_iterator(&this->buffer_[0]);
}

template<typename TData>
inline typename CArray<TData>::const_iterator CArray<TData>::end() const
{
  return const_iterator(&this->buffer_[this->size_]);
}

template<typename TData>
inline void CArray<TData>::add_memory(
    unsigned int _additional_size
)
{
  this->cap_ = !_additional_size ? this->size_ + 3 : this->cap_ + _additional_size + 3;

  // since we need 'raw' memory without calling constructors again
  TData* new_buffer = this->alloc_space(this->cap_);

  // move old buffer to the new memory
  std::memcpy(new_buffer, this->buffer_, this->size_ * sizeof(TData));

  // dealloc old memory
  std::free(this->buffer_);

  this->buffer_ = new_buffer;
}

template<typename TData>
inline TData* CArray<TData>::alloc_space(
    unsigned int _size
)
{
  // todo exceptions

  TData* raw_buffer = static_cast<TData*>(std::malloc(this->cap_ * sizeof(TData)));
  std::memset(raw_buffer, 0, this->cap_ * sizeof(TData));

  return raw_buffer;
}
