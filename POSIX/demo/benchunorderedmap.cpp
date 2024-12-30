#include  "MMKV.h"
#include "MMKVPredef.h"
#include "MMBuffer.h"
#include "MMKV_IO.h"
#include "KeyValueHolder.h"
#include <iostream>
#include <chrono>
using namespace std;
using namespace mmkv;

// using MMKVMap = std::unordered_map<std::string, mmkv::KeyValueHolder, KeyHasher, KeyEqualer>;

int main() {
   string value = "value";
   MMBuffer data((void *) value.data(), value.length(), MMBufferNoCopy);
    
   mmkv::MMKVMap *m_dic = new mmkv::MMKVMap();

   string key = "test";
   bool isDataHolder = true;
   auto ret = make_pair(true, KeyValueHolder(key.length(), value.length(), 0));
   // Print ret contents
   cout << "ret.first (success): " << (ret.first ? "true" : "false") << endl;
   cout << "ret.second (KeyValueHolder) - keyLength: " << ret.second.keySize 
        << ", valueLength: " << ret.second.valueSize 
        << ", offset: " << ret.second.offset << endl;

   // Insert some test data into the map
   m_dic->emplace(key, std::move(ret.second));

   auto it = m_dic->find(key);
   cout << "it.first (success): " << (it != m_dic->end() ? "true" : "false") << endl;
   cout << "it.second (KeyValueHolder) - keyLength: " << it->second.keySize 
        << ", valueLength: " << it->second.valueSize 
        << ", offset: " << it->second.offset << endl;
   // Measure the time taken for 1000000 find operations
   auto start = chrono::high_resolution_clock::now();
   for (int i = 0; i < 1000000; ++i) {
       m_dic->find(key);
   }
   auto end = chrono::high_resolution_clock::now();

   // Calculate the average time per find operation in nanoseconds
   auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
   double average_time = static_cast<double>(duration) / 1000000;

   // Print the average time
   cout << "Average time per find operation: " << average_time << " ns" << endl;

// simple unordered map with string value
    std::unordered_map<std::string, std::string> m_dic2;
    m_dic2.emplace(key, value);
   start = chrono::high_resolution_clock::now();
   for (int i = 0; i < 1000000; ++i) {
       m_dic2.find(key);
   }
   end = chrono::high_resolution_clock::now();

   // Calculate the average time per find operation in nanoseconds
   duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
   average_time = static_cast<double>(duration) / 1000000;

   // Print the average time
   cout << "Average time per find operation: " << average_time << " ns" << endl;

   delete m_dic;
  
   return 0;
}
