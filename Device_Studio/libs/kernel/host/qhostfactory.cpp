#include "qhostfactory.h"

#include "qabstracthost.h"

#include "qwidgethost.h"
#include "qlineedithost.h"
#include "qframehost.h"
#include "qpushbuttonhost.h"
#include "qcheckboxhost.h"
#include "qradiobuttonhost.h"
#include "qcomboboxhost.h"
#include "qdialhost.h"
#include "qsliderhost.h"
#include "qscrollbarhost.h"
#include "qlcdnumberhost.h"
#include "qlabelhost.h"
#include "qspinboxhost.h"
#include "qdoublespinboxhost.h"
#include "qtimeedithost.h"
#include "qdatehost.h"
#include "qdatetimeedithost.h"

#include "../data/qfloatdatahost.h"
#include "../data/qintdatahost.h"

#include "qformhost.h"

#include <QUuid>
#include <QVariant>

QMap<QString,QAbstractHostInfo*>     QHostFactory::m_metaMap;
QList<QAbstractHostInfo*>            QHostFactory::m_metas;

void QHostFactory::registerHost(QAbstractHostInfo *info)
{
    if(m_metaMap.contains(info->m_name) || info == NULL)
    {
        return;
    }

    m_metaMap.insert(info->m_name,info);
    m_metas.append(info);
}

QAbstractHost* QHostFactory::createHost(const QString &name)
{
    QAbstractHostInfo * info = m_metaMap.value(name);
    if(info == NULL)
    {
        return NULL;
    }

    QAbstractHost *host = (QAbstractHost*)info->m_metaObject->newInstance();
    if(host!=NULL)
    {
        host->setProperty("hostType",info->m_type);
        host->setProperty("hostName",info->m_name);
        host->init();
    }
    return host;
}

QList<QAbstractHostInfo*> QHostFactory::getHostInfo()
{
    return m_metas;
}

QAbstractHostInfo * QHostFactory::getHostInfo(const QString &name)
{
    return m_metaMap.value(name);
}

void QHostFactory::registerInnerHost()
{
    registerHost(QWidgetHost::getHostInfo());
    registerHost(QFrameHost::getHostInfo());
    registerHost(QLineEditHost::getHostInfo());
    registerHost(QPushButtonHost::getHostInfo());
    registerHost(QCheckBoxHost::getHostInfo());
    registerHost(QRadioButtonHost::getHostInfo());
    registerHost(QComboBoxHost::getHostInfo());
    registerHost(QDialHost::getHostInfo());
    registerHost(QSliderHost::getHostInfo());
    registerHost(QScrollBarHost::getHostInfo());
    registerHost(QLCDNumberHost::getHostInfo());
    registerHost(QLabelHost::getHostInfo());
    registerHost(QSpinBoxHost::getHostInfo());
    registerHost(QDoubleSpinBoxHost::getHostInfo());
    registerHost(QTimeEditHost::getHostInfo());
    registerHost(QDateHost::getHostInfo());
    registerHost(QDateTimeEditHost::getHostInfo());

    registerHost(QFormHost::getHostInfo());

    registerHost(QIntDataHost::getHostInfo());
    registerHost(QFloatDataHost::getHostInfo());
}
