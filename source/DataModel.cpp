#include "DataModel.h"

#include <QDebug>

DataModel::DataModel(QObject *parent)
	: QObject(parent)
	, m_metaData(this)
	, m_verbEnd(this)
	, m_genus(this)
	, m_plural(this)
	, m_results(this)
{
	connect(&m_plural, &PluralModel::dataChanged,
			this, &DataModel::pluralModelChanged);

	connect(&m_metaData, &PluralModel::dataChanged, 
			this, &DataModel::metaDataChanged);
}

void DataModel::write(QJsonObject &target) const
{
	write(m_metaData, target, "MetaData");
	write(m_verbEnd, target, "VerbEnd");
	write(m_genus, target, "Genus");
	write(m_plural, target, "Plural");
}

void DataModel::read(const QJsonObject &source)
{
	read(m_metaData, source, "MetaData");
	read(m_verbEnd, source, "VerbEnd");
	read(m_genus, source, "Genus");
	read(m_plural, source, "Plural");
}
	
void DataModel::pluralModelChanged()
{
	m_results.setPluralResult(m_plural.getPoints());
}

void DataModel::metaDataChanged()
{
}
