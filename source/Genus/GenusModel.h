#pragma once

#include "CheckableItem.h"
#include "CheckableItems.h"

#include <QAbstractTableModel>

class GenusModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	CheckableItems m_tiere = {{0, {"Tiger"}}, {1, {"Bär"}}, {2, {"Katze"}},
		{3, {"Pferd"}}, {4, {"Gans"}}, {5, {"Elefant"}}, {6, {"Katze"}},
		{7, {"Hund"}}};

	CheckableItems m_futter = {{0, {"Salat"}}, {1, {"Fleisch"}},
		{2, {"Knocken"}}, {3, {"Banane"}}, {4, {"Apfel"}}, {5, {"Möhre"}},
		{6, {"Honig"}}, {7, {"Zucker"}}};

	CheckableItems m_zirkus = {
		{0, {"Kiste"}}, {1, {"Holz"}}, {2, {"Vorhang"}}, {3, {"Baum"}}};

public:
	GenusModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(
		const QModelIndex &index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	bool setData(const QModelIndex &index, const QVariant &value,
		int role = Qt::EditRole) override;

	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;

	void write(QJsonObject &json) const;
	void read(const QJsonObject &json);

private:
	bool isValidIndex(const QModelIndex &index) const;

	CheckableItems &getItems(const QModelIndex &index);
	const CheckableItems &getItems(const QModelIndex &index) const;

	CheckableItem &getItem(const QModelIndex &index);
	const CheckableItem &getItem(const QModelIndex &index) const;
};
