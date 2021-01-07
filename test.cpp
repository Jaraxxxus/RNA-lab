#include "pch.h"
#include <gtest/gtest.h>
#include "rna.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


namespace {
    class RnaFixture : public testing::Test {
    public:
        RNA rna1, rna2, rna3;
    };
}


TEST_F(RnaFixture, eq) {
    rna1[0] = RNA::A;
    EXPECT_EQ(rna1[0], RNA::A);
    rna1[0] = rna2[1] = RNA::G;
    EXPECT_EQ(rna1[0], RNA::G);
    EXPECT_EQ(rna2[1], RNA::G);
}

TEST_F(RnaFixture, plus) {
    for (int i = 0; i < 100; i++) {
        rna1[i] = RNA::G;
        rna2[i] = RNA::A;
    }
    rna3 = rna1 + rna2;
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(rna3[i], rna1[i]);
        ASSERT_EQ(rna3[i + 100], rna2[i]);
    }
}

TEST_F(RnaFixture, 1mil) {
    for (int i = 0; i < 1000000; i++) {
        rna1[i] = RNA::C;
    }
    for (int i = 91; i < 1000000; i += 20317) {
        ASSERT_EQ(rna1[i], RNA::C);
    }
}

TEST_F(RnaFixture, cpy) {
    for (int i = 0; i < 1000; i += 3) {
        rna1[i] = RNA::G;
        rna1[i + 1] = RNA::A;
        rna1[i + 2] = RNA::C;
    }
    rna2 = rna1;
    ASSERT_EQ(rna1, rna2);
    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(rna1[i], rna2[i]);
    }
    const RNA rna4(rna1);
    ASSERT_EQ(rna1, rna4);
    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(rna4[i], rna1[i]);
    }
}

/*TEST_F(RnaFixture, split) {
    for (int i = 0; i < 1000; i += 3) {
        rna1[i] = RNA::G;
        rna1[i + 1] = RNA::A;
        rna1[i + 2] = RNA::C;
    }
    rna2 = rna1.delp(100);
    for (int i = 0; i < 1000 - 100; i++) {
        ASSERT_EQ(rna1[i + 100], rna2[i]);
    }
}*/

TEST_F(RnaFixture, big_rad) {
    rna1[0] = RNA::C;
    rna1[1000000000] = rna1[0];
    ASSERT_EQ(rna1[0], RNA::C);
    ASSERT_EQ(rna1[1000000000], RNA::C);
}
/*
TEST_F(RnaFixture, empty_split) {
    rna2 = rna1.split(100);
    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(rna1[i], NULL);
    }
}*/

TEST_F(RnaFixture, unavailibale_pos) {
    for (int i = 0; i < 100000; i++) {
        ASSERT_EQ(rna1[i], NULL);
    }
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}