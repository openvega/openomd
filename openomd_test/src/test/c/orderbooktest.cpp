#include <gtest/gtest.h>
#include "openomd/fulltick.h"

namespace openomd
{
TEST(OrderBookTest, FullTick)
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

    EXPECT_EQ(dp._depth[0][0], Level( 18, 4000, 1 ));
    EXPECT_EQ(dp._depth[0][1], Level(20, 3000, 2));
    EXPECT_EQ(dp._depth[0][2], Level(21, 3000, 1));
    EXPECT_EQ(dp._depth[0][3], Level(22, 5000, 1));
    EXPECT_EQ(dp._depth[1][0], Level(23, 50000, 1));
    EXPECT_EQ(dp._depth[1][1], Level(24, 10000, 1));
    EXPECT_EQ(dp._depth[1][2], Level(25, 20000, 1));
    EXPECT_EQ(dp._depth[1][3], Level(26, 70000, 2));

    //ft.modifyOrder(3, 3000);
}
}