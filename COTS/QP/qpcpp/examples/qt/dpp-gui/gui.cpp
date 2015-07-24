//****************************************************************************
// Product: QP/C++ GUI example for Qt5
// Last Updated for Version: 5.0.0
// Date of the Last Update:  Aug 12, 2012
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) 2002-2012 Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// Quantum Leaps Web sites: http://www.quantum-leaps.com
//                          http://www.state-machine.com
// e-mail:                  info@quantum-leaps.com
//****************************************************************************
#include <QtWidgets>
#include "gui.h"
//-----------------
#include "qp_port.h"
#include "dpp.h"
#include "bsp.h"

Q_DEFINE_THIS_FILE

//............................................................................
static Gui *l_instance;

//............................................................................
Gui::Gui(QWidget *parent)
    : QDialog(parent)
{
    l_instance = this;   // initialize the instance (Singleton)
    setupUi(this);
    setWindowTitle(tr("Dining Philosophers"));

    BSP_randomSeed(123U);
}
//............................................................................
Gui *Gui::instance() {
    return l_instance;
}
//............................................................................
void Gui::onPausePressed() { // slot
    static QP::QEvt const e(DPP::PAUSE_SIG);
    QP::QF::PUBLISH(&e, (void *)0);
    qDebug("onPausePressed");
}
//............................................................................
void Gui::onPauseReleased() { // slot
    static QP::QEvt const e(DPP::SERVE_SIG);
    QP::QF::PUBLISH(&e, (void *)0);
    qDebug("onPauseReleased");
}
//............................................................................
void Gui::onQuit() { // slot
    static QP::QEvt const e(DPP::TERMINATE_SIG);
    QP::QF::PUBLISH(&e, (void *)0);
    qDebug("onQuit");
}
