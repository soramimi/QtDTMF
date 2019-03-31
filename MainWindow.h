#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	struct Private;
	Private *m;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void outputAudio();
	void on_pushButton_clicked();
	void on_toolButton_pressed();

	void on_toolButton_released();

	void on_toolButton_1_pressed();
	void on_toolButton_1_released();
	void on_toolButton_2_pressed();
	void on_toolButton_2_released();
	void on_toolButton_3_pressed();
	void on_toolButton_3_released();
	void on_toolButton_4_pressed();
	void on_toolButton_4_released();
	void on_toolButton_5_pressed();
	void on_toolButton_5_released();
	void on_toolButton_6_pressed();
	void on_toolButton_6_released();
	void on_toolButton_7_pressed();
	void on_toolButton_7_released();
	void on_toolButton_8_pressed();
	void on_toolButton_8_released();
	void on_toolButton_9_pressed();
	void on_toolButton_9_released();
	void on_toolButton_10_pressed();
	void on_toolButton_10_released();
	void on_toolButton_11_pressed();
	void on_toolButton_11_released();
	void on_toolButton_12_pressed();
	void on_toolButton_12_released();
	void on_toolButton_a_pressed();
	void on_toolButton_a_released();
	void on_toolButton_b_pressed();
	void on_toolButton_b_released();
	void on_toolButton_c_pressed();
	void on_toolButton_c_released();
	void on_toolButton_d_pressed();
	void on_toolButton_d_released();

private:
	Ui::MainWindow *ui;
	void setTone(char c);
	void detectDTMF(int size, const int16_t *data);
protected:
	void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
