#pragma once

namespace internal {

// std::apply reference implementation from cppreference:
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