#pragma once

#include <FastBVH/impl/Array.h>

namespace FastBVH {

namespace impl {

//! Used to contain a series of Morton
//! codes that are specifically associated
//! with a set of geometric primitives.
template <typename Index>
class MortonTable final {

 public:

  //! Represents a single entry in the table.
  struct Entry final {
    //! The morton code for this table entry.
    Index code;
    //! The index of the primitive that the code corresponds to.
    Index primitive;
  };

  //! Constructs a new Morton table.
  //! \param size the number of entries to allocate for the table.
  MortonTable(Size size) : entries(size) {}

  //! Initializes a code in the table.
  //! This sets the Morton code value as well as the index of the primitive.
  //! \param index The index of the table entry to initialize.
  //! This value is also assigned as the primitive's index.
  //! \param code The code to assign the entry.
  inline void initCode(Size index, Index code) noexcept {
    entries[index].code = code;
    entries[index].primitive = index;
  }

  //! Indicates the number of entries in the table.
  auto size() const noexcept { return entries.size(); }

  //! Sorts the table according to the Morton codes.
  void sort();

  //! Accesses a code in the Morton table.
  //! This function does not perform bounds checking.
  //! \param index The index of the code to access.
  //! \return A const-reference to the specified code.
  const auto& operator [] (Size index) const noexcept {
    return entries[index].code;
  }

  //! Accesses the index of a primitive assigned to a certain entry.
  //! \param index The index of the entry to get the primitive of.
  //! \return An index to the primitive corresponding to a certain Morton code.
  auto getPrimitive(Size index) const noexcept {
    return entries[index].primitive;
  }

 private:

  //! The array of table entries.
  Array<Entry> entries;
};

} // namespace impl

} // namespace FastBVH

#include <FastBVH/impl/MortonTable.inl>
