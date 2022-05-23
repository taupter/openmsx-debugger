#ifndef PALETTEPATCH_H
#define PALETTEPATCH_H

#include <QPushButton>
#include "MSXPalette.h"
#include <cstdint>

class PalettePatch : public QPushButton
{
    Q_OBJECT

public:
    PalettePatch(QWidget* parent, int palNr);

public slots:
    void setMSXPalette(MSXPalette* pal);
    void setHighlightTest(int colorNr);
    void paletteChanged();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QRgb myColor = Qt::green;
    bool isSelected = false;
    int msxPalNr;
    MSXPalette* myPal = nullptr;
};

#endif // PALETTEPATCH_H
