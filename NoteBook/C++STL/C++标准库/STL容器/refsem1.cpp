#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <string>

using namespace std;

class Item {
 private:
  std::string name;
  float price;

 public:
  Item(const std::string& n, float p = 0.0f) : name(n), price(p) {}

  string getName() const { return name; }

  void setName(const std::string& n) { name = n; }

  float getPrice() const { return price; }

  void setPrice(float p) { price = p; }
};

template <typename Coll>
void printItems(const std::string& msg, const Coll& coll) {
  cout << msg << endl;
  for (const auto& item : coll) {
    cout << item.getName() << " " << item.getPrice() << endl;
  }
}

int main(int argc, char** argv) {

    typedef shared_ptr<Item> ItemPtr;
    set<ItemPtr> allItems;

    deque<ItemPtr> bestSelles;

    bestSelles = {ItemPtr(new Item("YYY",12.21)), ItemPtr(new Item("hhhh",12.21), ItemPtr(new Item("he",12.21),ItemPtr(new Item("UUU",32.21))};

    allItems = {ItemPtr(new Item("qqq",12.21)), ItemPtr(new Item("mmm",12.21))};

    allItems.insert(bestSelles.begin(), bestSelles.end());

    printItems("bestSelles", bestSelles);
    printItems("allItems", allItems);
    cout << endl;

    for_each(bestSelles.begin(), bestSelles.end(),[](shared_ptr<ItemPtr>& item) {
        elem->setPrice(elem->getPrice()*2);
    });

    bestSelles[1] = *(std::find_if(allItems.begin(), allItems.end(),[](shared_ptr<ItemPtr>& item) {
        return item->getName() == "pizza";
    }));

    return 0;
}
