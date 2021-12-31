#include "StyleHelper.h"
#include "ui_MainWindow.h"

#include "config/AppConfig.h"
#include "interface/fragment/SettingsFragment.h"
#include "MainWindow.h"
#include <eeleditor.h>

#include <QApplication>
#include <QTextStream>

StyleHelper::StyleHelper(QObject *host)
{
	m_objhost = host;
}

void StyleHelper::SetStyle()
{
	MainWindow *m_host = qobject_cast<MainWindow*>(m_objhost);

    QApplication::setStyle(AppConfig::instance().get<QString>(AppConfig::Theme));

    QString     color_palette = AppConfig::instance().get<QString>(AppConfig::ThemeColors);
	auto        palettes      = ColorStyleProvider::TABLE();

	if (color_palette == "custom")
	{
		QColor     base          = QColor(loadColor(0, 0), loadColor(0, 1), loadColor(0, 2));
		QColor     background    = QColor(loadColor(1, 0), loadColor(1, 1), loadColor(1, 2));
		QColor     foreground    = QColor(loadColor(2, 0), loadColor(2, 1), loadColor(2, 2));
		QColor     selection     = QColor(loadColor(3, 0), loadColor(3, 1), loadColor(3, 2));
		QColor     disabled      = QColor(loadColor(4, 0), loadColor(4, 1), loadColor(4, 2));
		QColor     selectiontext = QColor(255 - loadColor(3, 0), 255 - loadColor(3, 1), 255 - loadColor(3, 2));
        ColorStyle cs            = ColorStyle(AppConfig::instance().get<bool>(AppConfig::ThemeColorsCustomWhiteIcons),
		                                      base, background, foreground, selection, selectiontext, disabled);

		setPalette(cs);
        loadIcons(AppConfig::instance().get<bool>(AppConfig::ThemeColorsCustomWhiteIcons));
	}
	else if (palettes.contains(color_palette))
	{
		ColorStyle currentColorStyle = palettes[color_palette];
		setPalette(currentColorStyle);
		loadIcons(currentColorStyle.useWhiteIcons);
	}
	else
	{
		loadIcons(false);
		QApplication::setPalette(m_host->style()->standardPalette());
	}

    QFile f(":/styles/default.qss");

    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

	emit styleChanged();
}

void StyleHelper::setPalette(const ColorStyle &s)
{
	QPalette *palette = new QPalette();
	palette->setColor(QPalette::Window,          s.background);
	palette->setColor(QPalette::WindowText,      s.foreground);
	palette->setColor(QPalette::Base,            s.base);
	palette->setColor(QPalette::AlternateBase,   s.background);
	palette->setColor(QPalette::ToolTipBase,     s.background);
	palette->setColor(QPalette::ToolTipText,     s.foreground);
	palette->setColor(QPalette::Text,            s.foreground);
	palette->setColor(QPalette::Button,          s.background);
	palette->setColor(QPalette::ButtonText,      s.foreground);
	palette->setColor(QPalette::BrightText,      Qt::red);
	palette->setColor(QPalette::Link,            QColor(42, 130, 218));
	palette->setColor(QPalette::Highlight,       s.selection);
    palette->setColor(QPalette::HighlightedText, s.selectiontext);
    palette->setColor(QPalette::Disabled, QPalette::Text, s.disabled);
    palette->setColor(QPalette::Disabled, QPalette::WindowText, s.disabled);
    palette->setColor(QPalette::Disabled, QPalette::ToolTipText, s.disabled);
    palette->setColor(QPalette::Disabled, QPalette::ButtonText, s.disabled);
    qApp->setPalette(*palette);
	qApp->setStyleSheet(QString(R"(QFrame[frameShape="4"], QFrame[frameShape="5"]{
                            color: gray;
                        }
                        *::disabled {
                        color: %1;
                        }
                        QToolButton::disabled{
                        color: %1;

                        }
                        QComboBox::disabled{
                        color: %1;
                        })").arg(s.disabled.name()));
}

void StyleHelper::loadIcons(bool white)
{
    emit iconColorChanged(white);
}

int StyleHelper::loadColor(int index,
                           int rgb_index)
{
    QStringList elements = AppConfig::instance().get<QString>(AppConfig::ThemeColorsCustom).split(';');

	if (elements.length() < 5 || elements[index].split(',').size() < 3)
	{
		if (index == 0)
		{
			return 25;
		}
		else if (index == 1)
		{
			return 53;
		}
		else if (index == 2)
		{
			return 255;
		}
		else if (index == 3)
		{
			if (rgb_index == 0)
			{
				return 42;
			}
			else if (rgb_index == 1)
			{
				return 130;
			}
			else if (rgb_index == 2)
			{
				return 218;
			}
		}
		else if (index == 4)
		{
			return 85;
		}
	}

	QStringList rgb = elements[index].split(',');
	return rgb[rgb_index].toInt();
}
