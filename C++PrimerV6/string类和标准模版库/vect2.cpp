#include<iostream>
#include<string>
#include<vector>

struct Review
{
    std::string title;
    int rating;
};

bool FillReview(Review &rr);
void ShowReview(const Review &rr);

int main()
{
    using std::cout;
    using std::vector;
    vector<Review> books;
    Review temp;
    while(FillReview(temp))
    {
        books.push_back(temp);
    }
    int num = books.size();
    if(num > 0)
    {
        cout << "Thank you, you entered the following :\n"
        << "Rating\tbook\t";
        for(int i = 0; i < num; i++)
        {
            ShowReview(books[i]);
        }
        cout << "Reprising rating book\n";
        vector<Review>::iterator pr;
        for(pr = books.begin(); pr != books.end(); pr++)
        {
            ShowReview(*pr);
        }
        vector<Review> oldlist(books);
        if(num > 3)
        {
            book.erase(books.begin()+1, books.end()+3);
        }
        cout << "After erase\n";
        for(pr = books.begin(); pr != books.end();pr++)
        {
            ShowReview(*pr);
        }

        books.insert(books.begin(),oldlist.begin()+1,oldlist.end()+2);

        cout << "After insertions\n";
        for(pr = books.begin(); pr != books.end(); pr++)
        {
            ShowReview(*pr);
        }

        books.swap(oldlist);
        cout << "Swap oldlist with books\n";
        for(pr = books.begin(); pr != books.end(); pr++)
        {
            ShowReview(*pr);
        }
    }
    else
    {
        cout << "Nothing Entered, nothing gained\n";
    }
    return 0;
}

bool FillReview(Review &rr)
{
    std::cout <<"ENter book title(quit to quit)\n";
    std::getline(std::cin,rr.title);
    if(rr.title == "quit")
    {
        return false;
    }
    std::cout << "Enter book rating:\n";
    std::cin >> rr.rating;
    if(!std::cin)
    {
        return false;
    }

    while(std::cin.get() != '\n')
    {
        continue;
    }
    return true;
}

void ShowReview(const Review &rr)
{
    std::cout << rr.rating << "\t " << rr.title << "\n";
}
