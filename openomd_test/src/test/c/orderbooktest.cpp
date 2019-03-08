#include <gtest/gtest.h>
#include "openomd/fulltick.h"

namespace openomd
{
TEST(OrderBookTest, OMDCFullTick)
{
    OMDCFullTick ft;
    auto const& dp = ft.depth();

    ft.addOrder(1, 20, 1000, 0, '0');
    ft.addOrder(2, 20, 2000, 0, '0');
    ft.addOrder(3, 18, 4000, 0, '0');
    ft.addOrder(4, 22, 5000, 0, '0');
    ft.addOrder(5, 21, 3000, 0, '0');

    ft.addOrder(6, 24, 10000, 1, '0');
    ft.addOrder(7, 26, 30000, 1, '0');
    ft.addOrder(8, 26, 40000, 1, '0');
    ft.addOrder(9, 25, 20000, 1, '0');
    ft.addOrder(10, 23, 50000, 1, '0');
    EXPECT_EQ(dp._depth[0][0], Level(18, 4000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(20, 3000, 2));
    EXPECT_EQ(dp._depth[0][2], Level(21, 3000, 1));
    EXPECT_EQ(dp._depth[0][3], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(24, 10000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][3], Level(26, 70000, 2));

    ft.modifyOrder(3, 3000, 0);
    ft.modifyOrder(2, 1000, 0);
    ft.modifyOrder(6, 50000, 1);
    ft.modifyOrder(8, 10000, 1);
    EXPECT_EQ(dp._depth[0][0], Level(18, 3000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(20, 2000, 2));
    EXPECT_EQ(dp._depth[0][2], Level(21, 3000, 1));
    EXPECT_EQ(dp._depth[0][3], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(24, 50000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][3], Level(26, 40000, 2));

    // modify the same order again
    ft.modifyOrder(3, 30000, 0);
    ft.modifyOrder(2, 500, 0);
    ft.modifyOrder(6, 100000, 1);
    ft.modifyOrder(8, 1000, 1);
    EXPECT_EQ(dp._depth[0][0], Level(18, 30000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(20, 1500, 2));
    EXPECT_EQ(dp._depth[0][2], Level(21, 3000, 1));
    EXPECT_EQ(dp._depth[0][3], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(24, 100000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][3], Level(26, 31000, 2));
    EXPECT_EQ(dp._depth[0].size(), 4);
    EXPECT_EQ(dp._depth[1].size(), 4);

    ft.deleteOrder(1, 0);
    ft.deleteOrder(5, 0);
    ft.deleteOrder(8, 1);
    ft.deleteOrder(6, 1);
    EXPECT_EQ(dp._depth[0][0], Level(18, 30000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(20, 500, 1));
    EXPECT_EQ(dp._depth[0][2], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(26, 30000, 1));
    EXPECT_EQ(dp._depth[0].size(), 3);
    EXPECT_EQ(dp._depth[1].size(), 3);

    ft.deleteOrder(2, 0);
    ft.deleteOrder(7, 1);
    EXPECT_EQ(dp._depth[0][0], Level(18, 30000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[0].size(), 2);
    EXPECT_EQ(dp._depth[1].size(), 2);

    ft.deleteOrder(3, 0);
    ft.deleteOrder(10, 1);
    EXPECT_EQ(dp._depth[0][0], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[0].size(), 1);
    EXPECT_EQ(dp._depth[1].size(), 1);

    ft.deleteOrder(3, 0);
    ft.deleteOrder(10, 1);
    EXPECT_EQ(dp._depth[0][0], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[0].size(), 1);
    EXPECT_EQ(dp._depth[1].size(), 1);

    ft.clear();
    EXPECT_EQ(dp._depth[0].size(), 0);
    EXPECT_EQ(dp._depth[1].size(), 0);

    ft.addOrder(1, 20, 1000, 0, '0');
    ft.addOrder(2, 20, 2000, 0, '0');
    ft.addOrder(3, 18, 4000, 0, '0');
    ft.addOrder(4, 22, 5000, 0, '0');
    ft.addOrder(5, 21, 3000, 0, '0');

    ft.addOrder(6, 24, 10000, 1, '0');
    ft.addOrder(7, 26, 30000, 1, '0');
    ft.addOrder(8, 26, 40000, 1, '0');
    ft.addOrder(9, 25, 20000, 1, '0');
    ft.addOrder(10, 23, 50000, 1, '0');
    EXPECT_EQ(dp._depth[0][0], Level(18, 4000, 1));
    EXPECT_EQ(dp._depth[0][1], Level(20, 3000, 2));
    EXPECT_EQ(dp._depth[0][2], Level(21, 3000, 1));
    EXPECT_EQ(dp._depth[0][3], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(24, 10000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][3], Level(26, 70000, 2));

    ft.deleteOrder(1, 0); ft.deleteOrder(2, 0); ft.deleteOrder(3, 0); ft.deleteOrder(4, 0); ft.deleteOrder(5, 0);
    ft.deleteOrder(6, 1); ft.deleteOrder(7, 1); ft.deleteOrder(8, 1); ft.deleteOrder(9, 1); ft.deleteOrder(10, 1);
    EXPECT_EQ(dp._depth[0].size(), 0);
    EXPECT_EQ(dp._depth[1].size(), 0);
}

TEST(OrderBookTest, OMDDFullTick)
{
    OMDDFullTick ft;
    auto const& dp = ft.depth();
    ft.addOrder(1, 50, 10, 0, 0);
    ft.addOrder(2, 50, 20, 0, 0);
    ft.addOrder(3, 48, 30, 0, 0);
    ft.addOrder(4, 62, 60, 0, 0);
    ft.addOrder(5, 61, 100, 0, 0);

    ft.addOrder(1, 64, 10, 1, 0);
    ft.addOrder(2, 66, 30, 1, 0);
    ft.addOrder(3, 66, 40, 1, 0);
    ft.addOrder(4, 65, 20, 1, 0);
    ft.addOrder(5, 63, 50, 1, 0);
    EXPECT_EQ(dp._depth[0][0], Level(48, 30, 1));
    EXPECT_EQ(dp._depth[0][1], Level(50, 30, 2));
    EXPECT_EQ(dp._depth[0][2], Level(61, 100, 1));
    EXPECT_EQ(dp._depth[0][3], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(64, 10, 1));
    EXPECT_EQ(dp._depth[1][2], Level(65, 20, 1));
    EXPECT_EQ(dp._depth[1][3], Level(66, 70, 2));

    ft.modifyOrder(3, 48, 20, 0, 0);
    ft.modifyOrder(2, 50, 10, 0, 0);
    ft.modifyOrder(1, 64, 50, 1, 0);
    ft.modifyOrder(3, 66, 100, 1, 0);
    EXPECT_EQ(dp._depth[0][0], Level(48, 20, 1));
    EXPECT_EQ(dp._depth[0][1], Level(50, 20, 2));
    EXPECT_EQ(dp._depth[0][2], Level(61, 100, 1));
    EXPECT_EQ(dp._depth[0][3], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(64, 50, 1));
    EXPECT_EQ(dp._depth[1][2], Level(65, 20, 1));
    EXPECT_EQ(dp._depth[1][3], Level(66, 130, 2));

    // modify the same order again
    ft.modifyOrder(3, 47, 30, 0, 0);
    ft.modifyOrder(2, 61, 100, 0 , 0);
    ft.modifyOrder(1, 65, 10, 1, 0);
    EXPECT_EQ(dp._depth[0][0], Level(47, 30, 1));
    EXPECT_EQ(dp._depth[0][1], Level(50, 10, 1));
    EXPECT_EQ(dp._depth[0][2], Level(61, 200, 2));
    EXPECT_EQ(dp._depth[0][3], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(65, 30, 2));
    EXPECT_EQ(dp._depth[1][2], Level(66, 130, 2));
    EXPECT_EQ(dp._depth[1].size(), 3);
    ft.modifyOrder(3, 67, 200, 1, 0);
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(65, 30, 2));
    EXPECT_EQ(dp._depth[1][2], Level(66, 30, 1));
    EXPECT_EQ(dp._depth[1][3], Level(67, 200, 1));
    EXPECT_EQ(dp._depth[1].size(), 4);

    ft.deleteOrder(2, Side::Buy);
    ft.deleteOrder(1, Side::Buy);
    ft.deleteOrder(1, Side::Sell);
    ft.deleteOrder(3, Side::Sell);
    EXPECT_EQ(dp._depth[0][0], Level(47, 30, 1));
    EXPECT_EQ(dp._depth[0][1], Level(61, 100, 1));
    EXPECT_EQ(dp._depth[0][2], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(65, 20, 1));
    EXPECT_EQ(dp._depth[1][2], Level(66, 30, 1));
    EXPECT_EQ(dp._depth[0].size(), 3);
    EXPECT_EQ(dp._depth[1].size(), 3);

    ft.deleteOrder(5, Side::Buy);
    ft.deleteOrder(2, Side::Sell);
    EXPECT_EQ(dp._depth[0][0], Level(47, 30, 1));
    EXPECT_EQ(dp._depth[0][1], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(65, 20, 1));
    EXPECT_EQ(dp._depth[0].size(), 2);
    EXPECT_EQ(dp._depth[1].size(), 2);

    ft.deleteOrder(3, Side::Buy);
    ft.deleteOrder(4, Side::Sell);
    EXPECT_EQ(dp._depth[0][0], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[0].size(), 1);
    EXPECT_EQ(dp._depth[1].size(), 1);

    ft.deleteOrder(3, Side::Buy);
    ft.deleteOrder(4, Side::Sell);
    EXPECT_EQ(dp._depth[0][0], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[0].size(), 1);
    EXPECT_EQ(dp._depth[1].size(), 1);

    ft.clear();
    EXPECT_EQ(dp._depth[0].size(), 0);
    EXPECT_EQ(dp._depth[1].size(), 0);

    ft.addOrder(1, 50, 10, 0, 0);
    ft.addOrder(2, 50, 20, 0, 0);
    ft.addOrder(3, 48, 30, 0, 0);
    ft.addOrder(4, 62, 60, 0, 0);
    ft.addOrder(5, 61, 100, 0, 0);

    ft.addOrder(1, 64, 10, 1, 0);
    ft.addOrder(2, 66, 30, 1, 0);
    ft.addOrder(3, 66, 40, 1, 0);
    ft.addOrder(4, 65, 20, 1, 0);
    ft.addOrder(5, 63, 50, 1, 0);
    EXPECT_EQ(dp._depth[0][0], Level(48, 30, 1));
    EXPECT_EQ(dp._depth[0][1], Level(50, 30, 2));
    EXPECT_EQ(dp._depth[0][2], Level(61, 100, 1));
    EXPECT_EQ(dp._depth[0][3], Level(62, 60, 1));
    EXPECT_EQ(dp._depth[1][0], Level(63, 50, 1));
    EXPECT_EQ(dp._depth[1][1], Level(64, 10, 1));
    EXPECT_EQ(dp._depth[1][2], Level(65, 20, 1));
    EXPECT_EQ(dp._depth[1][3], Level(66, 70, 2));

    ft.deleteOrder(1, 0); ft.deleteOrder(2, 0); ft.deleteOrder(3, 0); ft.deleteOrder(4, 0); ft.deleteOrder(5, 0);
    ft.deleteOrder(1, 1); ft.deleteOrder(2, 1); ft.deleteOrder(3, 1); ft.deleteOrder(4, 1); ft.deleteOrder(5, 1);
    EXPECT_EQ(dp._depth[0].size(), 0);
    EXPECT_EQ(dp._depth[1].size(), 0);
}
}