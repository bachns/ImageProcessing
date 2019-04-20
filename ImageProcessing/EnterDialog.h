#ifndef ENTERDIALOG_H
#define ENTERDIALOG_H

#include <QDialog>
#include "ui_EnterDialog.h"

class EnterDialog : public QDialog
{
	Q_OBJECT

public:
	explicit EnterDialog(QWidget *parent = nullptr);
	void setLabel(const QString& label) const;
	void setRange(int min, int max) const;
	void setDefaultValue(int value) const;
	int getValue() const;
	~EnterDialog();

private:
	Ui::EnterDialog *ui;
};


#endif