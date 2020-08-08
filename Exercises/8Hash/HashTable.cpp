#include "HashTable.h"

using namespace std;

HashTable::HashTable()
    : buckets_(13),
    hash_([this](const string &s)
    {
        return static_cast<size_t>(s[0]) % buckets_.size();
    })
{
}

HashTable& HashTable::insert(string s)
{
    size_t h = hash_(s);
    buckets_[h].push_back(std::move(s));
    return *this;
}

bool HashTable::contains(const std::string &needle) const
{
    size_t h = hash_(needle);

    //empty bucket: not here!
    if(buckets_[h].empty())
    {
        return false;
    }

    // non-empty bucket: check each value in bucket
    for(const string &s : buckets_[h])
    {
        if(s == needle)
        {
            return true;
        }
    }

    return false;
}

vector<pair<size_t, size_t>> HashTable::bucketCounts() const
{
    vector<pair<size_t, size_t>> counts;

    for(size_t i = 0; i < buckets_.size(); i++)
    {
        counts.emplace_back(i, buckets_[i].size());
    }

    return counts;
}