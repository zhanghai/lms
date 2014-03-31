/*
 * File: Lms.h
 * Author: Zhang Hai
 */

#ifndef _LMS_H_
#define _LMS_H_


#include "Library/Common.h"

#include "Book.h"
#include "BookFilters.h"
#include "BookList.h"

void Lms_searchBook(BookList *list);

void Lms_deleteBook(BookList *list);


#endif /* _LMS_H_ */
