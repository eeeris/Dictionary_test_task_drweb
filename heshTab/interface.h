#pragma once

template<class TKey, class TValue>
class Dictionary
{
public:
    virtual ~Dictionary() = default;

    virtual const TValue& Get(const TKey& key) const = 0; //получить
    virtual void Set(const TKey& key, const TValue& value) = 0; // задать - изменить
    virtual bool IsSet(const TKey& key) const = 0; // задано ли
};

template<class TKey>
class NotFoundException : public std::exception
{
public:
    virtual const TKey& GetKey() const noexcept = 0;
};