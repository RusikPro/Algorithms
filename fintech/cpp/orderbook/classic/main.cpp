#include "orderbook.h"

int main()
{
    OrderBook ob;

    // Add some orders
    ob.addOrder({1, 100.0, 10, true});  // Buy 10 @ 100.0
    ob.addOrder({2, 99.5, 5, true});    // Buy 5 @ 99.5
    ob.addOrder({3, 101.0, 8, false});  // Sell 8 @ 101.0
    ob.addOrder({4, 100.0, 12, false}); // Sell 12 @ 100.0

    ob.printOrderBook();
    std::cout << "-----------------------" << std::endl << std::endl;

    // Modify an order
    ob.modifyOrder(1, 20);  // Change orderId 1 to quantity 20
    // Delete an order
    ob.deleteOrder(4);      // Remove orderId 4

    ob.printOrderBook();

    return 0;
}
