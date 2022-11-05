#ifndef AUDIOABSTRACTIO_H
#define AUDIOABSTRACTIO_H

#include <QIODevice>
#include <QString>
#include <cstdint>
#include <deque>

class AudioDevice;
class QAudioFormat;
class QByteArray;
class QIODevice;

class AbstractAudioInput {
public:
	int RECOMMENDED_BUFFER_SIZE = 9600;
	virtual ~AbstractAudioInput() = default;
	virtual QString description() = 0;
	virtual void start(const AudioDevice &dev, const QAudioFormat &format) = 0;
	virtual void stop() = 0;
	virtual int bytesAvailable() const = 0;
	virtual int read(char *data, int maxlen) = 0;
	virtual QByteArray readAll() = 0;
};

class AbstractAudioOutput {
public:
	int RECOMMENDED_BUFFER_SIZE = 9600;
	virtual ~AbstractAudioOutput() = default;
	virtual QString description() = 0;
	virtual void start(AudioDevice const &dev, const QAudioFormat &format, QIODevice *out) = 0;
	virtual void stop() = 0;
};

#endif // AUDIOABSTRACTIO_H
