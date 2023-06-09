﻿#include "WidgetBrowser.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include <QPainter>
#include <QGuiApplication>
#include <QClipboard>
#include <iostream>
#include <QTimer>
#include <QScrollBar>
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

    QTimer* timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,[this,timer](){
        static int processNum = 0;
        _WidgetViewer->AppendData("\r<processBar>" +QString::number(processNum++) +"</processBar>");
        processNum+=3;
        if(processNum>100)
        {
            timer->stop();
        }
    });
    //timer->start(250);
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
#define USE_XmlNaiveParser 1

#ifdef USE_XmlNaiveParser
#include "XmlNaiveParser.h"
#else
#include <pugixml/pugixml.hpp>
#endif
//#include "../ZStyleSheet.h"


WidgetViewer::WidgetViewer(QWidget* parent)
	:QAbstractScrollArea(parent)
{
	setMouseTracking(true);
	connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjust()));

	_Format.setFamily("monoSpace");
	_Format.setPixelSize(_CharH);
	_Format.setLetterSpacing(QFont::AbsoluteSpacing, _RowSpace);
	
	QFontMetrics fm(_Format, viewport());
	_CharW = fm.boundingRect("9").width();
	//setStyleSheet("");
	this->setStyleSheet("background-color:rgba(51,51,51,1);");
    //this->verticalScrollBar()->setStyleSheet(ZStyleSheet_ScollBar3);

	AppendData("1");
    AppendData("<font>nihao world!</font><font color=\"red\">hello world!</font>");
    AppendData("nihao world!hello world!");
	AppendData("<font color=\"green\">hello world!</font>");
	AppendData("12");
	AppendData("134");
	AppendData("12345");
	AppendData("1424325");
	AppendData("124234");
	AppendData("1234");
	AppendData("123");
	AppendData("<font color=\"red\">hello world!</font>");
	AppendData("<font color=\"green\">hello world!</font>");
	AppendData("<processBar>60</processBar>");

}

void WidgetViewer::AppendData(QString _text)
{

#if DRAW_RICH_CONTENT
    if(_text.startsWith("\r") && !_text.startsWith("\r\n"))
    {
        if(_ContentRichList.size()>0)
        {
            _ContentRichList.pop_back();
        }
    }
	// parse the text
	// current format
	// 1.  
	// 2.
	// parse the data and push to the contentRichList

#ifdef USE_XmlNaiveParser
    XmlNaiveParser parser;
    std::string content = _text.toUtf8().toStdString();
    auto result = parser.LoadBuffer(content);
    if(result)
    {
        auto rootNode = std::make_shared<ViewLineString>();
        std::shared_ptr <ViewLineNode> curNode = rootNode;
        for(auto& item:parser._ChildNodeList)
        {
             if(item.blockTag=="" || item.blockTag=="font")
             {
                 auto strNode = std::make_shared<ViewLineString>();
                 strNode->SetColor(item.attribute("color"));
                 strNode->SetText(QString::fromStdString(item.blockContent));
                 curNode->nextNode = strNode;
                 curNode = std::move(strNode);

             }
             else if(item.blockTag=="processBar")
             {
                 auto strNode = std::make_shared<ViewLineProcessBar>();
                 strNode->SetProcess(QString::fromStdString(item.blockContent).toInt());
                 curNode->nextNode = strNode;
                 curNode = std::move(strNode);

             }
        }
        if (rootNode->nextNode)
        {
            _ContentRichList.append(rootNode->nextNode);
        }
    }
    else
    {
        printf("raw text\n");
        auto rootNode = std::make_shared<ViewLineString>();
        rootNode->SetText(_text);
        _ContentRichList.append(rootNode);
    }

#else
    pugi::xml_document doc;
    std::string content = _text.toUtf8().toStdString();
    pugi::xml_parse_result result = doc.load_buffer((char*)content.data(), content.size());
    if (result)
    {
        auto rootNode = std::make_shared<ViewLineString>();
        std::shared_ptr <ViewLineNode> curNode = rootNode;
        for (auto it = doc.begin(); it != doc.end(); ++it)
        {
            pugi::xpath_node node = *it;
            std::cout << "name " << node.node().attribute("color").value() << node.node().name() << node.node().child_value() << std::endl;
            std::string name = node.node().name();
            if (name == "font")
            {
                //std::string color = node.node().attribute("color").value();
                auto strNode = std::make_shared<ViewLineString>();
                strNode->SetColor(node.node().attribute("color").value());
                strNode->SetText(node.node().child_value());
                curNode->nextNode = strNode;
                curNode = std::move(strNode);
            }
            else if (name == "processBar")
            {
                auto strNode = std::make_shared<ViewLineProcessBar>();
                strNode->SetProcess(QString(node.node().child_value()).toInt());
                curNode->nextNode = strNode;
                curNode = std::move(strNode);
            }
        }
        if (rootNode->nextNode)
        {
            _ContentRichList.append(rootNode->nextNode);
        }
    }
    else
    {
        auto rootNode = std::make_shared<ViewLineString>();
        rootNode->SetText(_text);
        _ContentRichList.append(rootNode);
    }
#endif

#else
	_ContentList.append(_text);
#endif
	adjust();
	// scroll to buttom
	verticalScrollBar()->setValue(verticalScrollBar()->maximum());
}

void WidgetViewer::Clear()
{
#if DRAW_RICH_CONTENT
	_ContentRichList.clear();
#else
	_ContentList.clear();
#endif
	
	//this->viewport()->update();
	adjust();
}

QString WidgetViewer::Copy()
{
	// copy the selected text to the clip board
	QClipboard* clipboard = QGuiApplication::clipboard();

	// get the selected text
	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };
#if DRAW_RICH_CONTENT
	QString result;
	if (_ContentRichList.size() == 0)
	{
		return QString();
	}
	QFontMetrics fm(_Format, viewport());
	for (int absl = _SelectPBegin.y(); absl <= _SelectPEnd.y() && absl >= 0 && absl < _ContentRichList.size(); absl++)
	{
		if (_ContentRichList.at(absl)->GetType() != ViewLineNode::NodeType::String)
		{
			continue;
		}

		auto lineItem = std::dynamic_pointer_cast<ViewLineString>(_ContentRichList.at(absl));
        QString lineItemText = lineItem->GetText();
		if (absl > _SelectPBegin.y() && absl < _SelectPEnd.y())
		{
            result.append(lineItemText);
		}
		else
		{
            int textLineWidth = fm.boundingRect(lineItemText).width();
			int lpos = 0;
			int rpos = textLineWidth;
			if (absl == _SelectPBegin.y())
			{
				lpos = f_min((_SelectPBegin.x()) * (_CharW+ _RowSpace), textLineWidth);
			}
			if (absl == _SelectPEnd.y())
			{
				rpos = f_min((_SelectPEnd.x()) * (_CharW + _RowSpace), textLineWidth);
			}
			// for the first line andd last line, handle char one by one
			// tranverse the line, find the hightlight left pos, and right pos
			//for (auto& item : _ContentList.at(absl))
			//{
			//	int charWidth = fm.boundingRect(item).width();	
			//}
			if (lpos >= textLineWidth)
			{
				continue;
			}
			int hlIndex = 0;
            int hrIndex = lineItemText.size() - 1;
            for (int i = 0; i < lineItemText.size(); i++)
			{
                int charWidth = fm.boundingRect(lineItemText.mid(i)).width();
				if (textLineWidth - charWidth > lpos)
				{
					break;
				}
				hlIndex = i;
			}
            for (int i = lineItemText.size(); i > 0; i--)
			{
                int charWidth = fm.boundingRect(lineItemText.mid(0, i)).width();
				if (charWidth < rpos)
				{
					break;
				}
				hrIndex = i;
			}
            result.append(lineItemText.mid(hlIndex, hrIndex - hlIndex));
		}
		if (absl != _SelectPEnd.y()) {
			result.append("\n");
		}
	}
	if (result.size() > 0)
	{
		clipboard->setText(result);
	}
#else
	QString result;
	if (_ContentList.size() == 0)
	{
		return QString();
}
	QFontMetrics fm(_Format, viewport());
	for (int absl = _SelectPBegin.y(); absl <= _SelectPEnd.y() && absl >= 0 && absl < _ContentList.size(); absl++)
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
			if (lpos >= textLineWidth)
			{
				continue;
			}
			int hlIndex = 0;
			int hrIndex = _ContentList.at(absl).size() - 1;
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
			result.append(_ContentList.at(absl).mid(hlIndex, hrIndex - hlIndex));
		}
		if (absl != _SelectPEnd.y()) {
			result.append("\n");
		}
	}
	if (result.size() > 0)
	{
		clipboard->setText(result);
	}


#endif
	
	return QString();
}

void WidgetViewer::resizeEvent(QResizeEvent* event)
{
	Q_UNUSED(event)
	adjust();
}

void WidgetViewer::mousePressEvent(QMouseEvent* _event)
{
	_Pressed = true;
	// record cur postion and last position
	if (_event->button() == Qt::LeftButton)
	{
		auto pos = CursorPosition(_event->pos());
		ResetSelection(pos);
		SetSelection(pos);
		this->viewport()->update();
	}
}

void WidgetViewer::mouseReleaseEvent(QMouseEvent* _event)
{
	_Pressed = false;
}

void WidgetViewer::mouseMoveEvent(QMouseEvent* _event)
{
	if (_Pressed)
	{
		auto pos = CursorPosition(_event->pos());
		if (pos.x() >= 0 && pos.y() >= 0)
		{
			SetSelection(pos);
		}
		this->viewport()->update();
	}
}

void WidgetViewer::keyPressEvent(QKeyEvent* _event)
{
	/* Copy */
	if (_event->matches(QKeySequence::Copy))
	{
		Copy();
	}
}

void WidgetViewer::adjust() {
	// adjust the scrollbar value
	// total number of line show
#if DRAW_RICH_CONTENT
	_RowShowNum = (viewport()->height() - _RowPrefix) / (_CharH + _ColSpace);
	int lineCount = _ContentRichList.size();
	verticalScrollBar()->setRange(0, lineCount - _RowShowNum);
	verticalScrollBar()->setPageStep(_RowShowNum);

	// adjust the first line show
	int value = verticalScrollBar()->value();
	_RowShowFirst = value;
	// current number of line show
	_DataShow = (lineCount - _RowShowFirst);
	if (_DataShow > _RowShowNum)
	{
		_DataShow = _RowShowNum;
	}
#else
	_RowShowNum = (viewport()->height() - _RowPrefix) / _CharH;
	int lineCount = _ContentList.size();
	verticalScrollBar()->setRange(0, lineCount - _RowShowNum);
	verticalScrollBar()->setPageStep(_RowShowNum);

	// adjust the first line show
	int value = verticalScrollBar()->value();
	_RowShowFirst = value;
	// current number of line show
	_DataShow = (lineCount - _RowShowFirst);
	if (_DataShow > _RowShowNum)
	{
		_DataShow = _RowShowNum;
	}

#endif


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
		result.setX((posX - _ColPrefix)/ (_CharW+ _RowSpace));
	}


	if (posY > _RowPrefix)
	{
		result.setY((posY - _RowPrefix) / (_CharH+ _ColSpace) + _RowShowFirst);
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
	QColor formatColor = QColor("white");
	QColor hightLightColor("#0078d7");
	p.setFont(_Format);
	p.setPen(formatColor);
	auto f_min = [](int a, int b)->int {return  a > b ? b : a; };
	auto f_max = [](int a, int b)->int {return  a < b ? b : a; };
	QPoint pos(_ColPrefix, _RowPrefix);
	QFontMetrics fm(_Format, p.device());

	p.fillRect(paintEvent->rect(), QColor("#333333"));

	for (int l = 0; l < _DataShow; l++)
	{
		// absl
		int absl = _RowShowFirst + l;

#if DRAW_RICH_CONTENT

		auto lineItem = _ContentRichList.at(absl);
		QString lineItemText = lineItem->GetText();
		int textLineWidth = fm.boundingRect(lineItemText).width();
		// draw hightlight
	
		pos += QPoint(0, _CharH );

		if (absl >= _SelectPBegin.y() && absl <= _SelectPEnd.y())
		{
		    if (absl > _SelectPBegin.y() && absl < _SelectPEnd.y())
		    {
			p.fillRect(QRect(pos, QSize(textLineWidth, -_CharH)).normalized(), hightLightColor);
		    }
		    else
		    {
			int lpos = 0;
			int rpos = textLineWidth;
			if (absl == _SelectPBegin.y())
			{
			    lpos = f_min((_SelectPBegin.x()) * (_CharW+ _RowSpace), textLineWidth);
			}
			if (absl == _SelectPEnd.y())
			{
			    rpos = f_min((_SelectPEnd.x()) * (_CharW + _RowSpace), textLineWidth);
			}
			// for the first line andd last line, handle char one by one
			// tranverse the line, find the hightlight left pos, and right pos
			//for (auto& item : _ContentList.at(absl))
			//{
			//	int charWidth = fm.boundingRect(item).width();
			//}

			if (lpos < textLineWidth)
			{
			    int hlpos = 0;
			    int hrpos = textLineWidth;
			    for (int i = 0; i < lineItemText.size(); i++)
			    {
				int charWidth = fm.boundingRect(lineItemText.mid(i)).width();
				if (textLineWidth - charWidth > lpos)
				{
				    break;
				}
				hlpos = textLineWidth - charWidth;
			    }
			    for (int i = lineItemText.size(); i > 0; i--)
			    {
				int charWidth = fm.boundingRect(lineItemText.mid(0, i)).width();
				if (charWidth < rpos)
				{
				    break;
				}
				hrpos = charWidth;
			    }
			    p.fillRect(QRect(pos + QPoint(hlpos, 0), QSize(hrpos - hlpos, -_CharH)).normalized(), hightLightColor);
			}

		    }
		}
	
		// draw content
		lineItem->Paint(&p, pos);
		pos += QPoint(0, _ColSpace);
#else
		int textLineWidth = fm.boundingRect(_ContentList.at(absl)).width();
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

				if (lpos < textLineWidth)
				{
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
						int charWidth = fm.boundingRect(_ContentList.at(absl).mid(0, i)).width();
						if (charWidth < rpos)
						{
							break;
						}
						hrpos = charWidth;
					}
					p.fillRect(QRect(pos + QPoint(hlpos, 0), QSize(hrpos - hlpos, _CharH)).normalized(), hightLightColor);
				}

			}
		}
		pos += QPoint(0, _CharH);
		p.drawText(pos, _ContentList.at(absl));
#endif
	}

	
}

/*
class ViewLineString
*/
void ViewLineString::Paint(QPainter* _painter, QPoint pos)
{
	if (GetColor().size() > 0)
	{
		_painter->setPen(QColor(GetColor()));
	}
	else
	{
		_painter->setPen(QColor(255,255,255));
	}
    _painter->drawText(pos + QPoint(0,-_painter->fontMetrics().descent()), _Text);
    if(nextNode)
    {
        nextNode->Paint(_painter,pos + QPoint(_painter->fontMetrics().horizontalAdvance(_Text),0));
    }
}

QRect ViewLineString::GetRect(QRect _rect)
{
    // giving a width



//    int lpos = 0;
//    int rpos = textLineWidth;
//    if (absl == _SelectPBegin.y())
//    {
//        lpos = f_min((_SelectPBegin.x()) * _CharW, textLineWidth);
//    }
//    if (absl == _SelectPEnd.y())
//    {
//        rpos = f_min((_SelectPEnd.x()) * _CharW, textLineWidth);
//    }
//    // for the first line andd last line, handle char one by one
//    // tranverse the line, find the hightlight left pos, and right pos
//    //for (auto& item : _ContentList.at(absl))
//    //{
//    //	int charWidth = fm.boundingRect(item).width();
//    //}

//    if (lpos < textLineWidth)
//    {
//        int hlpos = 0;
//        int hrpos = textLineWidth;
//        for (int i = 0; i < lineItem->GetText().size(); i++)
//        {
//            int charWidth = fm.boundingRect(lineItem->GetText().mid(i)).width();
//            if (textLineWidth - charWidth > lpos)
//            {
//                break;
//            }
//            hlpos = textLineWidth - charWidth;
//        }
//        for (int i = lineItem->GetText().size(); i > 0; i--)
//        {
//            int charWidth = fm.boundingRect(lineItem->GetText().mid(0, i)).width();
//            if (charWidth < rpos)
//            {
//                break;
//            }
//            hrpos = charWidth;
//        }
//    }
    return QRect();
}

/*
class ViewLineProcessBar
*/
void ViewLineProcessBar::Paint(QPainter* _painter, QPoint pos)
{
	if (_ProcessNum > 100)
	{
		_ProcessNum = 100;
	}
	else if (_ProcessNum < 0)
	{
		_ProcessNum = 0;
	}
	
    QColor backColor(Qt::white);
    QColor borderCoolor(QColor(0xFF,0xFF,0xFF).rgb() - backColor.rgb());
    qreal mid_y = pos.y() - _painter->fontMetrics().descent() - _painter->fontMetrics().ascent()/2;
    qreal radius = _painter->fontMetrics().ascent()/2;
    qreal processBarWidth = 400;
    _painter->setRenderHint(QPainter::Antialiasing);
    _painter->setPen(borderCoolor);
    _painter->setBrush(backColor);
    _painter->drawRoundedRect(QRect(QPoint(pos.x(), mid_y-radius), QSize(processBarWidth +radius, radius*2)),radius/2,radius/2);
    _painter->setBrush(borderCoolor);
    _painter->drawRoundedRect(QRect(QPoint(pos.x()+radius/2, mid_y-radius/2), QSize(processBarWidth*_ProcessNum/100, radius*2/2)),radius/4,radius/4);
    _painter->setPen(backColor);
    _painter->drawText(QPoint(pos.x()+processBarWidth+ 2*radius,pos.y()-_painter->fontMetrics().descent()),QString::number(_ProcessNum)+"%");

}

QRect ViewLineProcessBar::GetRect(QRect _rect)
{
    return QRect();
}
