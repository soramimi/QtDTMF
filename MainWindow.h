#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioFormat>
#include <QAudioOutput>
#include <QIODevice>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	Ui::MainWindow *ui;
	struct Private;
	Private *m;

	void detectDTMF(int size, const int16_t *data);
	void outputAudio();
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;
private slots:
    void setTone(char c);
protected:
	void timerEvent(QTimerEvent *) override;
};

#endif // MAINWINDOW_H
