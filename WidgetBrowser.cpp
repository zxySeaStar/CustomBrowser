﻿#include "WidgetBrowser.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QGuiApplication>
#include <QClipboard>
WidgetBrowser::WidgetBrowser(QWidget* parent)
	:QWidget(parent),
	_WidgetPort(new WidgetChoosePort(this)),
	_WidgetViewer(new WidgetViewer(this)),
	_TextEdit(new QTextEdit(this)),
	_BtnAppend(new QPushButton(this)),
	_BtnClear(new QPushButton(this)),
	_BtnCopy(new QPushButton(this))
{
	auto vLayout = new  QVBoxLayout(this);
	setLayout(vLayout);

	vLayout->addWidget(_WidgetPort);
	vLayout->addWidget(_WidgetViewer);

	{
		auto hLayout = new QHBoxLayout();
		auto vvLayout = new QVBoxLayout();
		hLayout->setSpacing(0);
		hLayout->setMargin(0);
		hLayout->addWidget(_TextEdit);
		vvLayout->addWidget(_BtnAppend); _BtnAppend->setText(u8"添加");
		vvLayout->addWidget(_BtnClear); _BtnClear->setText(u8"清空");
		vvLayout->addWidget(_BtnCopy); _BtnCopy->setText(u8"复制");
		vLayout->addLayout(hLayout);
		hLayout->addLayout(vvLayout);
	}
	InitUI();
}

void WidgetBrowser::InitUI()
{
	connect(_BtnAppend, &QPushButton::clicked, this, [this]() {
		QString content = _TextEdit->toPlainText();
		_WidgetViewer->AppendData(content);
	});
	connect(_BtnClear, &QPushButton::clicked, this, [this]() {
		_WidgetViewer->Clear();
	});
	connect(_BtnCopy, &QPushButton::clicked, this, [this]() {
		_WidgetViewer->Copy();
	});
	UpdateUI();
}

void WidgetBrowser::UpdateUI()
{
}

/*
class WidgetChoosePort
*/
WidgetChoosePort::WidgetChoosePort(QWidget* parent)
	:QWidget(parent),
	_Combobox(new QComboBox(this)),
	_BtnConnect(new QPushButton(this)),
	_BtnStop(new QPushButton(this)),
	_Frame(new QFrame(this))
{
	auto vLayout = new QVBoxLayout();
	setLayout(vLayout);
	vLayout->addWidget(_Frame);

	auto hLayout = new QHBoxLayout();
	_Frame->setLayout(hLayout);

	hLayout->setSpacing(0);
	hLayout->setMargin(0);
	hLayout->addWidget(_Combobox);
	hLayout->addWidget(_BtnConnect);
	hLayout->addWidget(_BtnStop);
	//⏯⏸
	//_BtnConnect->setText(u8"⏯");
	//_BtnStop->setText(u8"⏸");
	InitUI();
}

void WidgetChoosePort::InitUI()
{
	connect(_BtnConnect, &QPushButton::pressed, this, [this]() {
		TryConnect(true);
	});
	connect(_BtnStop, &QPushButton::pressed, this, [this]() {
		TryConnect(false);
	});

	_Combobox->addItem("COM122");
	_Combobox->addItem("COM123");
	_Combobox->addItem("COM124");

	QString btnStyle1 = "QPushButton{ background-color: qlineargradient(spread : 180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(187, 140, 253, 1), stop:1 rgba(115, 11, 230, 1)); "
		" color: white;"
		"font-size:14px;font-family:'Microsoft YaHei UI';"
		"border-color:qlineargradient(spread:180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(153, 99, 230, 1), stop:1 rgba(82, 12, 159, 1));"
		"border-radius: 0px; border-width: 1px;width:50px;height:30px;border-style:solid;}"
		"QPushButton:hover{background-color: qlineargradient(spread:180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(187, 140, 253, 0.8), stop:1 rgba(115, 11, 230, 0.8));}"
		"QPushButton:pressed{background-color: rgba(124,27,233,1);}"
		"QPushButton:disabled{background-color:grey; color:rgba(200,200,200,1);border-color:rgba(200,200,200,1);border-width:1px;border-style:solid}"
		"QPushButton:checked{background-color: rgba(131,133,140,1); color:rgba(255,255,255,1);border-color:rgba(200,200,200,1);border-width:1px;border-style:solid}";

	QString btnStyle2 = "QPushButton{ background-color: qlineargradient(spread : 180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(187, 140, 253, 1), stop:1 rgba(115, 11, 230, 1)); "
		" color: white;"
		"font-size:14px;font-family:'Microsoft YaHei UI';"
		"border-color:qlineargradient(spread:180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(153, 99, 230, 1), stop:1 rgba(82, 12, 159, 1));"
		"border-radius:0px; border-top-right-radius:15px;border-bottom-right-radius:15px; border-width: 1px;width:50px;height:30px;border-style:solid;}"
		"QPushButton:hover{background-color: qlineargradient(spread:180deg, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(187, 140, 253, 0.8), stop:1 rgba(115, 11, 230, 0.8));}"
		"QPushButton:pressed{background-color: rgba(124,27,233,1);}"
		"QPushButton:disabled{background-color: grey; color:rgba(200,200,200,1);border-color:rgba(200,200,200,1);border-width:1px;border-style:solid}"
		"QPushButton:checked{background-color: rgba(131,133,140,1); color:rgba(255,255,255,1);border-color:rgba(200,200,200,1);border-width:1px;border-style:solid}";

	QString comboboxStyle = "QComboBox::drop-down{border-width:0px;}"\
		"QComboBox{ border-width:1px; border-style:solid;border-radius:0px;border-top-left-radius:15px;border-bottom-left-radius:15px; font-size:13px; font-style: 'Microsoft YaHei UI';color:rgba(0,0,0,0.6);padding:6px;outline: none}"\
		"QComboBox::down-arrow{ border-width:0px; background-color:transparent; image: url(:/Button/Resources/Button/Arrow_Down.png); width: 13px; height: 13px; }"
		"QComboBox QAbstractItemView{ background-color: rgba(255,255,255,0);margin:1px; padding: 3px 0px 3px 0px; border: 0px solid transparent; border-radius:3px;}"\
		"QComboBox QAbstractItemView::item{ padding: 3px 50px 3px 25px; border: 0px solid transparent;}"\
		"QComboBox QAbstractItemView::item:selected{background-color: rgba(255,255,255,1);color:white;}";


	// stylesheet
	//_Frame->setStyleSheet(".QFrame{background-color:purple;border-radius:10px;};");
	_BtnConnect->setStyleSheet(btnStyle1);
	_BtnConnect->setIcon(QIcon(":/Button/Resources/Button/play.png"));
	_BtnStop->setStyleSheet(btnStyle2);
	_BtnStop->setIcon(QIcon(":/Button/Resources/Button/pause.png"));
	_Combobox->setStyleSheet(comboboxStyle);
	UpdateUI();
}

void WidgetChoosePort::UpdateUI()
{
	_BtnConnect->setDisabled(_IsConnected);
	_BtnStop->setDisabled(!_IsConnected);
}

void WidgetChoosePort::TryConnect(bool flags)
{
	_IsConnected = flags;
	UpdateUI();
}


/*
class WidgetViewer
*/
WidgetViewer::WidgetViewer(QWidget* parent)
	:QAbstractScrollArea(parent)
{
	setMouseTracking(true);
	connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjust()));

	_Format.setFamily("monoSpace");
	_Format.setPixelSize(_CharH);
	_Format.setLetterSpacing(QFont::AbsoluteSpacing, 0);
	
	QFontMetrics fm(_Format, viewport());
	_CharW = fm.boundingRect("9").width();

	AppendData("1");
	AppendData("12");
	AppendData("134");
	AppendData("12345");
	AppendData("1424325");
	AppendData("124234");
	AppendData("1234");
	AppendData("123");
}

void WidgetViewer::AppendData(QString _text)
{
	//setUpdatesEnabled(false);

	// parse the text
	// current format
	// 1.  
	// 2.

	_ContentList.append(_text);
	adjust();
	////verticalScrollBar()->setRange(0, _CharH * (LineCount() + 1) - viewport()->size().height() + 6);
	//verticalScrollBar()->setRange(0, _ContentList.size()-((viewport()->height() - _ColPrefix) / _CharH));
	//verticalScrollBar()->setValue(verticalScrollBar()->maximum());
	//setUpdatesEnabled(true);
	//this->viewport()->update();
}

void WidgetViewer::Clear()
{
	_ContentList.clear();
	//this->viewport()->update();
	adjust();
}

QString WidgetViewer::Copy()
{
	// copy the selected text to the clip board
	QClipboard* clipboard = QGuiApplication::clipboard();
	QString originalText = clipboard->text();
	// etc.

	// get the selected text
	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };

	QString result;
	if (_ContentList.size() == 0)
	{
		return QString();
	}
	//// for the first line
	//if (_SelectPBegin.y() != _SelectPEnd.y())
	//{
	//	// line
	//	for (int l = _SelectPBegin.y() ; l < _SelectPEnd.y() && l < _ContentList.size(); l++)
	//	{
	//		result.append(_ContentList.at(l));
	//	}

	//	// last line
	//	if (_SelectPEnd.y() < _ContentList.size())
	//	{
	//		result.append(_ContentList.at(_SelectPEnd.y()).mid(0,_SelectPEnd.x()));
	//	}
	//}
	//else
	//{
	//	if (_SelectPEnd.y() < _ContentList.size())
	//	{
	//		result.append(_ContentList.at(_SelectPEnd.y()).mid(_SelectPBegin.x(), _SelectPEnd.x()- _SelectPBegin.x()));
	//	}
	//}
	QFontMetrics fm(_Format, viewport());
	for (int absl = _SelectPBegin.y(); absl <= _SelectPEnd.y() && absl < _ContentList.size(); absl++)
	{
		if (absl > _SelectPBegin.y() && absl < _SelectPEnd.y())
		{
			result.append(_ContentList.at(absl));
		}
		else
		{
			int textLineWidth = fm.boundingRect(_ContentList.at(absl)).width();
			int lpos = 0;
			int rpos = textLineWidth;
			if (absl == _SelectPBegin.y())
			{
				lpos = f_min((_SelectPBegin.x()) * _CharW, textLineWidth);
			}
			if (absl == _SelectPEnd.y())
			{
				rpos = f_min((_SelectPEnd.x()) * _CharW, textLineWidth);
			}
			// for the first line andd last line, handle char one by one
			// tranverse the line, find the hightlight left pos, and right pos
			//for (auto& item : _ContentList.at(absl))
			//{
			//	int charWidth = fm.boundingRect(item).width();	
			//}
			int hlIndex = 0;
			int hrIndex = _ContentList.at(absl).size()-1;
			for (int i = 0; i < _ContentList.at(absl).size(); i++)
			{
				int charWidth = fm.boundingRect(_ContentList.at(absl).mid(i)).width();
				if (textLineWidth - charWidth > lpos)
				{
					break;
				}
				hlIndex = i;
			}
			for (int i = _ContentList.at(absl).size(); i > 0; i--)
			{
				int charWidth = fm.boundingRect(_ContentList.at(absl).mid(0, i)).width();
				if (charWidth < rpos)
				{
					break;
				}
				hrIndex = i;
			}
			result.append(_ContentList.at(absl).mid(hlIndex, hrIndex-hlIndex));
		}
		result.append("\n");
	}

	clipboard->setText(result);
	return QString();
}

void WidgetViewer::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event)
	//verticalScrollBar()->setPageStep(_CharH * 10);
	//verticalScrollBar()->setPageStep(((viewport()->height() - _ColPrefix) / _CharH));
	//verticalScrollBar()->setSingleStep(_CharH);
	//verticalScrollBar()->setRange(0, _ContentList.size() - ((viewport()->height() - _ColPrefix) / _CharH));

	//verticalScrollBar()->setRange(0, _CharH * (LineCount() + 1) - viewport()->size().height() + _ColPrefix);
	adjust();
}

void WidgetViewer::mousePressEvent(QMouseEvent* _event)
{
	_Pressed = true;
	// record cur postion and last position
	if (_event->button() == Qt::LeftButton)
	{
		//auto pos = _event->pos() + QPoint(0,verticalScrollBar()->value());
		//_LastCursorPos = pos;
		//_CurCursorPos = pos;
		//this->viewport()->update();
		auto pos = CursorPosition(_event->pos());
		ResetSelection(pos);
		SetSelection(pos);
		this->viewport()->update();
	}
}

void WidgetViewer::mouseReleaseEvent(QMouseEvent* _event)
{
	_Pressed = false;
	// update last 
	if (_event->button() == Qt::LeftButton)
	{
		//auto pos = _event->pos() + QPoint(0, verticalScrollBar()->value());
		//_CurCursorPos = pos;
		//this->viewport()->update();
		//CursorPosition(_event->pos());
		//this->viewport()->update();
	}
}

void WidgetViewer::mouseMoveEvent(QMouseEvent* _event)
{
	if (_Pressed)
	{
		//auto pos = _event->pos() + QPoint(0, verticalScrollBar()->value());
		//_CurCursorPos = pos;
		//this->viewport()->update();
		auto pos = CursorPosition(_event->pos());
		if (pos.x() >= 0 && pos.y() >= 0)
		{
			SetSelection(pos);
		}
		this->viewport()->update();
	}
}

void WidgetViewer::adjust() {
	// adjust the scrollbar value
	// total number of line show
	_RowShowNum = (viewport()->height() - _RowPrefix )/ _CharH ;
	int lineCount = _ContentList.size();
	verticalScrollBar()->setRange(0, lineCount - _RowShowNum);
	verticalScrollBar()->setPageStep(_RowShowNum);

	// adjust the first line show
	int value = verticalScrollBar()->value();
	_RowShowFirst = value;
	// current number of line show
	_DataShow = (_ContentList.size() - _RowShowFirst);
	if (_DataShow > _RowShowNum)
	{
		_DataShow = _RowShowNum;
	}

	// update the viewport()
	viewport()->update();
}

QPoint WidgetViewer::CursorPosition(QPoint _pos)
{
	// transpform to current position
	QPoint result;
	int posX = _pos.x();
	int posY = _pos.y()-3;
	if (posX > _ColPrefix)
	{
		result.setX((posX - _ColPrefix)/ _CharW);
	}


	if (posY > _RowPrefix)
	{
		result.setY((posY - _RowPrefix) / _CharH + _RowShowFirst);
	}


	return result;
}

void WidgetViewer::SetSelection(QPoint _pos)
{
	int posX = _pos.x() > 0 ? _pos.x() : 0;
	int posY = _pos.y()>0 ? _pos.y() : 0;
	
	if (_SelectPInit.y() > posY || (_SelectPInit.y()== posY && _SelectPInit.x()> posX))
	{
		_SelectPBegin = QPoint(posX, posY); 
		_SelectPEnd = _SelectPInit;
	}
	else
	{
		_SelectPBegin = _SelectPInit; 
		_SelectPEnd = QPoint(posX, posY);
	}
	//printf("X:%d,Y:%d\n", _SelectPEnd.x(), _SelectPEnd.y());

}
void WidgetViewer::ResetSelection(QPoint _pos)
{
	int posX = _pos.x() > 0 ? _pos.x() : 0;
	int posY = _pos.y() ? _pos.y() : 0;
	_SelectPInit = QPoint(posX, posY);
	_SelectPBegin = QPoint(posX, posY);
	_SelectPEnd = QPoint(posX, posY);
}


void WidgetViewer::paintEvent(QPaintEvent* paintEvent)
{
	QPainter p(viewport());
	QColor formatColor = QColor(0, 0, 0);
	QColor hightLightColor("yellow");
	p.setFont(_Format);
	p.setPen(formatColor);
	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };
	QPoint pos(_ColPrefix, _RowPrefix);
	QFontMetrics fm(_Format, p.device());
	for (int l = 0; l < _DataShow; l++)
	{

		// absl
		int absl = _RowShowFirst + l;
		//int textLineWidth = _ContentList.at(_RowShowFirst + l).size() * _CharW;

		int textLineWidth =  fm.boundingRect(_ContentList.at(absl)).width();


		if (absl >= _SelectPBegin.y() && absl <= _SelectPEnd.y())
		{
			if (absl > _SelectPBegin.y() && absl < _SelectPEnd.y())
			{
				p.fillRect(QRect(pos, QSize(textLineWidth, _CharH)).normalized(), hightLightColor);
			}
			else
			{
				int lpos = 0;
				int rpos = textLineWidth;
				if(absl == _SelectPBegin.y())
				{
					lpos = f_min((_SelectPBegin.x()) * _CharW, textLineWidth);
				}
				if(absl == _SelectPEnd.y())
				{
					rpos = f_min((_SelectPEnd.x()) * _CharW, textLineWidth);
				}
				// for the first line andd last line, handle char one by one
				// tranverse the line, find the hightlight left pos, and right pos
				//for (auto& item : _ContentList.at(absl))
				//{
				//	int charWidth = fm.boundingRect(item).width();	
				//}
				int hlpos = 0;
				int hrpos = textLineWidth;
				for (int i = 0; i < _ContentList.at(absl).size(); i++)
				{
					int charWidth = fm.boundingRect(_ContentList.at(absl).mid(i)).width();
					if (textLineWidth - charWidth > lpos)
					{
						break;
					}
					hlpos = textLineWidth - charWidth;
				}
				for (int i = _ContentList.at(absl).size(); i > 0; i--)
				{
					int charWidth = fm.boundingRect(_ContentList.at(absl).mid(0,i)).width();
					if (charWidth < rpos)
					{
						break;
					}
					hrpos = charWidth;
				}
				p.fillRect(QRect(pos+QPoint(hlpos,0), QSize(hrpos-hlpos, _CharH)).normalized(), hightLightColor);
			}
			/*else if (absl == _SelectPBegin.y() && absl == _SelectPEnd.y())
			{
				int width = (_SelectPEnd.x() - _SelectPBegin.x()) * _CharW;
				if (_SelectPBegin.x() * _CharW > textLineWidth)
				{
					width = 0;
				}
				if (_SelectPEnd.x() * _CharW > textLineWidth)
				{
					width = textLineWidth - _SelectPBegin.x() * _CharW;
				}
				p.fillRect(QRect(pos + QPoint(_SelectPBegin.x() * _CharW, 0), QSize(width, _CharH)).normalized(), hightLightColor);
			}
			else if (absl == _SelectPBegin.y())
			{
				int width = textLineWidth -(_SelectPBegin.x()) * _CharW;
				if (_SelectPBegin.x() * _CharW > textLineWidth)
				{
					width = 0;
				}
				
				p.fillRect(QRect(pos+ QPoint(_SelectPBegin.x()*_CharW,0), QSize(width, _CharH)).normalized(), hightLightColor);
			}
			else
			{
				int width = f_min((_SelectPEnd.x()) * _CharW,textLineWidth);
				p.fillRect(QRect(pos, QSize(width, _CharH)).normalized(), hightLightColor);
			}*/
		}
		pos += QPoint(0, _CharH);
		p.drawText(pos,_ContentList.at(absl));
	}

}


//void WidgetViewer::paintEvent(QPaintEvent* paintEvent)
//{
//	QPainter p(viewport());
//	p.setPen(QColor(187, 187, 187));
//	p.setBrush(QColor(0x23, 0x26, 0x29));
//	//p.setFont(_format.font());
//
//	//p.fillRect(viewport()->rect(), QColor(0x23, 0x26, 0x29));
//	p.fillRect(viewport()->rect(), QColor(0x255, 0x255, 0x255));
//
//	QPoint pos;
//	QColor formatColor = QColor(0, 0, 0);
//	QColor hightLightColor("yellow");
//	pos.setY(_ColPrefix);
//
//	int firstLine = verticalScrollBar()->value();
//	int lastLine = (viewport()->height() - _ColPrefix) / _CharH + firstLine;
//
//	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
//	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };
//	QPoint curP = _CurCursorPos;
//	QPoint lastP = _LastCursorPos;
//	curP = curP - QPoint(_RowPrefix,_ColPrefix);
//	lastP = lastP - QPoint(_RowPrefix,_ColPrefix);
//
//	int firstHightLine = f_min(curP.y() / _CharH, lastP.y() / _CharH);
//	int lastHightLine = f_max(curP.y() / _CharH, lastP.y() / _CharH);
//	int firstHightCol = curP.y() > lastP.y() ? lastP.x() / _CharW : curP.x() / _CharW;
//	int lastHightCol = curP.y() > lastP.y() ? curP.x() / _CharW : lastP.x() / _CharW;
//	if (firstHightLine == lastHightLine && firstHightCol > lastHightCol)
//	{
//		int temp = firstHightCol;
//		firstHightCol = lastHightCol;
//		lastHightCol = temp;
//	}
//
//	if (lastLine > LineCount())
//	{
//		lastLine = LineCount();
//	}
//
//	QFont font1("monoSpace");
//	font1.setPixelSize(_CharH);
//	font1.setLetterSpacing(QFont::AbsoluteSpacing, 0);
//	p.setFont(font1);
//	p.setPen(formatColor);
//	for (int l = firstLine; l < lastLine; l++)
//	{
//		pos.setX(_RowPrefix);
//
//		int textLineWidth = 0;
//		for (auto& item : _ContentList.at(l))
//		{
//			textLineWidth += (IsWideChar(item)? _CharW*2:_CharW);
//		}
//
//		// draw highlight for each line
//		//if (l > firstHightLine && l < lastHightLine)
//		//{
//		//	p.fillRect(QRect(pos, QSize(textLineWidth, _CharH)).normalized(), hightLightColor);
//		//}
//		//else if (l == firstHightLine && l == lastHightLine)
//		//{
//		//	p.fillRect(QRect(pos + QPoint(firstHightCol * _CharW, 0), QSize(f_min(lastHightCol*_CharW, f_max(textLineWidth - _CharW * firstHightCol, 0)), _CharH)).normalized(), hightLightColor);
//		//	printf("??\n");
//		//}
//		//else if (l == firstHightLine)
//		//{
//		//	p.fillRect(QRect(pos+ QPoint(firstHightCol * _CharW,0), QSize(f_max(textLineWidth - _CharW* firstHightCol,0) , _CharH)).normalized(), hightLightColor);
//		//	printf("!!\n");
//		//}
//		//else if (l == lastHightLine)
//		//{
//		//	p.fillRect(QRect(pos, QSize( f_min(lastHightCol * _CharW, textLineWidth), _CharH)).normalized(), hightLightColor);
//		//}
//		if (l >= firstHightLine && l <= lastHightLine)
//		{
//			int leftX = 0;
//			int rightX = textLineWidth;
//			if (l == firstHightLine)
//			{
//				leftX =  f_min(firstHightCol * _CharW,rightX);
//			}
//			if (l == lastHightLine)
//			{
//				rightX = f_min(lastHightCol * _CharW,rightX);
//			}
//			//printf("%d,%d\n",leftX, rightX);
//			p.fillRect(QRect(pos + QPoint(leftX, 0), QSize(rightX - leftX, _CharH)).normalized(), hightLightColor);
//		}
//
//		pos.setY(pos.y() + _CharH);
//
//		// draw text
//		//QRectF rect(pos, QPoint(textLineWidth, _CharH));
//		p.drawText(pos, _ContentList.at(l));
//
//		// draw text
//		//for (int c = 0; c < _ContentList.at(l).size(); c++)
//		//{
//		//	const QChar& vtChar = _ContentList.at(l)[c];
//		//	//p.setPen(vtChar.format().foreground());
//		//	p.setPen(formatColor);
//
//		//	// draw highlight for each node
//		//	if (IsWideChar(vtChar))
//		//	{
//		//		p.drawText(QRect(pos, QSize(_CharW*2, _CharH + 1)).normalized(), Qt::AlignLeft, QString(vtChar));
//		//		pos.setX(pos.x() + _CharW*2);
//		//	}
//		//	else
//		//	{
//		//		p.drawText(QRect(pos, QSize(_CharW, _CharH)).normalized(), Qt::AlignCenter, QString(vtChar));
//		//		pos.setX(pos.x() + _CharW);
//		//	}
//		//}
//	}
//}
