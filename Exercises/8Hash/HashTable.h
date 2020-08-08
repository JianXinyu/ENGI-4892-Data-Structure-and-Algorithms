#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <functional>
#include <string>
#include <vector>

class HashTable{
public:
    HashTable();

    HashTable& insert(std::string);
    bool contains(const std::string &)const;

    std::vector<std::pair<size_t,size_t >> bucketCounts() const;

private:
    using HashFn = std::function< size_t (const std::string&) >;

    std::vector<std::vector<std::string>> buckets_;
    HashFn hash_;
};
#endif //HASHTABLE_H
