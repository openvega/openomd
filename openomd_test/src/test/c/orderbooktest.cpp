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
    EXPECT_EQ(dp._depth[0].size(), 1);
    EXPECT_EQ(dp._depth[1].size(), 1);
}
}