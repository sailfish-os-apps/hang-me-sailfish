#ifndef CONTACTSMODEL_H
#define CONTACTSMODEL_H

#include <QAbstractListModel>
#include "qtimports.h"
#include "structs.h"

class ContactsModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit ContactsModel (QObject * parent = NULL);

    int rowCount (const QModelIndex & parent = QModelIndex ()) const;
    QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
    void addContact (User pContact);

    Q_INVOKABLE QString getContactFName (QString cid);
    Q_INVOKABLE QString getContactDName (QString cid);

private:
    QList<User> contacts;
    User myself;
};

#endif // CONTACTSMODEL_H
