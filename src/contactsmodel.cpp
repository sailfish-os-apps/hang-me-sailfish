
#include "contactsmodel.h"

ContactsModel::ContactsModel (QObject * parent) : QAbstractListModel (parent) { }

void ContactsModel::addContact (User pContact) {
    contacts.append (pContact);
}

QString ContactsModel::getContactFName (QString cid) {
    QString ret ("Unknown");
    foreach (User u, contacts) {
        if (u.chat_id == cid) {
            ret = u.first_name;
            break;
        }
    }
    return ret;
}

QString ContactsModel::getContactDName (QString cid) {
    QString ret (cid);
    foreach (User u, contacts) {
        if (u.chat_id == cid) {
            ret = u.display_name;
            break;
        }
    }
    return ret;
}

int ContactsModel::rowCount (const QModelIndex & parent) const {
    Q_UNUSED (parent);
    return contacts.size ();
}

QVariant ContactsModel::data (const QModelIndex & index, int role) const {
    QVariant ret;
    Q_UNUSED (index);
    Q_UNUSED (role);
    return ret;
}
