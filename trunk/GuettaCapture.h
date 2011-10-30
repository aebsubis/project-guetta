/* 
 * File:   GuettaViewer.h
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */

#ifndef _GuettaCapture_H
#define	_GuettaCapture_H

#include "ui_GuettaCapture.h"

class GuettaCapture : public QWidget {
    Q_OBJECT
public:
    GuettaCapture();
    virtual ~GuettaCapture();
private:
    Ui::GuettaCapture widget;
};

#endif	/* _GUETTAVIEWER_H */

