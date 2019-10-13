#ifndef _NL_CACTUS_TABLE_H_
#define _NL_CACTUS_TABLE_H_

#include <memory>
#include <map>

/*
 * CactusTable implements a multi-map with scoping semantics.
 * It is a cactus tree (wikipedia.org/wiki/Parent_pointer_tree)
 * that is specializable on K+V to build symbol/type/vtables.
 */
template <typename K, typename V>
class CactusTable
{
  public:
    CactusTable() {}
    CactusTable(std::shared_ptr<CactusTable<K, V>> parent)
      : parent(parent) {}

    void insert(K k, V v) {
      mappings[k] = v;
    }

    bool contains(K k) const {
      if (!parent) {
        return mappings.contains(k);
      }
      return mappings.contains(k) || parent->contains(k);
    }

    V get(K k) const {
      if (mappings.contains(k) || !parent) {
        return mappings[k];;
      }
      return parent->get(k);
    }

  private:
    std::map<std::string, V>  mappings;
    std::shared_ptr<CactusTable<K, V>> parent;
};

#endif  // _NL_CACTUS_TABLE_H_
