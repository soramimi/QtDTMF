#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SineCurve.h"
#include "pi2.h"
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
	bool playing = false;
	int volume = 5000;
	int sample_fq = 8000;
	std::shared_ptr<QAudioOutput> audio_output;
	QIODevice *device = nullptr;
	double dtmf_levels[8] = {};
	SineCurve sine_curve_lo;
	SineCurve sine_curve_hi;
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m(new Private)
{
	ui->setupUi(this);

	QAudioFormat format;
	format.setByteOrder(QAudioFormat::LittleEndian);
	format.setChannelCount(1);
	format.setCodec("audio/pcm");
	format.setSampleRate(m->sample_fq);
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);

	m->audio_output = std::make_shared<QAudioOutput>(format);
	m->audio_output->setBufferSize(2000);
	m->device = m->audio_output->start();

	startTimer(10);
}

MainWindow::~MainWindow()
{
	delete m;
	delete ui;
}

void MainWindow::detectDTMF(int size, int16_t const *data)
{
	for (int i = 0; i < 8; i++) {
		m->dtmf_levels[i] = goertzel(size, data, m->sample_fq, dtmf_fq[i]);
	}
}

void MainWindow::outputAudio()
{
	if (!m->playing) {
		for (int i = 0; i < 8; i++) {
			m->dtmf_levels[i] = 0;
		}
		return;
	}

	std::vector<int16_t> buf;

	while (1) {
		int n = m->audio_output->bytesFree();
		n /= sizeof(int16_t);
		const int N = 96;
		if (n < N) return;

		buf.resize(n);

		for (int i = 0; i < n; i++) {
			double a = m->sine_curve_lo.next();
			double b = m->sine_curve_hi.next();
			buf[i] = (int16_t)((a + b) * m->volume);
		}

		m->device->write((char const *)&buf[0], n * sizeof(int16_t));

		detectDTMF(buf.size(), &buf[0]);
	}
}

void MainWindow::timerEvent(QTimerEvent *)
{
	outputAudio();

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

	m->sine_curve_lo.tone_fq = tone_fq_lo;
	m->sine_curve_hi.tone_fq = tone_fq_hi;
}

void MainWindow::play(char c)
{
	if (c < 0) {
		m->playing = false;
	} else {
		setTone(c);
		m->playing = true;
	}
}

void MainWindow::on_toolButton_1_pressed()
{
	play('1');
}

void MainWindow::on_toolButton_1_released()
{
	play(-1);
}

void MainWindow::on_toolButton_2_pressed()
{
	play('2');
}

void MainWindow::on_toolButton_2_released()
{
	play(-1);
}

void MainWindow::on_toolButton_3_pressed()
{
	play('3');
}

void MainWindow::on_toolButton_3_released()
{
	play(-1);
}

void MainWindow::on_toolButton_4_pressed()
{
	play('4');
}

void MainWindow::on_toolButton_4_released()
{
	play(-1);
}

void MainWindow::on_toolButton_5_pressed()
{
	play('5');
}

void MainWindow::on_toolButton_5_released()
{
	play(-1);
}

void MainWindow::on_toolButton_6_pressed()
{
	play('6');
}

void MainWindow::on_toolButton_6_released()
{
	play(-1);
}

void MainWindow::on_toolButton_7_pressed()
{
	play('7');
}

void MainWindow::on_toolButton_7_released()
{
	play(-1);
}

void MainWindow::on_toolButton_8_pressed()
{
	play('8');
}

void MainWindow::on_toolButton_8_released()
{
	play(-1);
}

void MainWindow::on_toolButton_9_pressed()
{
	play('9');
}

void MainWindow::on_toolButton_9_released()
{
	play(-1);
}

void MainWindow::on_toolButton_10_pressed()
{
	play('*');
}

void MainWindow::on_toolButton_10_released()
{
	play(-1);
}

void MainWindow::on_toolButton_11_pressed()
{
	play('0');
}

void MainWindow::on_toolButton_11_released()
{
	play(-1);
}

void MainWindow::on_toolButton_12_pressed()
{
	play('#');
}

void MainWindow::on_toolButton_12_released()
{
	play(-1);
}

void MainWindow::on_toolButton_a_pressed()
{
	play('A');
}

void MainWindow::on_toolButton_a_released()
{
	play(-1);
}

void MainWindow::on_toolButton_b_pressed()
{
	play('B');
}

void MainWindow::on_toolButton_b_released()
{
	play(-1);
}

void MainWindow::on_toolButton_c_pressed()
{
	play('C');
}

void MainWindow::on_toolButton_c_released()
{
	play(-1);
}

void MainWindow::on_toolButton_d_pressed()
{
	play('D');
}

void MainWindow::on_toolButton_d_released()
{
	play(-1);
}

