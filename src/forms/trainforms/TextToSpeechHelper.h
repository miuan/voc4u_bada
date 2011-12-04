/*
 * TextToSpeechHelper.h
 *
 *  Created on: 4.12.2011
 *      Author: m1uan
 */

#ifndef TEXTTOSPEECHHELPER_H_
#define TEXTTOSPEECHHELPER_H_

#include <FBase.h>
#include <FUix.h>

using namespace Osp::Base;
using namespace Osp::Uix;

/*
 * must be static because using TextToSpeech
 *
 */
class TextToSpeechHelper: public ITextToSpeechEventListener
{
private:
	TextToSpeech *__pTextToSpeech;

	String __text;
public:
	TextToSpeechHelper();
	virtual ~TextToSpeechHelper();
	void Play(String text);

protected:
	// ITextToSpeechEventListener
	virtual void OnTextToSpeechErrorOccurred(Osp::Uix::TextToSpeechError error);
	virtual void OnTextToSpeechStatusChanged(Osp::Uix::TextToSpeechStatus status);
};

#endif /* TEXTTOSPEECHHELPER_H_ */
