/*

GPL-2.0 License
Copyright (c) 2022 Ivan Chapkailo

See license: https://github.com/septimomend/pigmend-player

Author: Ivan Chapkailo (https://github.com/septimomend/)
E-mail: chapkailo.ivan@gmail.com

*/

#include "translatorinjector.h"

TranslatorInjector::TranslatorInjector()
{
}

TranslatorInjector::~TranslatorInjector()
{
}

QString TranslatorInjector::translate(const char *context, const char *sourceText, const char *disambiguation, int n) const
{
    if (context == QStringLiteral("AudioChannelEnum"))
    {
        if (!strcmp(sourceText, "Stereo"))
            return "Stereo";
        else if (!strcmp(sourceText, "Channel4"))
            return "4-channel";
        else if (!strcmp(sourceText, "Channel4_1"))
            return "4.1-channel";
        else if (!strcmp(sourceText, "Channel5"))
            return "5-channel";
        else if (!strcmp(sourceText, "Channel5_1"))
            return "5.1-channel";
        else if (!strcmp(sourceText, "AC3"))
            return "AC3 Passthrough";
        else
            return sourceText;
    }

    if (context == QStringLiteral("SupportedLanguagesEnum"))
    {
        if (!strcmp(sourceText, "EN"))
            return "English";
        else if (!strcmp(sourceText, "UA"))
            return "Ukrainian";
        else
            return sourceText;
    }

    return QTranslator::translate(context, sourceText, disambiguation, n);
}
