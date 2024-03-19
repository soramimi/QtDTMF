#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Generator.h"
#include "pi2.h"
#include "Audio.h"
#include <QDebug>
#include <QKeyEvent>
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
	Generator generator;
	QAudioFormat audio_format;
	AudioOutput audio_output;
	double dtmf_levels[8] = {};
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m(new Private)
{
	ui->setupUi(this);

	m->audio_format = Audio::defaultAudioFormat();
	m->audio_format.setChannelCount(1);
	m->audio_format.setSampleRate(m->generator.sampleRate());

	m->generator.start(m->audio_format.sampleRate());
	m->audio_output.start(AudioDevices::defaultAudioOutputDevice(), m->audio_format, &m->generator);

	connect(&m->generator, &Generator::notify, [&](int n, int16_t const *p){
		detectDTMF(n, p);
	});

	startTimer(10);

    const auto buttons = findChildren<QToolButton *>();
    for (auto button : buttons) {
        connect(button, &QToolButton::pressed, [button, this]() { setTone(button->text().at(0).toLatin1()); });
        connect(button, &QToolButton::released, [this]() { setTone(0); });
    }
}

MainWindow::~MainWindow()
{
	m->generator.stop();
	delete m;
	delete ui;
}

void MainWindow::detectDTMF(int size, int16_t const *data)
{
	for (int i = 0; i < 8; i++) {
		m->dtmf_levels[i] = goertzel(size, data, m->audio_format.sampleRate(), dtmf_fq[i]);
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
		pb[i]->setValue((int)m->dtmf_levels[i]);
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    const auto text = event->text();
    if (!text.isEmpty())
        setTone(text.at(0).toUpper().toLatin1());
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
    setTone(0);
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

	m->generator.setTone(tone_fq_lo, tone_fq_hi);
}
