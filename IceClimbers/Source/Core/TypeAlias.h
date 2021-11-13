#pragma once

#include <unordered_map>
#include <vector>
#include <queue>

typedef bool IsDestructible;
typedef int TileIndex;
typedef std::vector<std::pair<TileIndex, IsDestructible>> TileMap;		// tile index, isDestructible

using String = std::string;

template <typename T>
using List = std::vector<T>;

template <typename T>
using Queue = std::queue<T>;

template <typename Key, typename Value>
using HashTable = std::unordered_map<Key, Value>;

using Uint = unsigned int;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;

#define STRINGIFY(x) (#x)