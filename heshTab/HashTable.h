#pragma once

#include "interface.h"
#include <vector>
#include <list>
using namespace std;

//Необходимо реализовать класс контейнера, реализующий интерфейс Dictionary и способный выбросить исключение, реализующее интерфейс NotFoundException.
//При разработке допускается использовать STL.Кроме этого, внутренняя реализация ничем не ограничена.

template<class TKey, class TValue>
class HashTable : public Dictionary<TKey, TValue>
{
public:
    explicit HashTable(size_t num_buckets = 100) : buckets(num_buckets) {};

    using Bucket = list<pair<TKey, TValue>>;
    vector<Bucket> buckets;

    hash<TKey> hash_func = {};
    

    class Exception : public NotFoundException<TKey>
    {
    public:
        Exception(TKey key) : key(move(key)) {}

        const TKey& GetKey() const noexcept override
        {
            return key;
        }
    private:
        TKey key;

    };

    pair <Bucket&, TValue*> Find(const TKey& key) const
    {
        auto bucket_number = hash_func(key) % buckets.size();
        auto& bucket = buckets[bucket_number];
        auto it = find_if(bucket.begin(), bucket.end(), [key](pair <TKey, TValue> const& item) {return (item.first == key); });
        if (it == bucket.end())
        {
            return { const_cast<Bucket&>(bucket), nullptr };
        }
        return { const_cast<Bucket&>(bucket), const_cast<TValue*>(&(it->second)) };
    }

    const TValue& Get(const TKey& key) const override
    {
        if (auto [bucket, p_value] = Find(key); p_value)
        {
            return *p_value;
        }
        throw Exception{ key };
    }

    void Set(const TKey& key, const TValue& value) override // добавить - заменить
    {
        /*auto bucket_number = hash_func(key) % buckets.size();
        auto& bucket = buckets[bucket_number];
        auto it = find_if(bucket.begin(), bucket.end(), [key](pair <TKey, TValue> const& item) {return (item.first == key); });*/
        auto [bucket, p_value] = Find(key);
        if (p_value == nullptr)
        {
            bucket.push_back({ key, value });
        }
        else
        {
            *p_value = value;
        }

    }

    bool IsSet(const TKey& key) const override // задано ли
    {
        /*auto bucket_number = hash_func(key) % buckets.size();
        auto& bucket = buckets[bucket_number];
        auto it = find_if(bucket.begin(), bucket.end(), [key](pair <TKey, TValue> const& item) {return (item.first == key); });*/
        auto [bucket, p_value] = Find(key);
        return (p_value);
    }
};