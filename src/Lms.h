/**
 * @file Lms.h
 * @author Zhang Hai
 */

#ifndef _LMS_H_
#define _LMS_H_


#include "Library/Common.h"

#include "Book.h"
#include "BookFilters.h"
#include "BookList.h"


BookList *Lms_deserializeOrCreateBookList(string filename);

bool Lms_serializeBookList(BookList *list, string filename);

void Lms_searchBook(BookList *list);

void Lms_addBook(BookList *list);

void Lms_modifyBook(BookList *list);

void Lms_removeBook(BookList *list);

void Lms_loop();


#endif /* _LMS_H_ */
