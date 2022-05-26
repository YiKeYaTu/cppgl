//
// Created by lc on 2022/4/28.
//

#ifndef CPPGL_DEBUG_HPP
#define CPPGL_DEBUG_HPP

#ifndef CPPGL_DEBUG_MODE
#define CPPGL_DEBUG_MODE true
#endif

#if CPPGL_DEBUG_MODE
#define requireBuilt() \
if (isBuilt() == false) { \
    throw std::runtime_error("Object is not built yet."); \
}
#else
#define requireWindowContext()
#endif


#endif //CPPGL_DEBUG_HPP
