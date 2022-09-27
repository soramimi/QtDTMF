#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Generator.h"
#include "SineCurve.h"
#include "pi2.h"
#include "MyAudioOutput6.h"
#include <QAudioFormat>
#include <QAudioSink>
#include <QMediaDevices>
#include <memory>

static const int dtmf_fq[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };

double goertzel(int size, int16_t const *data, int sample_fq, int detect_fq)
{
	double omega = PI2 * detect_fq / sample_fq;
	double sine = sin(omega);
	double cosine = cos(omega);
	double coeff = cosine * 2;
	double q0 = 0;
	double q1 = 0;
	double q2 = 0;

	for (int i = 0; i < size; i++) {
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}

	double real = (q1 - q2 * cosine) / (size / 2.0);
	double imag = (q2 * sine) / (size / 2.0);

	return sqrt(real * real + imag * imag);
}

struct MainWindow::Private {
	double dtmf_levels[8] = {};
	std::shared_ptr<Generator> generator;
	MyAudioOutput6 audio_output;
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m(new Private)
{
	ui->setupUi(this);

	m->generator = std::make_shared<Generator>();
	m->generator->start();

	m->audio_output.start(m->generator.get());

	connect(m->generator.get(), &Generator::notify, [&](int n, int16_t const *p){
		detectDTMF(n, p);
	});

	startTimer(10);
}

MainWindow::~MainWindow()
{
	m->generator->stop();
	delete m;
	delete ui;
}

void MainWindow::detectDTMF(int size, int16_t const *data)
{
	for (int i = 0; i < 8; i++) {
		m->dtmf_levels[i] = goertzel(size, data, m->audio_output.sample_fq, dtmf_fq[i]);
	}
}

void MainWindow::timerEvent(QTimerEvent *)
{
	QProgressBar *pb[8] = {
		ui->progressBar_1,
		ui->progressBar_2,
		ui->progressBar_3,
		ui->progressBar_4,
		ui->progressBar_5,
		ui->progressBar_6,
		ui->progressBar_7,
		ui->progressBar_8,
	};

	for (int i = 0; i < 8; i++) {
		pb[i]->setRange(0, 10000);
		pb[i]->setValue(m->dtmf_levels[i]);
	}
}

void MainWindow::setTone(char c)
{
	int tone_fq_lo = 0;
	int tone_fq_hi = 0;
	switch (c) {
	case '1':
	case '2':
	case '3':
	case 'A':
		tone_fq_lo = 697;
		break;
	case '4':
	case '5':
	case '6':
	case 'B':
		tone_fq_lo = 770;
		break;
	case '7':
	case '8':
	case '9':
	case 'C':
		tone_fq_lo = 852;
		break;
	case '*':
	case '0':
	case '#':
	case 'D':
		tone_fq_lo = 941;
		break;
	}

	switch (c) {
	case '1':
	case '4':
	case '7':
	case '*':
		tone_fq_hi = 1209;
		break;
	case '2':
	case '5':
	case '8':
	case '0':
		tone_fq_hi = 1336;
		break;
	case '3':
	case '6':
	case '9':
	case '#':
		tone_fq_hi = 1477;
		break;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
		tone_fq_hi = 1633;
		break;
	}

	m->generator->setTone(tone_fq_lo, tone_fq_hi);
}

void MainWindow::on_toolButton_1_pressed()
{
	setTone('1');
}

void MainWindow::on_toolButton_1_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_2_pressed()
{
	setTone('2');
}

void MainWindow::on_toolButton_2_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_3_pressed()
{
	setTone('3');
}

void MainWindow::on_toolButton_3_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_4_pressed()
{
	setTone('4');
}

void MainWindow::on_toolButton_4_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_5_pressed()
{
	setTone('5');
}

void MainWindow::on_toolButton_5_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_6_pressed()
{
	setTone('6');
}

void MainWindow::on_toolButton_6_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_7_pressed()
{
	setTone('7');
}

void MainWindow::on_toolButton_7_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_8_pressed()
{
	setTone('8');
}

void MainWindow::on_toolButton_8_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_9_pressed()
{
	setTone('9');
}

void MainWindow::on_toolButton_9_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_10_pressed()
{
	setTone('*');
}

void MainWindow::on_toolButton_10_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_11_pressed()
{
	setTone('0');
}

void MainWindow::on_toolButton_11_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_12_pressed()
{
	setTone('#');
}

void MainWindow::on_toolButton_12_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_a_pressed()
{
	setTone('A');
}

void MainWindow::on_toolButton_a_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_b_pressed()
{
	setTone('B');
}

void MainWindow::on_toolButton_b_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_c_pressed()
{
	setTone('C');
}

void MainWindow::on_toolButton_c_released()
{
	setTone(0);
}

void MainWindow::on_toolButton_d_pressed()
{
	setTone('D');
}

void MainWindow::on_toolButton_d_released()
{
	setTone(0);
}

