#pragma once

#include <memory>

#ifdef _WIN32
#ifdef DUCKIEMAP_DEBUG
#define DC_CORE_ASSERT(x, ...) { if(!(x)) { DC_CORE_CRITICAL("Assertation failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define DC_CORE_ASSERT(x, ...)
#endif
#define TODO() { DC_CORE_CRITICAL("TODO hit in {0}:{1}", __FILE__, __LINE__); __debugbreak(); }
#define VERIFY_NOT_REACHED() DC_CORE_CRITICAL("Verify not reached hit in {0}:{1}!", __FILE__, __LINE__); __debugbreak()
#else
// TODO: figure out how to do debugging on gdb
#define DC_CORE_ASSERT(x, ...) { if(!(x)) { DC_CORE_CRITICAL("Assertation failed: {0} in {1} at {2}", __VA_ARGS__, __FILE__, __LINE__); abort(); } }
#define VERIFY_NOT_REACHED() DC_CORE_CRITICAL("Verify not reached hit in {0}:{1}!", __FILE__, __LINE__); abort()
#define TODO() { DC_CORE_CRITICAL("TODO hit in {0}:{1}", __FILE__, __LINE__); abort(); }
#endif

// Test helper macro
#define RUN_TEST(testclass) { MapTools::testclass __##testClass_instance; auto result = __##testClass_instance.run(); if (result == MapTools::TestResult::Pass) { DC_CORE_INFO("{0}: PASS",  __##testClass_instance.number()); } else { DC_CORE_ERROR("{0}: FAIL : {1}", __##testClass_instance.number(), __##testClass_instance.failDescription()); }}

// Unique pointers aka Scoped pointers
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Scope<T> createScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Shared pointers aka References
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> createRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

// Weak pointers aka Weak reference
template<typename T>
using WeakRef = std::weak_ptr<T>;

template<typename T, typename ... Args>
constexpr Ref<T> createWeakRef(Args&& ... args)
{
    return std::weak_ptr<T>(std::forward<Args>(args)...);
}
