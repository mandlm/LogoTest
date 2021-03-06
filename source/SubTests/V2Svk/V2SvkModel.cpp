#include "V2SvkModel.h"

#include <regex>

V2SvkModel::V2SvkModel(QObject *parent)
    : PrintableModel(parent)
{
}

void V2SvkModel::printTests(QPainter &painter) const
{
	painter.setFont(tableFont());
	painter.setPen(tablePen());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	auto v2TestIndices = v2Tests();
	auto svkTestIndices = svkTests();

	double x = 0;
	double y = 0;
	auto testIndex = 0;
	for (const auto &test : m_tests)
	{
		double rowHeaderWidth = headerWidthFactor() * width;
		double resultCellWidth = (test.size() > 8 ? 0.5 : 1) * cellWidthFactor() * width;
		double rowHeight = height;

		QString testName = test.name();
		if (testName.length() > 20)
		{
			testName = QString::fromStdString(
			    std::regex_replace(testName.toStdString(), std::regex("[\\s-]"), "\n"));
		}

		if (testIndex == 0)
		{
			drawTextSquare(painter, {x, y, rowHeaderWidth, 2 * rowHeight}, testName);
			x += rowHeaderWidth;

			std::vector<std::pair<std::string, unsigned int>> columnHeaders;
			for (const auto &item : test.items())
			{
				const auto &itemText = item.getText();
				if (!columnHeaders.empty() && columnHeaders.back().first == itemText)
				{
					columnHeaders.back().second++;
				}
				else
				{
					columnHeaders.emplace_back(itemText, 1);
				}
			}

			for (const auto &columnHeader : columnHeaders)
			{
				double cellWidth = columnHeader.second * resultCellWidth;
				drawTextSquare(painter, {x, y, cellWidth, rowHeight}, columnHeader.first.c_str());
				x += cellWidth;
			}
			x = rowHeaderWidth;
			y += rowHeight;
		}
		else
		{
			drawTextSquare(painter, {x, y, rowHeaderWidth, rowHeight}, testName);
			x += rowHeaderWidth;
		}

		unsigned int emptyItemsStack = 0;
		for (const auto &item : test.items())
		{
			if (item.getText().empty())
			{
				emptyItemsStack++;
			}
			else
			{
				if (emptyItemsStack > 0)
				{
					drawGreySquare(painter, {x - emptyItemsStack * resultCellWidth, y,
					                         emptyItemsStack * resultCellWidth, rowHeight});
					emptyItemsStack = 0;
				}

				drawCheckSquare(painter, {x, y, resultCellWidth, rowHeight}, item.isChecked());
			}
			x += resultCellWidth;
		}
		if (emptyItemsStack > 0)
		{
			drawGreySquare(painter, {x - emptyItemsStack * resultCellWidth, y,
			                         emptyItemsStack * resultCellWidth, rowHeight});
			emptyItemsStack = 0;
		}

		if (v2TestIndices.find(testIndex) != v2TestIndices.end())
		{
			drawResultSquare(painter, y, false, test.getPoints());
		}

		if (svkTestIndices.find(testIndex) != svkTestIndices.end())
		{
			drawResultSquare(painter, y, true, test.getPoints());
		}

		x = 0;
		y += rowHeight;

		testIndex++;
	}

	x = 0;
	y += height;

	painter.translate(0, y);
}

void V2SvkModel::printSummary(QPainter &painter, unsigned int v2Points, unsigned int svkPoints)
{
	painter.setFont(PrintableModel::tableFont());
	painter.setPen(PrintableModel::tablePen());

	auto width = painter.device()->width();
	auto height = 1.5 * painter.fontMetrics().lineSpacing();

	painter.drawText(0, 0, 0.91 * width, height, Qt::AlignRight | Qt::AlignVCenter,
	                 "Rohwertpunkte Total:");

	painter.setPen(resultPen());
	drawNumberSquare(painter, 0.93 * width, 0, v2Points);
	drawNumberSquare(painter, 0.97 * width, 0, svkPoints);

	painter.translate(0, 3 * height);
}

