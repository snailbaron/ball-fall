#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../lru_cache.hpp"

#include <cmath>

TEST_CASE("LRU cache test", "[lru]")
{
    auto callCount = 0;

    LruCache<int, int> cache(
        2,
        [&callCount] (const int& x) {
            callCount++;
            return x * x;
        });

    CHECK(cache.get(1) == 1);
    CHECK(callCount == 1);

    CHECK(cache.get(1) == 1);
    CHECK(callCount == 1);

    CHECK(cache.get(2) == 4);
    CHECK(callCount == 2);

    CHECK(cache.get(2) == 4);
    CHECK(callCount == 2);

    CHECK(cache.get(1) == 1);
    CHECK(callCount == 2);

    CHECK(cache.get(3) == 9);
    CHECK(callCount == 3);

    CHECK(cache.get(1) == 1);
    CHECK(callCount == 3);

    CHECK(cache.get(2) == 4);
    CHECK(callCount == 4);
}