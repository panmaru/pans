#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "pans/macros.h"

TEST(PansMacrosTest, TypeAliases) {
    EXPECT_TRUE((std::is_same_v<pans::i8, std::int8_t>))
        << "pans::i8 is not std::int8_t";
    EXPECT_TRUE((std::is_same_v<pans::u8, std::uint8_t>))
        << "pans::u8 is not std::uint8_t";
    EXPECT_TRUE((std::is_same_v<pans::i16, std::int16_t>))
        << "pans::i16 is not std::int16_t";
    EXPECT_TRUE((std::is_same_v<pans::u16, std::uint16_t>))
        << "pans::u16 is not std::uint16_t";
    EXPECT_TRUE((std::is_same_v<pans::i32, std::int32_t>))
        << "pans::i32 is not std::int32_t";
    EXPECT_TRUE((std::is_same_v<pans::u32, std::uint32_t>))
        << "pans::u32 is not std::uint32_t";
    EXPECT_TRUE((std::is_same_v<pans::i64, std::int64_t>))
        << "pans::i64 is not std::int64_t";
    EXPECT_TRUE((std::is_same_v<pans::u64, std::uint64_t>))
        << "pans::u64 is not std::uint64_t";
}

TEST(PansMacrosTest, CheckStmtSuccess) {
    bool stmt_executed = false;
    PANS_CHECK_STMT(true, stmt_executed = true);
    EXPECT_FALSE(stmt_executed)
        << "'PANS_CHECK_STMT' should not execute the statement on success";
}

TEST(PansMacrosTest, CheckStmtFailure) {
    bool stmt_executed = false;
    PANS_CHECK_STMT(false, stmt_executed = true);
    EXPECT_TRUE(stmt_executed)
        << "'PANS_CHECK_STMT' should execute the statement on failure";
}

TEST(PansMacrosTest, CheckStmtMsgSuccess) {
    bool stmt_executed = false;
    PANS_CHECK_STMT_MSG(true, stmt_executed = true, "Custom message");
    EXPECT_FALSE(stmt_executed)
        << "'PANS_CHECK_STMT_MSG' should not execute the statement on success";
}

TEST(PansMacrosDeathTest, CheckStmtMsgFailure) {
    bool stmt_executed = false;
    PANS_CHECK_STMT_MSG(false, stmt_executed = true, "Custom message");
    EXPECT_TRUE(stmt_executed)
        << "'PANS_CHECK_STMT_MSG' should execute the statement on failure";

    // TODO: Logger will be used to print the custom message, not stderr
    EXPECT_EXIT(
        {
            PANS_CHECK_STMT_MSG(false, std::exit(0), "Custom message");
            std::exit(1);
        },
        ::testing::ExitedWithCode(0), "Custom message")
        << "'PANS_CHECK_STMT_MSG' should print the custom message on failure";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, AbortDebug) {
    EXPECT_DEATH(
        { PANS_ABORT(); }, "")
        << "'PANS_ABORT' should abort in debug mode";
}
#else
TEST(PansMacrosDeathTest, Abort) {
    EXPECT_EXIT(
        {
            PANS_ABORT();
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_ABORT' should be a no-op in any non-debug mode";
}
#endif

TEST(PansMacrosDeathTest, CheckSuccess) {
    EXPECT_EXIT(
        {
            PANS_CHECK(true);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK' should not abort on success";
}

TEST(PansMacrosDeathTest, CheckMsgSuccess) {
    EXPECT_EXIT(
        {
            PANS_CHECK_MSG(true, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK_MSG' should not abort on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, CheckFailureDebug) {
    EXPECT_DEATH(
        { PANS_CHECK(false); }, "")
        << "'PANS_CHECK' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, CheckMsgFailureDebug) {
    // TODO: Logger will be used to print the custom message, not stderr
    EXPECT_DEATH(
        { PANS_CHECK_MSG(false, "Custom message"); }, "Custom message")
        << "'PANS_CHECK_MSG' should abort with custom message on failure in "
           "debug mode";
}
#else
TEST(PansMacrosDeathTest, CheckFailure) {
    EXPECT_EXIT(
        {
            PANS_CHECK(false);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK' should not abort on failure in any non-debug mode";
}

TEST(PansMacrosDeathTest, CheckMsgFailure) {
    // TODO: Logger will be used to print the custom message, not stderr
    EXPECT_EXIT(
        {
            PANS_CHECK_MSG(false, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "Custom message")
        << "'PANS_CHECK_MSG' should not abort on failure, but print the custom "
           "message in any non-debug mode";
}
#endif

TEST(PansMacrosDeathTest, AssertSuccess) {
    EXPECT_EXIT(
        {
            PANS_ASSERT(true);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_ASSERT' should not abort on success";
}

TEST(PansMacrosDeathTest, AssertMsgSuccess) {
    EXPECT_EXIT(
        {
            PANS_ASSERT_MSG(true, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_ASSERT_MSG' should not abort on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, AssertFailureDebug) {
    EXPECT_DEATH(
        { PANS_ASSERT(false); }, "")
        << "'PANS_ASSERT' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, AssertMsgFailureDebug) {
    // TODO: Logger will be used to print the custom message, not stderr
    EXPECT_DEATH(
        { PANS_ASSERT_MSG(false, "Custom message"); }, "Custom message")
        << "'PANS_ASSERT_MSG' should abort with custom message on failure in "
           "debug mode";
}
#else
TEST(PansMacrosDeathTest, AssertFailure) {
    EXPECT_EXIT(
        {
            PANS_ASSERT(false);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_ASSERT' should not abort on failure in any non-debug mode";
}

TEST(PansMacrosDeathTest, AssertMsgFailure) {
    EXPECT_EXIT(
        {
            PANS_ASSERT_MSG(false, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_ASSERT_MSG' should not abort on failure in any non-debug "
           "mode";
}
#endif

TEST(PansMacrosTest, CheckReturnSuccess) {
    auto func = []() -> int {
        PANS_CHECK_RETURN(true, 42);
        return 0;
    };
    EXPECT_EQ(func(), 0)
        << "'PANS_CHECK_RETURN' should not early-return on success";
}

TEST(PansMacrosTest, CheckReturnMsgSuccess) {
    auto func = []() -> int {
        PANS_CHECK_RETURN_MSG(true, 42, "Custom message");
        return 0;
    };
    EXPECT_EQ(func(), 0)
        << "'PANS_CHECK_RETURN_MSG' should not early-return on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, CheckReturnFailureDebug) {
    auto func = []() -> int {
        PANS_CHECK_RETURN(false, 42);
        return 0;
    };
    EXPECT_DEATH(
        { func(); }, "")
        << "'PANS_CHECK_RETURN' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, CheckReturnMsgFailureDebug) {
    auto func = []() -> int {
        PANS_CHECK_RETURN_MSG(false, 42, "Custom message");
        return 0;
    };
    EXPECT_DEATH(
        { func(); }, "Custom message")
        << "'PANS_CHECK_RETURN_MSG' should abort with custom message on "
           "failure in debug mode";
}
#else
TEST(PansMacrosTest, CheckReturnFailure) {
    auto func = []() -> int {
        PANS_CHECK_RETURN(false, 42);
        return 0;
    };
    EXPECT_EQ(func(), 42)
        << "'PANS_CHECK_RETURN' should early-return the fallback value on "
           "failure in release mode";
}

TEST(PansMacrosTest, CheckReturnMsgFailure) {
    auto func = []() -> int {
        PANS_CHECK_RETURN_MSG(false, 42, "Custom message");
        return 0;
    };
    EXPECT_EQ(func(), 42)
        << "'PANS_CHECK_RETURN_MSG' should early-return the fallback value "
           "on failure in release mode";
}
#endif

TEST(PansMacrosTest, CheckRetVoidSuccess) {
    bool reached_end = false;
    auto func = [&reached_end]() {
        PANS_CHECK_RETVOID(true);
        reached_end = true;
    };
    func();
    EXPECT_TRUE(reached_end)
        << "'PANS_CHECK_RETVOID' should not early-return on success";
}

TEST(PansMacrosTest, CheckRetVoidMsgSuccess) {
    bool reached_end = false;
    auto func = [&reached_end]() {
        PANS_CHECK_RETVOID_MSG(true, "Custom message");
        reached_end = true;
    };
    func();
    EXPECT_TRUE(reached_end)
        << "'PANS_CHECK_RETVOID_MSG' should not early-return on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, CheckRetVoidFailureDebug) {
    auto func = []() { PANS_CHECK_RETVOID(false); };
    EXPECT_DEATH(
        { func(); }, "")
        << "'PANS_CHECK_RETVOID' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, CheckRetVoidMsgFailureDebug) {
    auto func = []() { PANS_CHECK_RETVOID_MSG(false, "Custom message"); };
    EXPECT_DEATH(
        { func(); }, "Custom message")
        << "'PANS_CHECK_RETVOID_MSG' should abort with custom message on "
           "failure in debug mode";
}
#else
TEST(PansMacrosTest, CheckRetVoidFailure) {
    bool reached_end = false;
    auto func = [&reached_end]() {
        PANS_CHECK_RETVOID(false);
        reached_end = true;
    };
    func();
    EXPECT_FALSE(reached_end)
        << "'PANS_CHECK_RETVOID' should early-return on failure in release "
           "mode";
}

TEST(PansMacrosTest, CheckRetVoidMsgFailure) {
    bool reached_end = false;
    auto func = [&reached_end]() {
        PANS_CHECK_RETVOID_MSG(false, "Custom message");
        reached_end = true;
    };
    func();
    EXPECT_FALSE(reached_end)
        << "'PANS_CHECK_RETVOID_MSG' should early-return on failure in "
           "release mode";
}
#endif

TEST(PansMacrosTest, CheckContinueSuccess) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_CONTINUE(true);
        ++count;
    }
    EXPECT_EQ(count, 5)
        << "'PANS_CHECK_CONTINUE' should not skip iterations on success";
}

TEST(PansMacrosTest, CheckContinueMsgSuccess) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_CONTINUE_MSG(true, "Custom message");
        ++count;
    }
    EXPECT_EQ(count, 5)
        << "'PANS_CHECK_CONTINUE_MSG' should not skip iterations on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, CheckContinueFailureDebug) {
    EXPECT_DEATH(
        {
            for (int i = 0; i < 5; ++i) {
                PANS_CHECK_CONTINUE(i < 3);
            }
        },
        "")
        << "'PANS_CHECK_CONTINUE' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, CheckContinueMsgFailureDebug) {
    EXPECT_DEATH(
        {
            for (int i = 0; i < 5; ++i) {
                PANS_CHECK_CONTINUE_MSG(i < 3, "Custom message");
            }
        },
        "Custom message")
        << "'PANS_CHECK_CONTINUE_MSG' should abort with custom message on "
           "failure in debug mode";
}
#else
TEST(PansMacrosTest, CheckContinueFailure) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_CONTINUE(i < 3);
        ++count;
    }
    EXPECT_EQ(count, 3)
        << "'PANS_CHECK_CONTINUE' should skip remaining iterations on "
           "failure in release mode";
}

TEST(PansMacrosTest, CheckContinueMsgFailure) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_CONTINUE_MSG(i < 3, "Custom message");
        ++count;
    }
    EXPECT_EQ(count, 3)
        << "'PANS_CHECK_CONTINUE_MSG' should skip remaining iterations on "
           "failure in release mode";
}
#endif

TEST(PansMacrosTest, CheckBreakSuccess) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_BREAK(true);
        ++count;
    }
    EXPECT_EQ(count, 5)
        << "'PANS_CHECK_BREAK' should not break the loop on success";
}

TEST(PansMacrosTest, CheckBreakMsgSuccess) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_BREAK_MSG(true, "Custom message");
        ++count;
    }
    EXPECT_EQ(count, 5)
        << "'PANS_CHECK_BREAK_MSG' should not break the loop on success";
}

#ifndef NDEBUG
TEST(PansMacrosDeathTest, CheckBreakFailureDebug) {
    EXPECT_DEATH(
        {
            for (int i = 0; i < 5; ++i) {
                PANS_CHECK_BREAK(i < 3);
            }
        },
        "")
        << "'PANS_CHECK_BREAK' should abort on failure in debug mode";
}

TEST(PansMacrosDeathTest, CheckBreakMsgFailureDebug) {
    EXPECT_DEATH(
        {
            for (int i = 0; i < 5; ++i) {
                PANS_CHECK_BREAK_MSG(i < 3, "Custom message");
            }
        },
        "Custom message")
        << "'PANS_CHECK_BREAK_MSG' should abort with custom message on "
           "failure in debug mode";
}
#else
TEST(PansMacrosTest, CheckBreakFailure) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_BREAK(i < 3);
        ++count;
    }
    EXPECT_EQ(count, 3)
        << "'PANS_CHECK_BREAK' should break the loop on failure in release "
           "mode";
}

TEST(PansMacrosTest, CheckBreakMsgFailure) {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        PANS_CHECK_BREAK_MSG(i < 3, "Custom message");
        ++count;
    }
    EXPECT_EQ(count, 3)
        << "'PANS_CHECK_BREAK_MSG' should break the loop on failure in "
           "release mode";
}
#endif

TEST(PansMacrosDeathTest, CheckNoEffectSuccess) {
    EXPECT_EXIT(
        {
            PANS_CHECK_NO_EFFECT(true);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK_NO_EFFECT' should not abort on success";
}

TEST(PansMacrosDeathTest, CheckNoEffectMsgSuccess) {
    EXPECT_EXIT(
        {
            PANS_CHECK_NO_EFFECT_MSG(true, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK_NO_EFFECT_MSG' should not abort on success";
}

TEST(PansMacrosDeathTest, CheckNoEffectFailure) {
    // TODO: Logger will be used to print the failure message, not stderr
    EXPECT_EXIT(
        {
            PANS_CHECK_NO_EFFECT(false);
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "")
        << "'PANS_CHECK_NO_EFFECT' should not abort on failure";
}

TEST(PansMacrosDeathTest, CheckNoEffectMsgFailure) {
    // TODO: Logger will be used to print the custom message, not stderr
    EXPECT_EXIT(
        {
            PANS_CHECK_NO_EFFECT_MSG(false, "Custom message");
            std::exit(0);
        },
        ::testing::ExitedWithCode(0), "Custom message")
        << "'PANS_CHECK_NO_EFFECT_MSG' should not abort on failure, but "
           "print the custom message";
}