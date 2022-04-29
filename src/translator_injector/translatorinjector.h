/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#ifndef TRANSLATORINJECTOR_H
#define TRANSLATORINJECTOR_H

#include <QObject>
#include <QTranslator>

class TranslatorInjector : public QTranslator
{
public:
    TranslatorInjector();
    ~TranslatorInjector();

protected:
    QString translate(const char *context, const char *sourceText, const char *disambiguation, int n) const override;
};

#endif // TRANSLATORINJECTOR_H
