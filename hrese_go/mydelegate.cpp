#include "MyDelegate.h"
#include <QPainter>
#include <QStyleOptionViewItem>

MyDelegate::MyDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //调用基类的paint方法来绘制单元格的背景和边框
    QStyledItemDelegate::paint(painter, option, index);
    //获取单元格中的图标和文本
    QIcon icon = qvariant_cast<QIcon>(index.data(Qt::UserRole + 1));
    QString text = index.model()->data(index, Qt::DisplayRole).toString();
    //根据单元格大小调整图标尺寸
    QPixmap pixmap = icon.pixmap(option.rect.size());
    //计算图标和文本的绘制位置
    QRect iconRect(option.rect);
    QRect textRect(option.rect.adjusted(pixmap.width() + 4, 0, 0, 0));
    //绘制图标
    painter->drawPixmap(iconRect.topLeft(), pixmap);
    //绘制文本
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
}
