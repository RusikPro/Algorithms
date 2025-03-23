#include "orderbook.h"

void OrderBook::addOrder ( Order const & newOrder )
{
    // Select the proper side: bids for buy orders, asks for sell orders.
    auto& sideMap = newOrder.isBuy ? bids_ : asks_;

    // Find the price level, or create it if it doesn't exist.
    auto plIt = sideMap.find( newOrder.price );
    if ( plIt == sideMap.end() )
    {
        auto result = sideMap.emplace(
            newOrder.price, PriceLevel( newOrder.price )
        );
        plIt = result.first;
    }

    // Insert the new order at the back of the deque.
    plIt->second.orders.push_back( newOrder );

    // Get an iterator to the newly added order.
    auto orderIt = --plIt->second.orders.end();

    // Record the location for quick access later.
    orderLookup_[ newOrder.orderId ] = { plIt, orderIt, newOrder.isBuy };
}

void OrderBook::modifyOrder ( OrderId orderId, int newQuantity )
{
    // 1. Find the order location in the hash map
    auto it = orderLookup_.find( orderId );
    if ( it == orderLookup_.end() )
    {
        std::cerr << "OrderId " << orderId << " not found." << std::endl;
        return;
    }

    // 2. Access the iterators
    OrderLocation & loc = it->second;
    auto& order = *( loc.orderIt );

    // 3. Modify the order
    order.quantity = newQuantity;

    // If the new quantity is 0 or less, remove the order.
    if ( newQuantity <= 0 )
    {
        deleteOrder(orderId);
    }
}

void OrderBook::deleteOrder ( OrderId orderId )
{
    // 1. Find the order in the hash map
    auto it = orderLookup_.find( orderId );
    if ( it == orderLookup_.end() )
    {
        std::cerr << "OrderId " << orderId << " not found." << std::endl;
        return;
    }

    // 2. Erase from the list in the PriceLevel
    OrderLocation& loc = it->second;
    auto& sideMap = loc.isBuy ? bids_ : asks_;
    auto& level = loc.priceLevelIt->second;

    // Erase the order from the deque.
    // Note: Erasing from a deque may invalidate iterators, unlike std::list.
    level.orders.erase( loc.orderIt );

    // If no orders remain at that price, remove the price level.
    if (level.orders.empty())
    {
        sideMap.erase(loc.priceLevelIt);
    }

    // Remove the order's location entry.
    orderLookup_.erase(it);
}

void OrderBook::printOrderBook () const
{
    std::cout << "=== Bids (Descending) ===" << std::endl;
    // Reverse iterate over bids (highest price first).
    for (auto it = bids_.rbegin(); it != bids_.rend(); ++it)
    {
        const auto& price = it->first;
        const auto& level = it->second;
        std::cout << "Price: " << price << " (Orders: "
            << level.orders.size() << ")" << std::endl
        ;
        for ( const auto& order : level.orders )
        {
            std::cout << "  OrderId: " << order.orderId << ", Qty: "
                << order.quantity << std::endl
            ;
        }
    }

    std::cout << "=== Asks (Ascending) ===" << std::endl;
    // Iterate over asks (lowest price first).
    for ( const auto& pair : asks_ )
    {
        const auto& price = pair.first;
        const auto& level = pair.second;
        std::cout << "Price: " << price << " (Orders: " << level.orders.size()
            << ")" << std::endl
        ;
        for ( const auto& order : level.orders )
        {
            std::cout << "  OrderId: " << order.orderId << ", Qty: "
                << order.quantity << std::endl
            ;
        }
    }
}
