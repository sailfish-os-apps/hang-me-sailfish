
#include "rostermodel.h"

RosterModel::RosterModel (QObject * parent) : QAbstractListModel (parent) {
}

QHash<int, QByteArray> RosterModel::roleNames () const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames ();
    roles.insert (ConvIdRole, QByteArrayLiteral ("id"));
    roles.insert (NameRole, QByteArrayLiteral ("name"));
    roles.insert (PartnumRole, QByteArrayLiteral ("particpantsNum"));
    roles.insert (UnreadRole, QByteArrayLiteral ("unread"));
    roles.insert (ImageRole, QByteArrayLiteral ("imagePath"));
    return roles;
}

int RosterModel::rowCount (const QModelIndex & parent) const {
    Q_UNUSED (parent);
    return conversations.size ();
}

QVariant RosterModel::data (const QModelIndex & index, int role) const {
    QVariant ret;
    if (index.row () >= 0 && index.row () < conversations.size ()) {
        // NOTE : Reverse the order so that the most recent conv is displayed on top
        ConvAbstract * conv = conversations.at (conversations.size () - index.row () -1);
        switch (role) {
            case NameRole:
                ret = QVariant::fromValue (conv->name);
                break;
            case PartnumRole:
                ret = QVariant::fromValue (conv->participantsNum);
                break;
            case ConvIdRole:
                ret = QVariant::fromValue (conv->convId);
                break;
            case UnreadRole:
                ret = QVariant::fromValue (conv->unread);
                break;
            case ImageRole:
                // TODO : once we should support multiple images
                ret = QVariant::fromValue (!conv->imagePaths.isEmpty () ? conv->imagePaths.first () : "");
                break;
            default:
                break;
        }
    }
    return ret;
}

void RosterModel::setMySelf (User pmyself) {
    myself = pmyself;
}

void RosterModel::addConversationAbstract (Conversation pConv) {
    QString name = "";
    QStringList imagePaths;
    if (pConv.name.size () > 1) {
        name = pConv.name;
    }
    else {
        foreach (Participant p, pConv.participants) {
            if (p.user.chat_id != myself.chat_id) {
                if (pConv.participants.last ().user.chat_id != p.user.chat_id && pConv.participants.last ().user.chat_id != myself.chat_id)  {
                    name += QString (p.user.display_name + ", ");
                }
                else {
                    name += QString (p.user.display_name + " ");
                }
                if (!p.user.photo.isEmpty ()) {
                    QString image = p.user.photo;
                    if (!image.startsWith ("https:")) {
                        image.prepend ("https:");
                    }
                    imagePaths << image;
                }
            }
        }
    }
    beginInsertRows (QModelIndex (), rowCount (), rowCount ());
    conversations.append (new ConvAbstract (pConv.id, name, imagePaths, pConv.participants.size (), pConv.unread));
    endInsertRows ();
}

bool RosterModel::conversationExists (QString convId) {
    bool ret = false;
    foreach (ConvAbstract * conv, conversations) {
        if (conv->convId == convId) {
            ret = true;
            break;
        }
    }
    return ret;
}

void RosterModel::addUnreadMsg (QString convId) {
    qDebug () << "adding unread msg " << convId;
    int i = 0;
    foreach (ConvAbstract * conv, conversations) {
        if (conv->convId == convId) {
            conv->unread += 1;
            QModelIndex entry = index (conversations.size () - i -1);
            emit dataChanged (entry, entry, QVector<int> () << UnreadRole);
            break;
        }
        i++;
    }
}

bool RosterModel::hasUnreadMessages (QString convId) {
    bool ret = false;
    foreach (ConvAbstract * conv, conversations) {
        if (conv->convId == convId) {
            ret = (conv->unread > 0);
            break;
        }
    }
    return ret;
}

void RosterModel::setReadConv (QString convId) {
    qDebug () << "Setting as read " << convId;
    int i = 0;
    foreach (ConvAbstract * conv, conversations) {
        if (conv->convId == convId) {
            conv->unread = 0;
            QModelIndex entry = index (conversations.size () - i -1);
            emit dataChanged (entry, entry, QVector<int> () << UnreadRole);
            break;
        }
        i++;
    }
}

QString RosterModel::getConversationName (QString convId) {
    QString ret;
    foreach (ConvAbstract * conv, conversations) {
        if (conv->convId==convId) {
            ret = conv->name;
            break;
        }
    }
    return ret;
}
