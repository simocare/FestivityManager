#ifndef MODIFICAPIETANZACUCINADIALOG_H
#define MODIFICAPIETANZACUCINADIALOG_H

#include "modificaProdottoDialog.h"

class modificaPietanzaCucinaDialog : public modificaProdottoDialog
{
    Q_OBJECT

public:
    modificaPietanzaCucinaDialog(prodotto* existingProd, QWidget *parent = nullptr);

private:
    pietanza_cucina *pc;

private slots:
    virtual void accept() override;
    virtual void applyChanges() override;
};

#endif // MODIFICAPIETANZACUCINADIALOG_H
