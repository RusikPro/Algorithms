#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;

// Order Types
enum OrderType { BUY, SELL };

// Order Class
struct Order {
    int orderId;
    double price;
    int quantity;
    OrderType type;
};

// Simple Order Book for Market Making
class OrderBook {
private:
    map<double, vector<Order>, greater<double>> buyOrders;  // Buy side
    map<double, vector<Order>, less<double>> sellOrders;    // Sell side

public:
    void placeOrder(Order order) {
        if (order.type == BUY) {
            buyOrders[order.price].push_back(order);
        } else {
            sellOrders[order.price].push_back(order);
        }
    }

    void printOrderBook() {
        cout << "\n--- Order Book ---\n";
        cout << "Buy Orders:\n";
        for (const auto& [price, orders] : buyOrders) {
            cout << "Price: " << price << " | Quantity: " << orders.size() << "\n";
        }
        cout << "Sell Orders:\n";
        for (const auto& [price, orders] : sellOrders) {
            cout << "Price: " << price << " | Quantity: " << orders.size() << "\n";
        }
    }

    void matchOrders() {
        while (!buyOrders.empty() && !sellOrders.empty()) {
            auto highestBuy = buyOrders.begin();
            auto lowestSell = sellOrders.begin();

            if (highestBuy->first >= lowestSell->first) {
                // Orders can be matched
                int matchQuantity = min(highestBuy->second[0].quantity, lowestSell->second[0].quantity);
                cout << "Matched Order: " << matchQuantity << " @ " << lowestSell->first << "\n";

                highestBuy->second[0].quantity -= matchQuantity;
                lowestSell->second[0].quantity -= matchQuantity;

                // Remove orders if fully matched
                if (highestBuy->second[0].quantity == 0)
                    highestBuy->second.erase(highestBuy->second.begin());
                if (lowestSell->second[0].quantity == 0)
                    lowestSell->second.erase(lowestSell->second.begin());

                // Remove empty price levels
                if (highestBuy->second.empty())
                    buyOrders.erase(highestBuy);
                if (lowestSell->second.empty())
                    sellOrders.erase(lowestSell);
            } else {
                // No match, break the loop
                break;
            }
        }
    }
};

// Risk Manager
class RiskManager {
private:
    double maxPositionSize;
    double currentPosition;

public:
    RiskManager(double maxSize) : maxPositionSize(maxSize), currentPosition(0) {}

    bool canPlaceOrder(Order order) {
        if (order.type == BUY) {
            return (currentPosition + order.quantity) <= maxPositionSize;
        } else {
            return (currentPosition - order.quantity) >= -maxPositionSize;
        }
    }

    void updatePosition(Order order) {
        if (order.type == BUY) {
            currentPosition += order.quantity;
        } else {
            currentPosition -= order.quantity;
        }
        cout << "Current Position: " << currentPosition << "\n";
    }
};

// Pricing Model
class PricingModel {
public:
    double calculateMidPrice(double bid, double ask) {
        return (bid + ask) / 2.0;
    }

    pair<double, double> getQuotes(double midPrice, double spread) {
        double bid = midPrice - spread / 2;
        double ask = midPrice + spread / 2;
        return {bid, ask};
    }
};

// Market Maker System
class MarketMaker {
private:
    OrderBook orderBook;
    RiskManager riskManager;
    PricingModel pricingModel;

public:
    MarketMaker(double maxPositionSize) : riskManager(maxPositionSize) {}

    void receiveMarketData(double bid, double ask) {
        double midPrice = pricingModel.calculateMidPrice(bid, ask);
        double spread = 0.02;  // Example spread

        // Generate bid/ask quotes
        auto [quoteBid, quoteAsk] = pricingModel.getQuotes(midPrice, spread);

        // Create orders
        Order buyOrder = {1, quoteBid, 100, BUY};
        Order sellOrder = {2, quoteAsk, 100, SELL};

        // Place orders if risk allows
        if (riskManager.canPlaceOrder(buyOrder)) {
            orderBook.placeOrder(buyOrder);
            riskManager.updatePosition(buyOrder);
        }
        if (riskManager.canPlaceOrder(sellOrder)) {
            orderBook.placeOrder(sellOrder);
            riskManager.updatePosition(sellOrder);
        }

        // Match orders
        orderBook.matchOrders();

        // Print order book
        orderBook.printOrderBook();
    }
};

// Simulate Market Data Feed
void marketDataFeed(MarketMaker& marketMaker) {
    vector<pair<double, double>> mockData = {
        {100.0, 100.5}, {100.1, 100.6}, {99.9, 100.4}, {101.0, 101.5}
    };

    for (const auto& [bid, ask] : mockData) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "\nNew Market Data: Bid = " << bid << " Ask = " << ask << "\n";
        marketMaker.receiveMarketData(bid, ask);
    }
}

int main() {
    MarketMaker marketMaker(500); // Set maximum position size to 500 units
    marketDataFeed(marketMaker);

    return 0;
}
