#pragma once

#include <QMainWindow>

#include <memory>

class DataModel;
class QDataWidgetMapper;

namespace Ui {
class MainWindow;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow *ui;
	std::unique_ptr<DataModel> m_dataModel;
    QString m_filename;

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

public slots:
	void newFile();
	void openFile();
    void saveFile();
	void saveFileAs();

private:
    void saveFile(const QString &filename);
};
