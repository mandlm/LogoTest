#include "CheckableTestModel.h"

#include <QJsonArray>
#include <QSize>
#include <QDebug>

CheckableTestModel::CheckableTestModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int CheckableTestModel::rowCount(const QModelIndex &) const
{
	return static_cast<int>(m_tests.size());
}

int CheckableTestModel::columnCount(const QModelIndex &) const
{
	int columnCount = 0;

	for (const auto &test : m_tests)
	{
		columnCount = std::max(columnCount, static_cast<int>(test.size()));
	}

	return columnCount;
}

QVariant CheckableTestModel::data(const QModelIndex &index, int role) const
{
	if (!isValidIndex(index))
	{
		return {};
	}

	try
	{
		auto &item = getItem(index);

		switch (role)
		{
			case Qt::DisplayRole:
			{
				return item.getText().c_str();
			}
			case Qt::CheckStateRole:
			{
				return item.isChecked() ? Qt::Checked : Qt::Unchecked;
			}
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "CheckableTestModel::data" << index << e.what();
	}

	return {};
}

Qt::ItemFlags CheckableTestModel::flags(const QModelIndex &index) const
{
	if (isValidIndex(index))
	{
		return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
	}

	return Qt::NoItemFlags;
}

bool CheckableTestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!isValidIndex(index))
	{
		return false;
	}

	try
	{
		if (role == Qt::CheckStateRole)
		{
			auto &item = getItem(index);
			item.setState(value.toBool());
			emit dataChanged(index, index);
			return true;
		}
	}
	catch (std::runtime_error &e)
	{
		qDebug() << "CheckableTestModel::setData" << index << e.what();
	}

	return false;
}

QVariant CheckableTestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch (orientation)
	{
		case Qt::Vertical:
		{
			switch (role)
			{
				case Qt::DisplayRole:
				{
					if (section < m_tests.size())
					{
						return m_tests.at(section).name();
					}
				}
				case Qt::SizeHintRole:
				{
					return QSize(200, 0);
				}
			}
			break;
		}
		default:
			break;
	}

	return QAbstractTableModel::headerData(section, orientation, role);
}

bool CheckableTestModel::isValidIndex(const QModelIndex &index) const
{
	if (index.row() < m_tests.size())
	{
		return index.column() < m_tests.at(index.row()).size();
	}

	return false;
}

CheckableItems &CheckableTestModel::getItems(const QModelIndex &index)
{
	if (index.row() < m_tests.size())
	{
		return m_tests.at(index.row()).items();
	}

	throw std::runtime_error("invalid index");
}

const CheckableItems &CheckableTestModel::getItems(const QModelIndex &index) const
{
	if (index.row() < m_tests.size())
	{
		return m_tests.at(index.row()).items();
	}

	throw std::runtime_error("invalid index");
}

CheckableItem &CheckableTestModel::getItem(const QModelIndex &index)
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}

const CheckableItem &CheckableTestModel::getItem(const QModelIndex &index) const
{
	auto &items = getItems(index);
	if (index.column() < items.size())
	{
		return items.at(index.column());
	}

	throw std::runtime_error("invalid index");
}

unsigned int CheckableTestModel::getPoints() const
{
	unsigned int points = 0;

	for (const auto &test : m_tests)
	{
		for (const auto &item : test.items())
		{
			points += item.points();
		}
	}

	return points;
}

QString CheckableTestModel::getTitle() const
{
	return m_title;
}
