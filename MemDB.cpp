#include <unordered_map>
#include <string>
#include <iostream>
using std::unordered_map;
using std::string;
using std::cout;

class InMemoryDB{
  unordered_map<string, int> MemDB;
  bool curr_transaction;
  unordered_map<string, int> current;

  public:
  InMemoryDB();
  int get(string key);
  void put(string key, int val);
  void begin_transaction();
  void commit();
  void rollback();
};

InMemoryDB::InMemoryDB(){
    curr_transaction = false;
}

int InMemoryDB::get(string key){
    if (MemDB.count(key)){
        return MemDB[key];
    }
    else{
        return -1;
    }
}

void InMemoryDB::put(string key, int val){
    if (curr_transaction){
        if (current.count(key)){
            current.at(key) = val;
        }
        else{
            current[key] = val;
        }
    }
    else{
        cout << "Error: no current transaction.\n";
    }
}

void InMemoryDB::begin_transaction(){
    if (curr_transaction){
        cout << "Transaction ongoing!\n";
        return;
    }
    curr_transaction = true;
}

void InMemoryDB::commit(){
    if (curr_transaction){
    for (unordered_map<string, int>::iterator it = current.begin(); it != current.end(); ++it){
        if (MemDB.count(it->first)){
        MemDB.at(it->first) = it->second;
        }
        else MemDB[it->first] = it->second;
    }
    current.clear();
    curr_transaction = false;
    }
    else cout << "Error: no current transaction.\n";
}

void InMemoryDB::rollback(){
    if (curr_transaction){
    current.clear();
    curr_transaction = false;
    }
    else cout << "Error: no current transaction.\n";
}

int main(){
    InMemoryDB inmemoryDB;
    cout << inmemoryDB.get("A") << std::endl;
    inmemoryDB.put("A", 5);
    inmemoryDB.begin_transaction();
    inmemoryDB.put("A", 5);
    cout << inmemoryDB.get("A") << std::endl;
    inmemoryDB.put("A", 6);
    inmemoryDB.commit();
    cout << inmemoryDB.get("A") << std::endl;
    inmemoryDB.commit();
    inmemoryDB.rollback();
    cout << inmemoryDB.get("B") << std::endl;
    inmemoryDB.begin_transaction();
    inmemoryDB.put("B", 10);
    inmemoryDB.rollback();
    cout << inmemoryDB.get("B") << std::endl;

    return 0;
}