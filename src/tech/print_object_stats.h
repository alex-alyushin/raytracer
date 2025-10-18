#ifndef PRINT_OBJECT_STATS_H
#define PRINT_OBJECT_STATS_H

#include <iostream>
#include <iomanip>

#include "geometry/vec.h"
#include "geometry/ray.h"
#include "physics/intersection.h"
#include "scene/triangle.h"
#include "scene/sphere.h"

inline void dump_object_stat() {
    #ifdef ENABLE_OBJECT_COUNTING
        std::cout
            << "\t"
            << "intersection: " << intersection::get_alive_count() << " = " << intersection::get_object_count() << " - " << intersection::get_destroyed_count() << "\t"
            << "vec: " << vec::get_alive_count() << " = " << vec::get_object_count() << " - " << vec::get_destroyed_count() << "\t"
            << std::endl;
            // << std::flush;
    #else
        (void)0;
    #endif
}

inline void print_object_statistics() {
    #ifdef ENABLE_OBJECT_COUNTING
        std::cout << "\n";

        std::cout << "========================================================================\n";
        std::cout << "                     Object Lifecycle Statistics\n";
        std::cout << "========================================================================\n";

        std::cout
            << std::left << std::setw(20) << "Class"
            << std::right << std::setw(15) << "Created"
            << std::right << std::setw(15) << "Destroyed"
            << std::right << std::setw(15) << "Alive" << "\n";

        std::cout << "------------------------------------------------------------------------\n";

        std::cout
            << std::left    << std::setw(20)    << "vec"
            << std::right   << std::setw(15)    << vec::get_object_count()
            << std::right   << std::setw(15)    << vec::get_destroyed_count()
            << std::right   << std::setw(15)    << vec::get_alive_count()
            << "\n";

        std::cout
            << std::left    << std::setw(20)    << "ray"
            << std::right   << std::setw(15)    << ray::get_object_count()
            << std::right   << std::setw(15)    << ray::get_destroyed_count()
            << std::right   << std::setw(15)    << ray::get_alive_count()
            << "\n";

        std::cout
            << std::left    << std::setw(20)    << "intersection"
            << std::right   << std::setw(15)    << intersection::get_object_count()
            << std::right   << std::setw(15)    << intersection::get_destroyed_count()
            << std::right   << std::setw(15)    << intersection::get_alive_count()
            << "\n";

        std::cout
            << std::left    << std::setw(20)    << "triangle"
            << std::right   << std::setw(15)    << triangle::get_object_count()
            << std::right   << std::setw(15)    << triangle::get_destroyed_count()
            << std::right   << std::setw(15)    << triangle::get_alive_count()
            << "\n";

        std::cout
            << std::left    << std::setw(20)    << "sphere"
            << std::right   << std::setw(15)    << sphere::get_object_count()
            << std::right   << std::setw(15)    << sphere::get_destroyed_count()
            << std::right   << std::setw(15)    << sphere::get_alive_count()
            << "\n";

        std::cout << "========================================================================\n";

        std::cout << "\n";
    #else
        (void)0;
    #endif
}

#endif
