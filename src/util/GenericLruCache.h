#ifndef INCLUDED_GENERIC_LRU_CACHE
#define INCLUDED_GENERIC_LRU_CACHE

#include <list>
#include <unordered_map>
#include <assert.h>

using namespace std;

template <class KEY_T, class VAL_T>
class GenericLruCache {
private:
  list< pair<KEY_T,VAL_T> > item_list;
  unordered_map<KEY_T, decltype(item_list.begin()) > item_map;
  size_t cache_size;

private:
  void clean(){
    while(item_map.size()>cache_size){
      auto last_it = item_list.end(); last_it --;
      item_map.erase(last_it->first);
      item_list.pop_back();
    }
  }

public:
  GenericLruCache(int cache_size_) : cache_size(cache_size_)
  {
  }

  size_t size() const {
    return item_list.size();
  }

  void put(const KEY_T &key, const VAL_T &val) {
    auto it = item_map.find(key);
    if(it != item_map.end()){
            item_list.erase(it->second);
            item_map.erase(it);
    }
    item_list.push_front(make_pair(key,val));
    item_map.insert(make_pair(key, item_list.begin()));
    clean();
  }

  bool exists(const KEY_T &key){
    return (item_map.count(key)>0);
  }

  VAL_T get(const KEY_T &key){
    assert(exists(key));
    auto it = item_map.find(key);
    item_list.splice(item_list.begin(), item_list, it->second);
    return it->second->second;
  }

};
#endif