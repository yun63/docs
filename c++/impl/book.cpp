/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: book.cpp
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/01/20 16时12分31秒
 *
 **/


#include "book.h"
#include "book_impl.h"

Book::Book() : book_impl_(new BookImpl("none", "none", 0)) {
}

Book::Book(std::string name, std::string author, unsigned int price)
: book_impl_(new BookImpl(name, author, price)) {
}

Book::Book(const Book &other) : book_impl_(new BookImpl(other.book_impl_->name_,other.book_impl_->author_, other.book_impl_->price_)) {

}

Book &Book::operator= (const Book &other) {
    book_impl_->name_ = other.book_impl_->name_;
    book_impl_->author_ = other.book_impl_->author_;
    book_impl_->price_ = other.book_impl_->price_;

    return *this;
}

void Book::PrintInfo() {
    book_impl_->Print();
}

