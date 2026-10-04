#ifndef PANS_INCLUDE_PANS_MACROS_H
#define PANS_INCLUDE_PANS_MACROS_H

// TODO: Add stacktrace
// TODO: Use logger instead of std::cerr

#include <cstdint>  // std::uint8_t, std::uint16_t, ...
#include <cstdlib>  // IWYU pragma: keep // std::abort
#include <iostream> // IWYU pragma: keep // std::cerr

#define PANS_CHECK_STMT(condition, stmt)                                       \
    if (!(condition)) [[unlikely]] {                                           \
        std::cerr << __FILE__ << ":" << __LINE__ << ": Condition failed: '"    \
                  << #condition << "'\n";                                      \
        stmt;                                                                  \
    } else                                                                     \
        (void(0))

#define PANS_CHECK_STMT_MSG(condition, stmt, msg)                              \
    if (!(condition)) [[unlikely]] {                                           \
        std::cerr << __FILE__ << ":" << __LINE__ << ": Condition failed: '"    \
                  << #condition << "' (" << msg << ")\n";                      \
        stmt;                                                                  \
    } else                                                                     \
        (void(0))

#ifdef NDEBUG
#define PANS_ABORT() (void(0))
#define PANS_ASSERT(condition) (void(0))
#define PANS_ASSERT_MSG(condition, msg) (void(0))
#else
#define PANS_ABORT() std::abort()
#define PANS_ASSERT(condition) PANS_CHECK_STMT(condition, PANS_ABORT())
#define PANS_ASSERT_MSG(condition, msg)                                        \
    PANS_CHECK_STMT_MSG(condition, PANS_ABORT(), msg)
#endif

#define PANS_CHECK(condition) PANS_CHECK_STMT(condition, PANS_ABORT())

#define PANS_CHECK_MSG(condition, msg)                                         \
    PANS_CHECK_STMT_MSG(condition, PANS_ABORT(), msg)

#define PANS_CHECK_RETURN(condition, ret)                                      \
    PANS_CHECK_STMT(condition, {                                               \
        PANS_ABORT();                                                          \
        return ret;                                                            \
    })

#define PANS_CHECK_RETURN_MSG(condition, ret, msg)                             \
    PANS_CHECK_STMT_MSG(                                                       \
        condition,                                                             \
        {                                                                      \
            PANS_ABORT();                                                      \
            return ret;                                                        \
        },                                                                     \
        msg)

#define PANS_CHECK_RETVOID(condition)                                          \
    PANS_CHECK_STMT(condition, {                                               \
        PANS_ABORT();                                                          \
        return;                                                                \
    })

#define PANS_CHECK_RETVOID_MSG(condition, msg)                                 \
    PANS_CHECK_STMT_MSG(                                                       \
        condition,                                                             \
        {                                                                      \
            PANS_ABORT();                                                      \
            return;                                                            \
        },                                                                     \
        msg)

#define PANS_CHECK_CONTINUE(condition)                                         \
    PANS_CHECK_STMT(condition, PANS_ABORT(); continue)

#define PANS_CHECK_CONTINUE_MSG(condition, msg)                                \
    PANS_CHECK_STMT_MSG(condition, PANS_ABORT(); continue, msg)

#define PANS_CHECK_BREAK(condition)                                            \
    PANS_CHECK_STMT(condition, PANS_ABORT(); break)

#define PANS_CHECK_BREAK_MSG(condition, msg)                                   \
    PANS_CHECK_STMT_MSG(condition, PANS_ABORT(); break, msg)

#define PANS_CHECK_NO_EFFECT(condition) PANS_CHECK_STMT(condition, (void(0)))

#define PANS_CHECK_NO_EFFECT_MSG(condition, msg)                               \
    PANS_CHECK_STMT_MSG(condition, (void(0)), msg)

namespace pans {

using i8 = std::int8_t;
using u8 = std::uint8_t;
using i16 = std::int16_t;
using u16 = std::uint16_t;
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

} // namespace pans

#endif // PANS_INCLUDE_PANS_MACROS_H