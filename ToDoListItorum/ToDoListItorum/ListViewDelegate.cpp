#include "ListViewDelegate.h"
#include "ListViewDelegatePrivate.h"
#include <QPainter>

ListViewDelegate::ListViewDelegate(QObject* parent) : QStyledItemDelegate(parent), modelPrivate(new ListViewDelegatePrivate)
{

}

ListViewDelegate::~ListViewDelegate()
{
	delete modelPrivate;
}

QMargins ListViewDelegate::contentsMargins() const
{
	return modelPrivate->margins;
}

void ListViewDelegate::setContentsMargins(int left, int top, int right, int bottom)
{
	modelPrivate->margins = QMargins(left, top, right, bottom);
}

int ListViewDelegate::horizontalSpacing() const
{
	return modelPrivate->spacingHorizontal;
}

void ListViewDelegate::setHorizontalSpacing(int spacing)
{
	modelPrivate->spacingHorizontal = spacing;
}

int ListViewDelegate::verticalSpacing() const
{
	return modelPrivate->spacingVertical;
}

void ListViewDelegate::setVerticalSpacing(int spacing)
{
	modelPrivate->spacingVertical = spacing;
}

void ListViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem opt(option);
	initStyleOption(&opt, index);
	const QPalette& palette(opt.palette);
	
	const QRect&	rect(opt.rect);
	const QRect&	contentRect(rect.adjusted(modelPrivate->margins.left(), modelPrivate->margins.top(), modelPrivate->margins.right(), modelPrivate->margins.bottom()));

	const bool lastIndex = (index.model()->rowCount() - 1) == index.row();
	const bool firstIndex = (index.row()) == 0;
	const int bottomEdge = rect.bottom();
	
	QFont font(opt.font);

	font.setPixelSize(modelPrivate->timestampFontPointSize(opt.font));

	painter->save();
	painter->setClipping(true);
	painter->setClipRect(rect);
	painter->setFont(opt.font);

	int borderRadiusX = 24; // Радиус по горизонтали
	int borderRadiusY = 24; // Радиус по вертикали
	

	// Отрисовка элемента TaskListView в виде прямоугольника с округленными краями
	if (firstIndex)
	{
		

		if (lastIndex)
		{
			QRect upperPart = rect.adjusted(rect.left() + 1, rect.top() + 1, -rect.left() - 1, -rect.top());
			painter->setPen(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->setBrush(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->drawRoundedRect(upperPart, borderRadiusX, borderRadiusY);
		}
		else
		{
			QRect upperPart = rect.adjusted(rect.left() + 1, rect.top() + 1, -rect.left() - 1, rect.bottom());
			painter->setPen(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->setBrush(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->drawRoundedRect(upperPart, borderRadiusX, borderRadiusY);
		}
	 
	}
	else
	{
		if (lastIndex)
		{
			QRect upperPart = rect.adjusted(rect.left() + 1,  -rect.bottom(), -rect.left() - 1, -1);
			painter->setPen(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->setBrush(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->drawRoundedRect(upperPart, borderRadiusX, borderRadiusY);
		}
		else
		{
			QRect upperPart = rect.adjusted(rect.left() + 1, rect.top() + 1, -rect.left() - 1, -rect.top());
			painter->setPen(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			painter->setBrush(opt.state & QStyle::State_Selected ? palette.highlight().color() : palette.light().color());
			//painter->fillRect(upperPart, opt.state & QStyle::State_Selected ? Qt::white : Qt::white);
			painter->drawRect(upperPart);
		}
		
	}
	
	QRect messageRect(modelPrivate->messageBox(opt));
	messageRect.moveTo(modelPrivate->margins.left() + modelPrivate->spacingHorizontal, contentRect.top());
	
	painter->setFont(opt.font);
	painter->setPen(palette.windowText().color());
	painter->drawText(messageRect, Qt::TextSingleLine, opt.text);

	QRect timeStampRect(modelPrivate->timestampBox(opt, index));

	timeStampRect.moveTo(messageRect.left(), messageRect.bottom() + modelPrivate->spacingHorizontal);

	painter->setFont(font);
	painter->setPen(palette.text().color());
	painter->drawText(timeStampRect, Qt::TextSingleLine, index.data(Qt::UserRole).toString());

	painter->restore();


}

QSize ListViewDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QStyleOptionViewItem opt(option);
	initStyleOption(&opt, index);

	int textHeight = modelPrivate->timestampBox(opt, index).height() + modelPrivate->spacingVertical + modelPrivate->messageBox(opt).height();
	int height = 40;
	int h = textHeight > height ? textHeight : height;
	return QSize(opt.rect.width(), modelPrivate->margins.top() + h + modelPrivate->margins.bottom());
}

ListViewDelegatePrivate::ListViewDelegatePrivate() : margins(0, 0, 0, 0), spacingHorizontal(0), spacingVertical(0)
{

}

QRect ListViewDelegatePrivate::timestampBox(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QFont font(option.font);

	font.setPointSizeF(timestampFontPointSize(option.font));
	return QFontMetrics(font).boundingRect(index.data(Qt::UserRole).toString()).adjusted(0, 0, 1, 1);
}

qreal ListViewDelegatePrivate::timestampFontPointSize(const QFont& font) const
{
	return 0.85 * font.pointSize();
}

QRect ListViewDelegatePrivate::messageBox(const QStyleOptionViewItem& option) const
{
	return option.fontMetrics.boundingRect(option.text).adjusted(0, 0, 1, 1);
}