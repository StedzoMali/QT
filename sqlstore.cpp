#include "sqlstore.h"

namespace SqlStore {

namespace Support {

QString get(const QString &key) {
    if (key == "PODATOCITE_OD_TABELATA")//gji dobivame site books
        return "SELECT id,title, author FROM books ORDER BY id DESC";
    if (key == "GET_ALL_BOOKS_BY_PUBLISHED_YEAR")//site books after 2000 god
        return "SELECT id, title, author, genre FROM books WHERE published_year >= 2000 ORDER BY id ASC";

    return ""; // ako kljuchot ne proistoi
}

}

}
