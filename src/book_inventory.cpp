#include "book_inventory.h"

double book::get_receipt(Books shopinglist) {
  double total_price{};

  std::cout << std::string(60, '*') << std::endl;
  std::cout << "|" << std::string(11, ' ') << "title" << std::string(12, ' ')
            << "|" << std::string(5, ' ') << "isbn" << std::string(5, ' ')
            << "|" << std::string(5, ' ') << "price" << std::string(4, ' ')
            << "|" << std::endl;
  std::cout << "|" << std::string(58, '-') << "|" << std::endl;
  for (auto books : shopinglist) {
    if (books.title.length() > 20) {
      std::cout << "|" << std::string(4, ' ') << books.title.substr(0, 17)
                << "..." << std::string(4, ' ') << "|" << std::string(3, ' ')
                << std::left << std::setw(8) << books.isbn.substr(0, 8)
                << std::string(3, ' ') << "|" << std::string(3, ' ')
                << std::setfill('0') << std::left << std::setw(7) << books.cost
                << "$" << std::string(3, ' ') << "|" << std::setfill(' ')
                << std::endl;
    } else {
      std::cout << "|" << std::string(4, ' ') << std::left << std::setw(20)
                << books.title << std::string(4, ' ') << "|"
                << std::string(3, ' ') << std::left << std::setw(8)
                << books.isbn.substr(0, 8) << std::string(3, ' ') << "|"
                << std::string(3, ' ') << std::setfill('0') << std::left
                << std::setw(7) << books.cost << "$" << std::string(3, ' ')
                << "|" << std::setfill(' ') << std::endl;
    }
    total_price += books.cost;
  }
  std::cout << "|" << std::string(58, '-') << "|" << std::endl;
  std::cout << "|" << std::string(30, ' ') << "Total Price  |"
            << std::string(3, ' ') << std::setfill('0') << std::left
            << std::setw(7) << total_price << "$" << std::string(3, ' ') << "|"
            << std::setfill(' ') << std::endl;
  std::cout << std::string(60, '*') << std::endl;

  return total_price;
}

bool book::order(Books &inventory, Books &shopinglist, std::string isbn) {
  std::string none{"none"};
  if (isbn == none)
    return false;
  for (auto &books : inventory) {
    if (books.isbn == isbn) {
      shopinglist.push_back(books);
      books.count--;

      return true;
    }
  }
  return false;
}

std::string book::search(Books &inventory, std::string title) {
  for (auto books : inventory) {
    if (books.title == title) {
      return books.isbn;
    }
  }
  return "none";
}

Books book::read_database(std::string filepath) {
  std::ifstream csvFile(filepath);

  Books exp_book;

  if (!csvFile)
    throw std::runtime_error("your path is NOT valid");

  else {
    std::string line;
    while (std::getline(csvFile, line)) {
      Book line_book;
      std::stringstream str(line);
      std::vector<std::string> arguments{};
      std::string separated{};
      while (std::getline(str, separated, ',')) {
        arguments.push_back(separated);
      }
      line_book.title = arguments[1];
      line_book.author = arguments[2];
      line_book.cost = std::stof(arguments[3]);
      line_book.isbn = arguments[4];
      line_book.language_code = arguments[5];
      line_book.num_pages = std::stoi(arguments[6]);
      line_book.publisher = arguments[7];
      line_book.count = std::stoi(arguments[8]);

      exp_book.push_back(line_book);
    }
  }
  return exp_book;
}
