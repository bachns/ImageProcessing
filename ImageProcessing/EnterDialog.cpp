#include "EnterDialog.h"

EnterDialog::EnterDialog(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::EnterDialog)
{
	ui->setupUi(this);
}

void EnterDialog::setLabel(const QString& label) const {
	ui->label->setText(label);
}

void EnterDialog::setRange(int min, int max) const {
	ui->spinBox->setMinimum(min);
	ui->spinBox->setMaximum(max);
	ui->horizontalSlider->setMinimum(min);
	ui->horizontalSlider->setMaximum(max);
}

void EnterDialog::setDefaultValue(int value) const {
	ui->spinBox->setValue(value);
}

int EnterDialog::getValue() const {
	return ui->spinBox->value();
}

EnterDialog::~EnterDialog()
{
	delete ui;
}
