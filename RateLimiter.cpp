/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <unordered_map>
#include <mutex>
#include <chrono>
#include <memory>

// RateLimiter Interface
class RateLimiter {
public:
    virtual bool grantAccess() = 0;
    virtual ~RateLimiter() = default;
};

// TokenBucket Implementation
class TokenBucket : public RateLimiter {
private:
    int bucketCapacity;
    int refreshRate; // tokens added per second
    std::atomic<int> currentCapacity;
    std::atomic<long long> lastUpdatedTime;

    long long currentTimeMillis() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    void refreshBucket() {
        long long currentTime = currentTimeMillis();
        int additionalTokens = static_cast<int>(((currentTime - lastUpdatedTime.load()) / 1000.0) * refreshRate);
        int updatedCapacity = std::min(currentCapacity.load() + additionalTokens, bucketCapacity);
        currentCapacity.store(updatedCapacity);
        lastUpdatedTime.store(currentTime);
    }

public:
    TokenBucket(int capacity, int rate)
        : bucketCapacity(capacity), refreshRate(rate), currentCapacity(capacity), lastUpdatedTime(currentTimeMillis()) {}

    bool grantAccess() override {
        refreshBucket();
        if (currentCapacity.load() > 0) {
            currentCapacity.fetch_sub(1);
            return true;
        }
        return false;
    }
};

// UserBucketCreator manages buckets for multiple users
class UserBucketCreator {
private:
    std::unordered_map<int, std::shared_ptr<TokenBucket>> buckets;
    std::mutex mutex;

public:
    explicit UserBucketCreator(int userId) {
        buckets[userId] = std::make_shared<TokenBucket>(10, 10);
    }

    void accessApplication(int userId) {
        std::shared_ptr<TokenBucket> bucket;
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (buckets.find(userId) == buckets.end()) {
                buckets[userId] = std::make_shared<TokenBucket>(10, 10);
            }
            bucket = buckets[userId];
        }

        if (bucket->grantAccess()) {
            std::cout << std::this_thread::get_id() << " -> able to access the application\n";
        } else {
            std::cout << std::this_thread::get_id() << " -> Too many requests, please try again later\n";
        }
    }
};

// Main application
int main() {
    UserBucketCreator userBucketCreator(1);
    std::vector<std::thread> threads;

    for (int i = 0; i < 12; ++i) {
        threads.emplace_back([&userBucketCreator]() {
            userBucketCreator.accessApplication(1);
        });
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
