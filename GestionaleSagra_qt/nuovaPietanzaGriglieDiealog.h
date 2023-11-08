#ifndef NUOVAPIETANZAGRIGLIEDIEALOG_H
#define NUOVAPIETANZAGRIGLIEDIEALOG_H

#include "nuovoProdottoDialog.h"

class nuovaPietanzaGriglieDialog : public nuovoProdottoDialog
{
    Q_OBJECT

public:
    nuovaPietanzaGriglieDialog(QWidget *parent = nullptr);

    // Aggiungi solo il metodo per ottenere il campo specifico per pietanza griglie
    float getPesoPorzione() const;

private:
    QLineEdit *pesoPorzioneLineEdit;


private slots:
    virtual void accept() override;
};

#endif // NUOVAPIETANZAGRIGLIEDIEALOG_H
