#include "MMKV.h"
#include "MMKVPredef.h"
#include "MMBuffer.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
using namespace mmkv;

const string testKey = "test";
const string testValue = "test";


void MyLogHandler(MMKVLogLevel level, const char *file, int line, const char *function, const string &message) {

    auto desc = [level] {
        switch (level) {
            case MMKVLogDebug:
                return "D";
            case MMKVLogInfo:
                return "I";
            case MMKVLogWarning:
                return "W";
            case MMKVLogError:
                return "E";
            default:
                return "N";
        }
    }();
    printf("redirecting-[%s] <%s:%d::%s> %s\n", desc, file, line, function, message.c_str());
}

void benchmarkMMKVRead(MMKV *kv, int iterations) {

    string result;
    cout << "read: "<< endl;
    kv->getString(testKey, result);
    cout << "result: " << result << endl;

     auto start = chrono::high_resolution_clock::now();
     for (int i = 0; i < iterations; ++i) {
         kv->getString(testKey, result);
     }
     auto end = chrono::high_resolution_clock::now();
     cout << "MMKVRead: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
     auto total_duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
     cout << "MMKVRead: " << static_cast<double>(total_duration) / iterations << " ns per operation" << endl;
}

void benchmarkMMKVWrite(MMKV *kv, int iterations) {

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        kv->set(testValue, testKey);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "MMKVWrite: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    auto total_duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "MMKVWrite: " << static_cast<double>(total_duration) / iterations << " ns per operation" << endl;
}

void benchmarkMMKVMultiRead(MMKV *kv, int iterations) {
    string result;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        kv->getString(testKey, result);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "MMKVMultiRead: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    auto total_duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "MMKVMultiRead: " << static_cast<double>(total_duration) / iterations << " ns per operation" << endl;
}

void benchmarkMMKVMultiWrite(MMKV *kv, int iterations) {

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        kv->set(testValue, testKey);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "MMKVMultiWrite: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    auto total_duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "MMKVMultiWrite: " << static_cast<double>(total_duration) / iterations << " ns per operation" << endl;
}

int main() {
    int iterations = 1000000; // Adjust the number of iterations as needed
    MMKV::initializeMMKV("/tmp/mmkv", MMKVLogError, MyLogHandler);
    auto kv = MMKV::defaultMMKV();
    kv->set(testValue, testKey);
    benchmarkMMKVRead(kv, iterations);
    benchmarkMMKVWrite(kv, iterations);
    benchmarkMMKVMultiRead(kv, iterations);
    benchmarkMMKVMultiWrite(kv, iterations);

    return 0;
}