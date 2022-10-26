#ifndef bookh
#define bookh

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Book {
  std::string title;         // title of the book
  std::string author;        // author of the book
  float cost;                // cost of the book
  std::string isbn;          // a unique string assigned to each book
  std::string language_code; // language of the book
  int num_pages;             // number of pages
  std::string publisher;     // publisher of the book
  int count;                 // how many books left in the inventory
};

using Books = std::vector<Book>;

namespace book {
Books read_database(std::string filepath);
std::string search(Books &inventory, std::string title);
bool order(Books &inventory, Books &shopinglist, std::string isbn);
double get_receipt(Books shopinglist);
} // namespace book

#endif