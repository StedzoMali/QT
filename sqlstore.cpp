#include "sqlstore.h"

namespace SqlStore::Support {

QString get(const QString &key) {
    if (key == "PODATOCITE_OD_TABELATA")//gji dobivame site books
        return "SELECT book_id,title, author FROM books ORDER BY book_id ASC";
    if (key == "GET_ALL_BOOKS_BY_PUBLISHED_YEAR")//site books after 2000 god
        return "SELECT book_id,title, author, genre FROM books WHERE published_year >= 2000 ORDER BY book_id ASC";

    return ""; // ako kljuchot ne proistoi
    }
}


