#ifndef NUOVAPIETANZACUCINADIALOG_H
#define NUOVAPIETANZACUCINADIALOG_H

#include "nuovoProdottoDialog.h"

class nuovaPietanzaCucinaDialog : public nuovoProdottoDialog
{
    Q_OBJECT

public:
    nuovaPietanzaCucinaDialog(QWidget *parent = nullptr);

private slots:
    virtual void accept() override;
};

#endif // NUOVAPIETANZACUCINADIALOG_H
