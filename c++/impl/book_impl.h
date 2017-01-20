/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: book_impl.h
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/01/20 16时15分20秒
 *
 **/

#include <string>

class BookImpl {
public:
    BookImpl(std::string name, std::string author, unsigned int price);
    ~BookImpl();

    void Print();

    std::string name_;
    std::string author_;
    unsigned int price_;
};
