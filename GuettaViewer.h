/* 
 * File:   GuettaViewer.h
 * Author: jose
 *
 * Created on 11 de octubre de 2011, 11:43
 */

#ifndef _GUETTAVIEWER_H
#define	_GUETTAVIEWER_H

#include "ui_GuettaViewer.h"

class GuettaViewer : public QWidget {
    Q_OBJECT
public:
    GuettaViewer();
    virtual ~GuettaViewer();
private:
    Ui::GuettaViewer widget;
};

#endif	/* _GUETTAVIEWER_H */

