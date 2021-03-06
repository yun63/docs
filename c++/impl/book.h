/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: book.h
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/01/20 16时10分51秒
 *
 **/

#include <string>
#include <memory>

class BookImpl;

class Book {
public:
    Book();
    Book(std::string name, std::string author, unsigned int price);
    Book(const Book &other);
    Book &operator =(const Book &other);
    void PrintInfo();

private:
    std::shared_ptr<BookImpl> book_impl_;
};
