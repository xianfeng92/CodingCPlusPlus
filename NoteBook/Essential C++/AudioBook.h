#ifndef NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_
#define NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_

class AudioBook : public Book{
public:
  AudioBook(const string &name, const string &title, const string &narrator) : Book(name, title), narrator_(narrator){
      cout << "AudioBook::AudioBook()" << endl;
  }

  ~AudioBook(){
      cout << "AudioBook::~AudioBook()" << endl;
  }

  virtual void print() const {
      cout << "AudioBook::print()" << endl;
      cout << "my title = " << title << endl;
      cout << "my author = " << author << endl;
      cout << "my narrator = " << narrator << end;
  }

  const string &narrator() const { return narrator_; }
protected:
  string narrator_;
};

#endif // NOTEBOOK_ESSENTIAL_20C_2B_2B_AUDIOBOOK_H_
