#include <FastBVH/impl/MortonTable.h>

#include <algorithm>

namespace FastBVH {

namespace impl {

//! Used for comparing Morton codes in entries.
//! \tparam Index The index type of the entries.
template <typename Index>
struct EntryComparator final {

  //! A simple type definition for a single entry.
  using Entry = typename MortonTable<Index>::Entry;

  //! Compares the Morton codes of two entries.
  //! \return True if the code of @p a is less than that of @p b.
  bool operator () (const Entry& a, const Entry& b) const noexcept {
    return a.code < b.code;
  }
};

template <typename Index>
void MortonTable<Index>::sort() {

  EntryComparator<Index> comparator;

  std::sort(&entries[0], &entries[0] + entries.size(), comparator);
}

} // namespace impl

} // namespace FastBVH
