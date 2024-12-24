#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QStyledItemDelegate>
#include <QIcon>

class MyDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit MyDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // MYDELEGATE_H
