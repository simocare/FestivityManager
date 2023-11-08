#ifndef MODIFICAPIETANZAGRIGLIEDIALOG_H
#define MODIFICAPIETANZAGRIGLIEDIALOG_H

#include "modificaProdottoDialog.h"

class modificaPietanzaGriglieDialog : public modificaProdottoDialog
{
    Q_OBJECT

public:
    modificaPietanzaGriglieDialog(prodotto* existingProd, QWidget *parent = nullptr);

    float getPesoPorzione() const;

private:
    QLineEdit *pesoPorzioneLineEdit;

    pietanza_griglie *pg;

private slots:
    virtual void accept() override;
    virtual void applyChanges() override;
};

#endif // MODIFICAPIETANZAGRIGLIEDIALOG_H
