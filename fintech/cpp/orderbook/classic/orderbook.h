#ifndef __FINTECH_CPP_ORDERBOOK_CLASSIC__ORDERBOOK_H__
#define __FINTECH_CPP_ORDERBOOK_CLASSIC__ORDERBOOK_H__

#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
#include <string>

using OrderId = int;

// A simple order structure.
struct Order
{
    OrderId orderId;
    double price;
    int quantity;
    bool isBuy; // true = buy, false = sell
};

// A price level holds orders at the same price, now using a deque.
struct PriceLevel
{
    double price;
    std::list<Order> orders; // using std::list for stable iterators

    PriceLevel(double p) : price(p) {}
};

class OrderBook
{
public:
    // Methods to add, modify, and delete orders.
    void addOrder(const Order& newOrder);
    void modifyOrder(OrderId orderId, int newQuantity);
    void deleteOrder(OrderId orderId);

    // For demonstration, print out the current order book.
    void printOrderBook() const;

private:
    // Use two maps: one for bids and one for asks.
    std::map<double, PriceLevel> bids_;
    std::map<double, PriceLevel> asks_;

    // To quickly locate an order, we store its position:
    struct OrderLocation
    {
        std::map<double, PriceLevel>::iterator priceLevelIt;
        std::list<Order>::iterator orderIt;
        bool isBuy;
    };

    std::unordered_map<OrderId, OrderLocation> orderLookup_;
};

#endif // __FINTECH_CPP_ORDERBOOK_CLASSIC__ORDERBOOK_H__
