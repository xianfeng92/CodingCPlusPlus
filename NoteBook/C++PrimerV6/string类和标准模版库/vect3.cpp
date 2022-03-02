#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

struct Review
{
    std::string title;
    int rating;
};

bool operator<(const Review& r1, const Review& r1);
bool worseThan(const Review& r1, const Review& r2);
bool fillReview(Review& r);
void showReview(const Review& r);

int main()
{
    using namespace std;

    vector<Review> books;
    Review temp;
    while(fillReview(temp))
    {
        books.push_back(temp);
    }
    if(books.size() > 0)
    {
        cout << "Thank you, you entered the following :\n" << books.size()
        << "Rating\tbook\t";
        for_each(books.begin(), books.end(),showReview);

        sort(books.begin(), books.end());
        cout << "Sorted by title:\n";
        for_each(books.begin(), books.end(),showReview);

        sort(books.begin(), books.end(),worseThan);
        cout << "Sort by rating\n";
        for_each(books.begin(), books.end(),showReview);

        random_shuffle(books.begin(), books.end());
        cout << "After random_shuffle\n";
        for_each(books.begin(), books.end(),showReview);
    }
    else
    {
        cout << "No Entry\n";
    }
    return 0;
}


bool operator<(connst Review &r1, connst Review &r2)
{
    if(r1.title < r2.title)
    {
        return true;
    }
    else if(r1.title == r2.title && r1.rating < r2.rating)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool worseThan(const Review &r1, const Review &r2)
{
    if(r1.rating < r2.rating)
    {
        return true;
    }
    else
    {
        return false;
    }
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