/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: book_impl.cpp
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/01/20 16时16分50秒
 *
 **/


#include <iostream>
#include "book_impl.h"

BookImpl::BookImpl(std::string name, std::string author, unsigned int price)
: name_(name)
, author_(author)
, price_(price) {}

BookImpl::~BookImpl() {

}

void BookImpl::Print() {
    std::cout << "ISBN: " << this->name_ << "\tAuthor: " << this->author_ << "\tPrice: " << this->price_ << std::endl;
}
