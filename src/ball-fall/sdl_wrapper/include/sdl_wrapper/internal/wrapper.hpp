#pragma once

#include <memory>

namespace sdl {
namespace internal {

template <class T, void(*F)(T*)>
class Wrapper {
public:
    explicit Wrapper(T* ptr)
        : _value(ptr, F)
    {
        assert(_value);
    }

    const T* get() const noexcept
    {
        return _value.get();
    }

private:
    std::shared_ptr<T> _value;
};

}} // namespace sdl::internal