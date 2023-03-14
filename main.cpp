#include <cctype>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

string months[] = {"January",   "February", "March",    "April",
                   "May",       "June",     "July",     "August",
                   "September", "October",  "November", "December"};


class Date {

private:
  int month2;
  int day;
  int year;
  int date;
  string month;

public:
  Date(int m, int d, int y) {
    month2 = m;
    day = d;
    year = y;
  }

  Date() { // system date
    const int century = 1900;
    time_t timer;
    tm *time;
    std::time(&timer);
    time = localtime(&timer);
    date = time->tm_mday;
    month = months[time->tm_mon];
    year = time->tm_year + century;
  }

  void getSystemDate() {
    cout << "Date added: " << month << " " << date << ", " << year << endl;
  }

  void setDate() { // user input

    cout << "\nMonth (mm): ";
    cin >> month;

    cout << "\nDay (dd): ";
    cin >> day;

    cout << "\nYear (yyyy): ";
    cin >> year;
  }

  void setDate(int m, int d, int y) {
    month = m;
    day = d;
    year = y;
  }
  string getDate() {
    string m = to_string(month2);
    string d = to_string(day);
    string y = to_string(year);

    return m + "/" + d + "/" + y;
  }

  int getMonth() { return month2; }
  int getDay() { return day; }
  int getYear() { return year; }

  
  void testDate() {
    Date testDate(11, 23, 2022);

    if (testDate.getMonth() == 11 && testDate.getDay() == 23 &&
        testDate.getYear() == 2022 && testDate.getDate() == "11/23/2022") {
      cout << "\nTest initilizing date...... Passed\n";
    } else {
      cout << "\nTest initilizing date...... Failed\n";
    }
  }
};
class Inventory {
private:
  int itemId;
  int quantity;
  int wholeSaleCost;
  int retailCost;
  Date itemDate;

public:
  friend istream &operator>>(istream &in, Inventory &inv);
  Inventory(int i, int q, int w, int r, int month, int day, int year) {
    itemId = i;
    quantity = q;
    wholeSaleCost = w;
    retailCost = r;
    itemDate.setDate(month, day, year);
    if (itemId > 5 || itemId < 0)
      itemId = 0;
    if (quantity < 0)
      quantity = 0;
    if (wholeSaleCost < 0)
      wholeSaleCost = 0;
  }

  Inventory(int i, int q, int w, int r) {
    itemId = i;
    quantity = q;
    wholeSaleCost = w;
    retailCost = r;
    itemDate.setDate(9, 9, 99);
    if (itemId > 99999 || itemId < 0)
      itemId = 0;
    if (quantity < 0)
      quantity = 0;
    if (wholeSaleCost < 0)
      wholeSaleCost = 0;
  }

  Inventory() {
    itemId = 0;
    quantity = 0;
    wholeSaleCost = 0;
    retailCost = 0;
  }
  // getters
  int getId() { return itemId; }
  int getQuantity() { return quantity; }
  int getWholeSaleCost() { return wholeSaleCost; }
  int getRetailCost() { return retailCost; }
  string getItemDate() { return itemDate.getDate(); }
  // setters
  void setId(int i) { itemId = i; }
  void setQuantity(int q) { quantity = q; }
  void setWholeSaleCost(int w) { wholeSaleCost = w; }
  void setRetailCost(int r) { retailCost = r; }
  void setItemDate(int m, int d, int y) { itemDate.setDate(m, d, y); }

  void getInformation() {
    cout << "\nId: " << itemId << "\nQuantity: " << quantity;
    cout << "\nWhole Sale Cost: " << wholeSaleCost
         << "\nRetail Cost: " << retailCost << endl;
    itemDate.getSystemDate();
  }

  void testInventory() {
    Inventory testInv(1, 5, 25, 50);

    if (testInv.getId() == 1 && testInv.getQuantity() == 5 &&
        testInv.getWholeSaleCost() == 25 && testInv.getRetailCost() == 50) {
      cout << "Testing Inventory constructer...... Passed\n";
    } else {
      cout << "Testing Inventory constructer...... Failed\n";
    }
  }
};


class NotArrayList {

private:
  int size;
  int count;

public:
  Inventory **array = nullptr;
  friend ostream &operator<<(ostream &, const NotArrayList &);
  NotArrayList(int s) {
    size = s;
    array = new Inventory *[size];
    count = 0;
  }

  NotArrayList() {
    size = 0;
    array = new Inventory *[size];
    count = 0;
  }

  ~NotArrayList() {
    cout << "\n\nSetting array to null\n";
    cout << "Freeing " << size << " element(s)...\n";
    for (int i = 0; i < size; i++) {
      cout << "\nElement at " << &array[i] << " "
           << "set to null";
      delete array[i];
      array[i] = nullptr;
    }
    cout << "\n\nArray at " << &array << " set to null\n";
    array = nullptr;
  }

  void addValue(Inventory &item) { // add inventory if it already exists
    if (count < size) {            // check to see if array is empty
      array[count] = &item;
      count++;
    } else if (count >= size) { // create temp ptr to add new element
      Inventory **temp = nullptr;
      size += 1;
      count++;
      temp = new Inventory *[size];
      for (int i = 0; i < size; i++) {
        temp[i] = array[i];
      }
      temp[size - 1] = &item;
      delete[] array;
      array = temp;
      temp = nullptr;
    } else {
      cout << "Error";
    }
  }

  
  void createInv(int id, int q, int w,
                 int r) { // create new inventory and append to array
    if (count < size) {
      array[count] = new Inventory(id, q, w, r);
      count++;
    } else if (count >= size) {
      Inventory **temp = nullptr;
      size += 1;
      count++;
      temp = new Inventory *[size];
      for (int i = 0; i < size; i++) {
        temp[i] = array[i];
      }
      temp[size - 1] = new Inventory(id, q, w, r);
      delete[] array;
      array = temp;
      temp = nullptr;
    } else {
      cout << "Error";
    }
  }

  void createInv() { // create new inventory and append to array
    if (count < size) {
      array[count] = new Inventory();
      count++;
    } else if (count >= size) {
      Inventory **temp = nullptr;
      size += 1;
      count++;
      temp = new Inventory *[size];
      for (int i = 0; i < size; i++) {
        temp[i] = array[i];
      }
      temp[size - 1] = new Inventory();
      delete[] array;
      array = temp;
      temp = nullptr;
    } else {
      cout << "Error";
    }
  }

 
  void deleteInv() {
    size--;
    Inventory **tmpArr = new Inventory *[size];
    count--;
    for (int i = 0; i < size; i++) {
      tmpArr[i] = array[i];
    }
    delete[] array;
    array = tmpArr;
    tmpArr = nullptr;
  }

  void returnInventory() { // return inventory information
    for (int i = 0; i < size; i++) {
      cout << endl;
      cout << "\nItem " << i + 1;
      array[i]->getInformation();
    }
  }

  
  void editInventory(int index) {
    cout << "\nChoose one of the items to edit\n";
    cout << "1. Item Id\n2. Quantity\n3. Wholesale Cost\n4. Retail Cost\n>>> ";
    int input;
    cin >> input;

   
    if (input == 1) {
      cout << "\nEnter new id: ";
      cin >> input;
      if (input > 99999 || input < 0) {
        cout << "\nFive digits only\n";
        this->editInventory(index);
      } else {
        this->array[index]->setId(input);
        cout << "\nChanged Id to " << input << endl;
      }
    } else if (input == 2) {
      cout << "\nEnter new quantity: ";
      cin >> input;
      if (input < 0) {
        cout << "\nQuantity cannot be negative\n";
        this->editInventory(index);
      } else {
        this->array[index]->setQuantity(input);
        cout << "\nChanged quantity to " << input << endl;
      }
    } else if (input == 3) {
      cout << "\nEnter new wholesale cost: ";
      cin >> input;
      if (input < 0) {
        cout << "\nWholesale cost cannot be negative\n";
        this->editInventory(index);
      } else {
        this->array[index]->setWholeSaleCost(input);
        cout << "\nWholesale cost changed to " << input << endl;
      }
    } else if (input == 4) {
      cout << "\nEnter to retail cost: ";
      cin >> input;
      this->array[index]->setRetailCost(input);
    } else {
      cout << "\nInvalid input\n";
      
    }
  }

  void testArray() {
    NotArrayList testArray;
    testArray.createInv(1, 25, 30, 60);
    if (testArray.array[0]->getId() == 1 &&
        testArray.array[0]->getQuantity() == 25 &&
        testArray.array[0]->getWholeSaleCost() == 30 &&
        testArray.array[0]->getRetailCost() == 60) {
      cout << "Testing array inialization...... Passed\n";
    } else {
      cout << "Testing array inialization...... Failed\n";
    }

    testArray.deleteInv();

    if (testArray.getSize() == 0) {
      cout << "Testing deleting element from array...... Passed\n";
    } else {
      cout << "Testing deleting element from array...... Failed\n";
    }
  }

  int getSize() { return size; }
};

char alphaMenu();
void ProgramGreeting();
void UnitTest();


ostream &operator<<(ostream &osObject, const NotArrayList &list) {
  for (int i = 0; i < list.size; i++) {
    osObject << "\nItem: " << i + 1;
    list.array[i]->getInformation();
  }
  return osObject;
}


istream &operator>>(istream &in, Inventory &inv) {

  cout << "\nEnter Id: ";
  in >> inv.itemId;
  cout << "\nEnter quantity: ";
  in >> inv.quantity;
  cout << "\nEnter wholesale cost: ";
  in >> inv.wholeSaleCost;
  cout << "\nEnter retail cost: ";
  in >> inv.retailCost;

  return in;
}
int main() {
  
  UnitTest();
  ProgramGreeting();
  NotArrayList inv;

  bool running = true;

  while (running) {
    char input;
    input = alphaMenu();

    char input2 = toupper(input);

    if (input2 == 'A') {
      inv.createInv();
      cout << "\nCreated new inventory at index: " << inv.getSize() - 1 << endl;
    } else if (input2 == 'D') {
      if (inv.getSize() > 0) {
        inv.deleteInv();
        cout << "\nDeleted inventory at index : " << inv.getSize() << endl;
      } else {
        cout << "\nInventory is empty";
      }

    } else if (input2 == 'E') {
      int index;
      cout << "\nEnter index: ";
      cin >> index;
      if (index >= 0 && index < inv.getSize()) {
        inv.editInventory(index);
        cout << endl;
      } else {
        cout << "\nOut of bounds";
      }
    } else if (input2 == 'S') {
      cout << inv;
    } else if (input2 == 'Q') {
      running = false;
      cout << "\nGoodbye...\n";
    } else {
      cout << "\nError";
    }
  }

  return 0;
}


char alphaMenu() {
  char input;
  cout << "\n\nMain menu\n";
  cout << "<A>dd Inventory\n";
  cout << "<D>elete Inventory\n";
  cout << "<E>dit Inventory\n";
  cout << "<S>how Inventory\n";
  cout << "<Q>uit program\n>>> ";

  
  while (true) {

    cin >> input;

    if (cin.get() != '\n') {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "\nOnly input one character: ";
    } else
      break;
  }
  while (toupper(input) != 'A' && toupper(input) != 'D' &&
         toupper(input) != 'E' && toupper(input) != 'S' &&
         toupper(input) != 'Q') {

    cout << "\nEnter a valid menu option: ";
    while (true) {

      cin >> input;

      if (cin.get() != '\n') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nOnly input one character: ";
      } else
        break;
    }
  }

  return input;
}

void ProgramGreeting() {
  cout << "\nThis program creates a list of inventory items for which the user "
          "can edit, add, or delete items\nCody Hopkins\n10-16-2022\n";
}


void UnitTest() {
  Date testDate;
  Inventory testInv;
  NotArrayList testList;
  testDate.testDate();
  testInv.testInventory();
  testList.testArray();
}
