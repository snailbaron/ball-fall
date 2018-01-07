#pragma once

#include <list>
#include <utility>
#include <map>
#include <algorithm>
#include <functional>
#include <tuple>

namespace internal {

// Reference implementation of std::apply from cppreference:
// http://en.cppreference.com/w/cpp/utility/apply

namespace detail {
template <class F, class Tuple, std::size_t... I>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
{
    return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
}
} // namespace detail

template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return detail::apply_impl(
        std::forward<F>(f), std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

} // namespace internal

template <class Key, class Value>
class LruCache {
public:
    LruCache(size_t capacity, std::function<Value(const Key&)> generator)
        : _capacity(capacity)
        , _generator(std::move(generator))
    { }

    const Value& get(Key&& key)
    {
        auto mapIt = _searchMap.find(key);
        if (mapIt == _searchMap.end()) {
            auto value = _generator(key);
            push(std::forward<Key>(key), std::move(value));
            return _pairsList.front().second;
        }

        auto listIt = mapIt->second;
        if (listIt != _pairsList.begin()) {
            std::iter_swap(listIt, _pairsList.begin());
            std::swap(
                _searchMap[_pairsList.front().first], _searchMap[listIt->first]);
        }
        return _pairsList.front().second;
    }

    void clear()
    {
        _searchMap.clear();
        _pairsList.clear();
    }

private:
    using PairsList = std::list<std::pair<Key, Value>>;
    using SearchMap = std::map<Key, typename PairsList::iterator>;

    void push(const Key& key, Value&& value)
    {
        if (_pairsList.size() == _capacity) {
            _searchMap.erase(_pairsList.back().first);
            _pairsList.pop_back();
        }
        _pairsList.emplace_front(key, std::move(value));
        _searchMap[key] = _pairsList.begin();
    }

    size_t _capacity;
    PairsList _pairsList;
    SearchMap _searchMap;
    std::function<Value(const Key&)> _generator;
};

template <class Value, class... Keys>
class MultiKeyLruCache {
public:
    MultiKeyLruCache(size_t capacity, std::function<Value(const Keys&...)> generator)
        : _cache(
            capacity,
            [generator] (const std::tuple<Keys...>& keyTuple) -> Value {
                return internal::apply(generator, keyTuple);
            })
    { }

    const Value& get(const Keys&... keys)
    {
        return _cache.get(std::make_tuple(keys...));
    }

    void clear()
    {
        _cache.clear();
    }

private:
    LruCache<std::tuple<Keys...>, Value> _cache;
};