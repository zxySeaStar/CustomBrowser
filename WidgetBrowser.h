#ifndef WIDGET_BROWSER_H_
#define WIDGET_BROWSER_H_
#include <QWidget>
#include <QPushButton>
#include <QCombobox>
#include <QAbstractScrollArea>
#include <QTextEdit>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <memory>
class WidgetChoosePort;
class WidgetViewer;
class WidgetBrowser :public QWidget {
	Q_OBJECT
public:
	WidgetBrowser(QWidget* parent=nullptr);
private:
	void InitUI();
	void UpdateUI();
	WidgetChoosePort* _WidgetPort;
	WidgetViewer* _WidgetViewer;
	QTextEdit* _TextEdit;
	QPushButton* _BtnAppend;
	QPushButton* _BtnClear;
	QPushButton* _BtnCopy;

	// line 
	// paintEvent draw for each line
};

class WidgetChoosePort :public QWidget {
	Q_OBJECT
public:
	WidgetChoosePort(QWidget* parent = nullptr);
private:
	void InitUI();
	void UpdateUI();
	void TryConnect(bool flags);

	// comstom browser
	// target: parse processbar command


	// selectable

	// combobox select serial

	// 

	QFrame* _Frame;
	QComboBox* _Combobox;
	QPushButton* _BtnConnect;
	QPushButton* _BtnStop;
	bool _IsConnected = false;
};


class ViewLineNode {
public:
	enum class NodeType {
		None,
		String,
		ProcessBar
	};
	// line offset
	virtual int GetOffset() = 0;
	virtual NodeType GetType() = 0;
	virtual QString& GetText()
	{
        return _Text;
	}
	virtual void Paint(QPainter* _painter,QPoint pos) = 0;
	//virtual QRect GetRect(QRect _rect) = 0; // interact with the cursor, get hightlight rect
	std::shared_ptr<ViewLineNode> nextNode;
    QString _Text;
};

class ViewLineString : public ViewLineNode
{
public:
	//~ViewLineString()
	//{
	//	printf("release\n");
	//}
	virtual int GetOffset() override{
		return _Offset;
	}
	virtual NodeType GetType() override {
		return _Type;
	}
	//virtual QRect GetRect(QRect _rect) override;
	//void SetText(std::string _info)
	//{
	//	_Text = QString::fromStdString(_info);
	//}
	void SetText(QString _info)
	{
		_Text = _info;
	}
	void SetColor(std::string _value)
	{
		_Color = QString::fromStdString(_value);
	}
	QString GetColor()
	{
		return _Color;
	}
	QString& GetText() override
	{
		return _Text;
	}

	virtual void Paint(QPainter* _painter, QPoint pos) override;
private:
	int _Offset = 0;
	NodeType _Type{ NodeType::String};
	QString _Color;

};

class ViewLineProcessBar : public ViewLineNode
{
public:
	virtual int GetOffset() override {
		return _Offset;
	}
	virtual NodeType GetType() override {
		return _Type;
	}
	void SetProcess(int _num)
	{
		_ProcessNum = _num;
	}
	virtual void Paint(QPainter* _painter, QPoint pos) override;
private:
	int _Offset = 0;
	int _ProcessNum=0;
	NodeType _Type{ NodeType::ProcessBar };
};



#define DRAW_RICH_CONTENT 1

class WidgetViewer : public QAbstractScrollArea {
	Q_OBJECT
public:
	explicit WidgetViewer(QWidget* parent = nullptr);
	void AppendData(QString _text);
	void Clear();
	QString Copy();

public slots:
	void adjust();
private:
	// append the data and update the scrollbar
	// todo:
	// 1. selectable text, draw hightlight ok
	// 1.5 copy selected text
	// 2. process bar
	// 3. color text

	// 4. scrollbar problem
	void paintEvent(QPaintEvent* paintEvent) override;
	void resizeEvent(QResizeEvent* paintEvent) override;
	virtual void mousePressEvent(QMouseEvent* _event) override;
	virtual void mouseReleaseEvent(QMouseEvent* _event) override;
	virtual void mouseMoveEvent(QMouseEvent* _event) override;

	void PaintString(std::shared_ptr<ViewLineString> _node,QPoint _pos, QPainter* _painter);

	bool IsWideChar(QChar _char)
	{
		return _char.unicode() >= 0x4e00 && _char.unicode() <= 0x9FA5;
	}

	int LineCount()
	{
#if DRAW_RICH_CONTENT
		return _ContentRichList.size();
#else
		return _ContentList.size();

#endif
	}

	int _CharH = 12*2;
	int _CharW = 12;
#if DRAW_RICH_CONTENT
	QList<std::shared_ptr<ViewLineNode>> _ContentRichList;
#else
	QList<QString> _ContentList;
#endif
	

	QPoint _LastCursorPos;
	QPoint _CurCursorPos;
	bool	_Pressed = { false };


	int _RowPrefix = 6;
	int _ColPrefix = 6;


	// first show line
	int _RowShowFirst{ 0 }; // #line for whole page
	int _RowShowNum{ 0 }; // #line show in one page
	int _DataShow{ 0 }; // #dataline show in current page
	QPoint _SelectPInit;
	QPoint _SelectPBegin{ -1,-1 };
	QPoint _SelectPEnd{ -1,-1 };

	QFont _Format;

	QPoint CursorPosition(QPoint _pos);
	void SetSelection(QPoint _pos);
	void ResetSelection(QPoint _pos);
	bool CursorVisable(QPoint _pos);


};

#endif
