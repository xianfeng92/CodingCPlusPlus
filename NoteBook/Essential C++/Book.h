#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_

class Book : public LibMat{
public:
  Book(const std::string &title, const std::string &author) : title_(title), author_(author) {
      cout << "Book::book" <<"title: "<< title << "author: " << author << endl;
  }

  virtual ~Book(){
      cout << "Book::~book() destructor" << endl;
  }

  virtual void print() const {
      cout << "Book::print()--I am book object " << "my title: " << title << endl;
      cout << "my author: " << author << endl;
  }

  const string &title() const { return title_; }
  const string &author() const { return author_; }

protected:
  string title_;
  string author_;
};

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_BOOK_H_
