/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: book_test.cpp
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/01/20 16时37分55秒
 *
 **/


#include "book.h"

int main(int argc, const char *argv[])
{
    Book b("<<C++程序设计艺术>>", "Liu Xiaoxia", 100);
    b.PrintInfo();

    Book bb = b;
    bb.PrintInfo();

    Book bbb;
    bbb = b;
    bbb.PrintInfo();

    return 0;
}
