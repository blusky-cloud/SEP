#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include <string>

namespace sep
{
    //  resource is an addressable unit of information, either
    // a collection (List) or instance of an object.
    struct Resource
    {
        std::string href; // optional
        std::string type_info;
        //virtual void ForPolymorphismOnly (){};
    };
}; // namespace sep

#endif // __RESOURCE_H__