#ifndef BRIDGE_EXPECTED_HPP
#define BRIDGE_EXPECTED_HPP

#include <string>

#include <tl/expected.hpp>

template <typename T>
using BridgeExpected = tl::expected<T, std::string>;

#endif
