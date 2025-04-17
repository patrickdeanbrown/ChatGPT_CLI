#include <gtest/gtest.h>
#include "commandcontext.hpp"

TEST(CommandContextTest, ParsesCommandOnly) {
    CommandContext ctx;
    ctx.setCommandAndArgs("%help");
    EXPECT_EQ(ctx.getCommand(), "%help");
    EXPECT_EQ(ctx.getArgumentsSize(), 0);
}

TEST(CommandContextTest, ParsesCommandWithArguments) {
    CommandContext ctx;
    ctx.setCommandAndArgs("%save myfile.txt");
    EXPECT_EQ(ctx.getCommand(), "%save");
    ASSERT_EQ(ctx.getArgumentsSize(), 1);
    EXPECT_EQ(ctx.getArgument(0), "myfile.txt");
}

TEST(CommandContextTest, HandlesMultipleArguments) {
    CommandContext ctx;
    ctx.setCommandAndArgs("%do arg1 arg2 arg3");
    EXPECT_EQ(ctx.getCommand(), "%do");
    ASSERT_EQ(ctx.getArgumentsSize(), 3);
    EXPECT_EQ(ctx.getArgument(0), "arg1");
    EXPECT_EQ(ctx.getArgument(1), "arg2");
    EXPECT_EQ(ctx.getArgument(2), "arg3");
}

TEST(CommandContextTest, HandlesEmptyInput) {
    CommandContext ctx;
    ctx.setCommandAndArgs("");
    EXPECT_EQ(ctx.getCommand(), "");
    EXPECT_EQ(ctx.getArgumentsSize(), 0);
}

TEST(CommandContextTest, HandlesWhitespaceInput) {
    CommandContext ctx;
    ctx.setCommandAndArgs("   %clear   ");
    EXPECT_EQ(ctx.getCommand(), "%clear");
    EXPECT_EQ(ctx.getArgumentsSize(), 0);
}
