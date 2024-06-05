#pragma once
#include <QStyledItemDelegate>

class ListViewDelegatePrivate;

class ListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ListViewDelegate(QObject* parent = nullptr);
	~ListViewDelegate();

	QMargins contentsMargins() const;
	void setContentsMargins(int left, int top, int right, int bottom);

	int horizontalSpacing() const;
	void setHorizontalSpacing(int spacing);

	int verticalSpacing() const;
	void setVerticalSpacing(int spacing);

	void paint(QPainter* painter, const QStyleOptionViewItem& option,
			   const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option,
				   const QModelIndex& index) const override;

private:
	ListViewDelegatePrivate* modelPrivate;
};