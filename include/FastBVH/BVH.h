#pragma once

#include <FastBVH/BBox.h>
#include <FastBVH/IntersectionInfo.h>
#include <FastBVH/Ray.h>

#include <vector>

#include <cstdint>

//! \brief This namespace contains all the declarations
//! in the library. All declarations in this namespace,
//! with some exceptions, are available for end-users.
namespace FastBVH {

//! \brief Node descriptor for the flattened tree
//! \tparam Float The floating point type
//! used for the bounding box vectors.
template <typename Float>
struct BVHFlatNode final {
  //! The bounding box of the node.
  BBox<Float> bbox;
  //! The index of the first primitive.
  uint32_t start;
  //! The number of primitives in this node.
  uint32_t nPrims;
  uint32_t rightOffset;
};

//! \author Brandon Pelfrey
//! \brief A Bounding Volume Hierarchy system for fast Ray-Object intersection tests
template <typename Float, typename Primitive>
class BVH final {
  //! The number of leafs in the BVH.
  uint32_t nLeafs;
  //! The number of primitives in a single leaf.
  uint32_t leafSize;
  //! The array of primitives used to construct
  //! the BVH.
  std::vector<Primitive> build_prims;
  //! An array of nodes used for fast iteration
  //! of the BVH, using iteration.
  std::vector<BVHFlatNode<Float>> flatTree;
public:
  //! Constructs a new BVH instance.
  BVH() : nLeafs(0), leafSize(4) {}
  //! Builds the BVH. This function may be called more than once.
  //! At each call to this function, the nodes in the BVH are cleared
  //! and then remade based on the new data.
  //! \param objects The primitives to build the BVH from.
  //! \param leafSize The number of primitives per leaf.
  //! \param converter The primitive-to-box converter instance.
  template <typename BoxConverter>
  void build(std::vector<Primitive>&& objects, const BoxConverter& converter, uint32_t leafSize = 4) {

    this->nLeafs = 0;
    this->leafSize = leafSize;
    this->build_prims = std::move(objects);
    this->flatTree.clear();

    this->build(converter);
  }
  //! Gets the number of leafs in the BVH.
  //! \return The number of leafs in the BVH.
  inline auto getLeafCount() const noexcept {
    return nLeafs;
  }
  //! Accesses the BVH nodes.
  //! \return A pointer to the nodes in the BVH.
  inline const auto* getNodes() const noexcept {
    return flatTree.data();
  }
  //! Gets the number of nodes in the BVH.
  //! \return The node count of the BVH.
  inline auto getNodeCount() const noexcept {
    return flatTree.size();
  }
  //! Accesses a pointer to the primitives in the BVH.
  //! \return A const pointer to the primitive array.
  inline const auto* getPrimitives() const noexcept {
    return build_prims.data();
  }
protected:
  //! Build the BVH tree out of build_prims
  //! \param converter The primitive to bounding box converter.
  template <typename BoxConverter>
  void build(const BoxConverter& converter);
};

//! \brief Contains the context used while building
//! a specific node in the BVH.
struct BuildEntry final {
  //! If non-zero then this is the index of the parent. (used in offsets)
  uint32_t parent;
  //! The starting index of the range of primitives in this node.
  uint32_t start;
  //! The ending index of the range of primitives in this node.
  uint32_t end;
};

//! Build the BVH, given an input data set
//! - Handling our own stack is quite a bit faster than the recursive style.
//! - Each build stack entry's parent field eventually stores the offset
//!   to the parent of that node. Before that is finally computed, it will
//!   equal exactly three other values. (These are the magic values Untouched,
//!   Untouched-1, and TouchedTwice).
//! - The partition here was also slightly faster than std::partition.
//! \tparam Float The floating point type used in the BVH vectors.
//! \tparam Primtive The type of the primtive in the BVH.
template <typename Float, typename Primitive>
template <typename BoxConverter>
void BVH<Float, Primitive>::build(const BoxConverter& converter) {

  BuildEntry todo[128];
  uint32_t stackptr = 0;
  const uint32_t Untouched    = 0xffffffff;
  const uint32_t TouchedTwice = 0xfffffffd;
  uint32_t nNodes = 0;

  // Push the root
  todo[stackptr].start = 0;
  todo[stackptr].end = build_prims.size();
  todo[stackptr].parent = 0xfffffffc;
  stackptr++;

  BVHFlatNode<Float> node;
  std::vector<BVHFlatNode<Float>> buildnodes;
  buildnodes.reserve(build_prims.size()*2);

  while(stackptr > 0) {
    // Pop the next item off of the stack
    BuildEntry &bnode( todo[--stackptr] );
    uint32_t start = bnode.start;
    uint32_t end = bnode.end;
    uint32_t nPrims = end - start;

    nNodes++;
    node.start = start;
    node.nPrims = nPrims;
    node.rightOffset = Untouched;

    // Calculate the bounding box for this node
    auto bb = converter(build_prims[start]);
    auto bc = BBox<Float>(bb.getCenter());

    for(uint32_t p = start+1; p < end; ++p) {
      auto box = converter(build_prims[p]);
      bb.expandToInclude(box);
      bc.expandToInclude(box.getCenter());
    }

    node.bbox = bb;

    // If the number of primitives at this point is less than the leaf
    // size, then this will become a leaf. (Signified by rightOffset == 0)
    if(nPrims <= leafSize) {
      node.rightOffset = 0;
      nLeafs++;
    }

    buildnodes.push_back(node);

    // Child touches parent...
    // Special case: Don't do this for the root.
    if(bnode.parent != 0xfffffffc) {
      buildnodes[bnode.parent].rightOffset --;

      // When this is the second touch, this is the right child.
      // The right child sets up the offset for the flat tree.
      if( buildnodes[bnode.parent].rightOffset == TouchedTwice ) {
        buildnodes[bnode.parent].rightOffset = nNodes - 1 - bnode.parent;
      }
    }

    // If this is a leaf, no need to subdivide.
    if(node.rightOffset == 0)
      continue;

    // Set the split dimensions
    uint32_t split_dim = bc.maxDimension();

    // Split on the center of the longest axis
    Float split_coord = .5f * (bc.min[split_dim] + bc.max[split_dim]);

    // Partition the list of objects on this split
    uint32_t mid = start;
    for(uint32_t i=start;i<end;++i) {
      auto box = converter(build_prims[i]);
      if(box.getCenter()[split_dim] < split_coord ) {
        std::swap( build_prims[i], build_prims[mid] );
        ++mid;
      }
    }

    // If we get a bad split, just choose the center...
    if(mid == start || mid == end) {
      mid = start + (end-start)/2;
    }

    // Push right child
    todo[stackptr].start = mid;
    todo[stackptr].end = end;
    todo[stackptr].parent = nNodes-1;
    stackptr++;

    // Push left child
    todo[stackptr].start = start;
    todo[stackptr].end = mid;
    todo[stackptr].parent = nNodes-1;
    stackptr++;
  }

  flatTree.resize(nNodes);

  for (uint32_t n = 0; n < nNodes; n++) {
    flatTree[n] = buildnodes[n];
  }
}

} // namespace FastBVH
