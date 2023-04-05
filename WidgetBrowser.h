#ifndef WIDGET_BROWSER_H_
#define WIDGET_BROWSER_H_
#include <QWidget>
#include <QPushButton>
#include <QCombobox>
#include <QAbstractScrollArea>
#include <QTextEdit>
#include <QMouseEvent>
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

class WidgetViewer : public QAbstractScrollArea {
	Q_OBJECT
public:
	explicit WidgetViewer(QWidget* parent = nullptr);
	void AppendData(QString _text);
	void Clear();
	void Copy();
private:
	// append the data and update the scrollbar
	// todo:
	// 1. selectable text, draw hightlight ok
	// 1.5 copy selected text
	// 2. process bar
	// 3. color text
	void paintEvent(QPaintEvent* paintEvent) override;
	void resizeEvent(QResizeEvent* paintEvent) override;
	virtual void mousePressEvent(QMouseEvent* _event) override;
	virtual void mouseReleaseEvent(QMouseEvent* _event) override;
	virtual void mouseMoveEvent(QMouseEvent* _event) override;

	bool IsWideChar(QChar _char)
	{
		return _char.unicode() >= 0x4e00 && _char.unicode() <= 0x9FA5;
	}

	int LineCount()
	{
		return _ContentList.size();
	}
	int _CharH = 13;
	int _CharW = 7;
	QList<QString> _ContentList;

	QPoint _LastCursorPos;
	QPoint _CurCursorPos;
	bool	_Pressed = { false };


	int _RowPrefix = 6;
	int _ColPrefix = 3;
};

#endif