// Copyright 2005-2017 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "mumble_pch.hpp"

#include "TextToSpeech.h"

#include <QTextToSpeech>

class TextToSpeechPrivate : public QObject {
	Q_OBJECT

	public:
		QTextToSpeech *m_tts;
		QVector<QVoice> m_voices;
		TextToSpeechPrivate();
		~TextToSpeechPrivate();
		void say(const QString &text);
		void setVolume(int v);
};

TextToSpeechPrivate::TextToSpeechPrivate() {
	m_tts = new QTextToSpeech(this);
}

TextToSpeechPrivate::~TextToSpeechPrivate() {}

void TextToSpeechPrivate::say(const QString &text) {
	m_tts->say(text);
}

void TextToSpeechPrivate::setVolume(int volume) {
	m_tts->setVolume(volume);
}

TextToSpeech::TextToSpeech(QObject *p) : QObject(p) {
	enabled = true;
	d = new TextToSpeechPrivate();
}

TextToSpeech::~TextToSpeech() {
	delete d;
}

void TextToSpeech::say(const QString &text) {
	if (enabled)
		d->say(text);
}

void TextToSpeech::setEnabled(bool e) {
	enabled = e;
}

void TextToSpeech::setVolume(int volume) {
	d->setVolume(volume);
}

bool TextToSpeech::isEnabled() const {
	return enabled;
}