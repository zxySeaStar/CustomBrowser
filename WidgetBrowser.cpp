#include "WidgetBrowser.h"
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
}

void WidgetViewer::AppendData(QString _text)
{
	setUpdatesEnabled(false);

	// parse the text
	// current format
	// 1.  
	// 2.

	_ContentList.append(_text);
	verticalScrollBar()->setRange(0, _CharH * (LineCount() + 1) - viewport()->size().height() + 6);
	verticalScrollBar()->setValue(verticalScrollBar()->maximum());
	setUpdatesEnabled(true);
	this->viewport()->update();
}

void WidgetViewer::Clear()
{
	_ContentList.clear();
	this->viewport()->update();
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
	int firstHightLine = f_min(_CurCursorPos.y() / _CharH, _LastCursorPos.y() / _CharH);
	int lastHightLine = f_max(_CurCursorPos.y() / _CharH, _LastCursorPos.y() / _CharH);
	int firstHightCol = _CurCursorPos.y() > _LastCursorPos.y() ? _LastCursorPos.x() / _CharW : _CurCursorPos.x() / _CharW;
	int lastHightCol = _CurCursorPos.y() > _LastCursorPos.y() ? _CurCursorPos.x() / _CharW : _LastCursorPos.x() / _CharW;

	QString result;
	for (int l = firstHightLine; l < lastHightLine && l < _ContentList.size(); l++)
	{
		result.append(_ContentList.at(l));
	}

	clipboard->setText(result);
	return QString();
}

void WidgetViewer::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event)
	verticalScrollBar()->setPageStep(_CharH * 10);
	verticalScrollBar()->setSingleStep(_CharH);
	verticalScrollBar()->setRange(0, _CharH * (LineCount() + 1) - viewport()->size().height() + 6);
}

void WidgetViewer::mousePressEvent(QMouseEvent* _event)
{
	_Pressed = true;
	// record cur postion and last position
	if (_event->button() == Qt::LeftButton)
	{
		auto pos = _event->pos() + QPoint(0,verticalScrollBar()->value());
		_LastCursorPos = pos;
		_CurCursorPos = pos;
		this->viewport()->update();
	}
}

void WidgetViewer::mouseReleaseEvent(QMouseEvent* _event)
{
	_Pressed = false;
	// update last 
	if (_event->button() == Qt::LeftButton)
	{
		auto pos = _event->pos() + QPoint(0, verticalScrollBar()->value());
		_CurCursorPos = pos;
		this->viewport()->update();
	}
}

void WidgetViewer::mouseMoveEvent(QMouseEvent* _event)
{
	if (_Pressed)
	{
		auto pos = _event->pos() + QPoint(0, verticalScrollBar()->value());
		_CurCursorPos = pos;
		this->viewport()->update();
	}
}

void WidgetViewer::paintEvent(QPaintEvent* paintEvent)
{
	QPainter p(viewport());
	p.setPen(QColor(187, 187, 187));
	p.setBrush(QColor(0x23, 0x26, 0x29));
	//p.setFont(_format.font());

	//p.fillRect(viewport()->rect(), QColor(0x23, 0x26, 0x29));
	p.fillRect(viewport()->rect(), QColor(0x255, 0x255, 0x255));

	QPoint pos;
	QColor formatColor = QColor(0, 0, 0);
	QColor hightLightColor("yellow");
	pos.setY(_ColPrefix);

	int firstLine = verticalScrollBar()->value() / _CharH;
	int lastLine = viewport()->size().height() / _CharH + firstLine;

	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };

	int firstHightLine = f_min(_CurCursorPos.y() / _CharH, _LastCursorPos.y() / _CharH);
	int lastHightLine = f_max(_CurCursorPos.y() / _CharH, _LastCursorPos.y() / _CharH);
	int firstHightCol = _CurCursorPos.y() > _LastCursorPos.y() ? _LastCursorPos.x() / _CharW : _CurCursorPos.x() / _CharW;
	int lastHightCol = _CurCursorPos.y() > _LastCursorPos.y() ? _CurCursorPos.x() / _CharW : _LastCursorPos.x() / _CharW;
	if (firstHightLine == lastHightLine && firstHightCol > lastHightCol)
	{
		int temp = firstHightCol;
		firstHightCol = lastHightCol;
		lastHightCol = temp;
	}

	if (lastLine > LineCount())
	{
		lastLine = LineCount();
	}

	QFont font1("monoSpace");
	font1.setPixelSize(_CharH);
	p.setFont(font1);
	p.setPen(formatColor);
	for (int l = firstLine; l < lastLine; l++)
	{
		pos.setX(_RowPrefix);

		int textLineWidth = 0;
		for (auto& item : _ContentList.at(l))
		{
			textLineWidth += (IsWideChar(item)? _CharW*2:_CharW);
		}

		// draw highlight for each line
		if (l > firstHightLine && l < lastHightLine)
		{
			p.fillRect(QRect(pos, QSize(textLineWidth, _CharH)).normalized(), hightLightColor);
		}
		else if (l == firstHightLine && l == lastHightLine)
		{
			p.fillRect(QRect(pos + QPoint(firstHightCol * _CharW, 0), QSize(f_min(lastHightCol*_CharW, f_max(textLineWidth - _CharW * firstHightCol, 0)), _CharH)).normalized(), hightLightColor);
			printf("??\n");
		}
		else if (l == firstHightLine)
		{
			p.fillRect(QRect(pos+ QPoint(firstHightCol * _CharW,0), QSize(f_max(textLineWidth - _CharW* firstHightCol,0) , _CharH)).normalized(), hightLightColor);
			printf("!!\n");
		}
		else if (l == lastHightLine)
		{
			p.fillRect(QRect(pos, QSize( f_min(lastHightCol * _CharW, textLineWidth), _CharH)).normalized(), hightLightColor);
		}

		pos.setY(pos.y() + _CharH);

		// draw text
		p.drawText(pos,_ContentList.at(l));

		// draw text
		//for (int c = 0; c < _ContentList.at(l).size(); c++)
		//{
		//	const QChar& vtChar = _ContentList.at(l)[c];
		//	//p.setPen(vtChar.format().foreground());
		//	p.setPen(formatColor);

		//	// draw highlight for each node
		//	if (IsWideChar(vtChar))
		//	{
		//		p.drawText(QRect(pos, QSize(_CharW*2, _CharH + 1)).normalized(), Qt::AlignLeft, QString(vtChar));
		//		pos.setX(pos.x() + _CharW*2);
		//	}
		//	else
		//	{
		//		p.drawText(QRect(pos, QSize(_CharW, _CharH)).normalized(), Qt::AlignCenter, QString(vtChar));
		//		pos.setX(pos.x() + _CharW);
		//	}
		//}
	}
}