//
//  Core.hpp
//  LighYearsGame
//
//  Created by Ori Sofer on 22/02/2025.
//

#ifndef Core_hpp
#define Core_hpp

#include <cstdio>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace ly
{
// macro
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)

    template<typename T>
    using unique = std::unique_ptr<T>;

    template<typename T>
    using shared = std::shared_ptr<T>;

    template<typename T>
    using weak = std::weak_ptr<T>;

    template<typename T>
    using List = std::vector<T>;

    template<typename Tkey, typename Tvalue, typename Tpredicate = std::less<Tkey>>
    using Map = std::map<Tkey, Tvalue, Tpredicate>;

    template<typename Tkey, typename Tvalue, typename Thasher = std::hash<Tkey>>
    using Dictionary = std::unordered_map<Tkey, Tvalue, Thasher>;

    template<typename T>
    using Set = std::unordered_set<T>;
}

#endif /* Core_hpp */
