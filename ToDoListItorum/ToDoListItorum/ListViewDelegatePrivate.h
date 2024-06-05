#pragma once
#include <qglobal.h>

class ListViewDelegatePrivate
{
public:
	ListViewDelegatePrivate();
	inline QRect timestampBox(const QStyleOptionViewItem& option,
							  const QModelIndex& index) const;
	inline qreal timestampFontPointSize(const QFont& f) const;
	inline QRect messageBox(const QStyleOptionViewItem& option) const;

	//QSize iconSize;
	QMargins margins;
	int spacingHorizontal;
	int spacingVertical;

	friend class ListViewDelegatePrivate;

};