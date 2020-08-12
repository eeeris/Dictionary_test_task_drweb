#pragma once
#include <map>

using namespace std;

template<class TKey, class TValue>
class TrivialDictionary : public Dictionary<TKey, TValue>
{
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

    map<TKey, TValue> dictionary;
    const TValue& Get(const TKey& key) const override
    {
        auto it = dictionary.find(key);
        if (it != dictionary.end())
        {
            return it->second;
        }
        else 
        {
            throw Exception{key};
        }
    }

    void Set(const TKey& key, const TValue& value) noexcept override // добавить - заменить
    {
        dictionary[key] = value;
    }

    bool IsSet(const TKey& key) const noexcept override // задано ли
    {
        auto it = dictionary.find(key);
        return (it != dictionary.end());

    }
};
