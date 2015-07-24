/*****************************************************************************
* Model: comp.qm
* File:  ./clock.c
*
* This code has been generated by QM tool (see state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*****************************************************************************/
/*${.::clock.c} ............................................................*/
#include "qpc.h"
#include "bsp.h"
#include "alarm.h"
#include "clock.h"

#include <stdio.h>

Q_DEFINE_THIS_FILE

/* Active object class -----------------------------------------------------*/
/*${Components::AlarmClock} ................................................*/
typedef struct {
/* protected: */
    QMActive super;

/* private: */
    uint32_t current_time;
    Alarm alarm;

/* public: */
    QTimeEvt timeEvt;
} AlarmClock;

/* protected: */
static QState AlarmClock_initial(AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_timekeeping  (AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_timekeeping_e(AlarmClock * const me);
static QState AlarmClock_timekeeping_x(AlarmClock * const me);
static QState AlarmClock_timekeeping_i(AlarmClock * const me);
static QMState const AlarmClock_timekeeping_s = {
    (QMState const *)0, /* superstate (top) */
    Q_STATE_CAST(&AlarmClock_timekeeping),
    Q_ACTION_CAST(&AlarmClock_timekeeping_e),
    Q_ACTION_CAST(&AlarmClock_timekeeping_x),
    Q_ACTION_CAST(&AlarmClock_timekeeping_i)
};
static QState AlarmClock_mode24h  (AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_mode24h_e(AlarmClock * const me);
static QMState const AlarmClock_mode24h_s = {
    &AlarmClock_timekeeping_s, /* superstate */
    Q_STATE_CAST(&AlarmClock_mode24h),
    Q_ACTION_CAST(&AlarmClock_mode24h_e),
    Q_ACTION_CAST(0), /* no exit action */
    Q_ACTION_CAST(0)  /* no intitial tran. */
};
static QState AlarmClock_mode12h  (AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_mode12h_e(AlarmClock * const me);
static QMState const AlarmClock_mode12h_s = {
    &AlarmClock_timekeeping_s, /* superstate */
    Q_STATE_CAST(&AlarmClock_mode12h),
    Q_ACTION_CAST(&AlarmClock_mode12h_e),
    Q_ACTION_CAST(0), /* no exit action */
    Q_ACTION_CAST(0)  /* no intitial tran. */
};
static QState AlarmClock_final  (AlarmClock * const me, QEvt const * const e);
static QState AlarmClock_final_e(AlarmClock * const me);
static QMState const AlarmClock_final_s = {
    (QMState const *)0, /* superstate (top) */
    Q_STATE_CAST(&AlarmClock_final),
    Q_ACTION_CAST(&AlarmClock_final_e),
    Q_ACTION_CAST(0), /* no exit action */
    Q_ACTION_CAST(0)  /* no intitial tran. */
};


/* Local objects -----------------------------------------------------------*/
static AlarmClock l_alarmClock; /* the single instance of the AO */

/* Global-scope objects ----------------------------------------------------*/
QMActive * const APP_alarmClock = &l_alarmClock.super; /* "opaque" pointer */

/*${Components::AlarmClock_ctor} ...........................................*/
void AlarmClock_ctor(void) {
    AlarmClock * const me = &l_alarmClock;

    QMActive_ctor(&me->super, Q_STATE_CAST(&AlarmClock_initial));
    Alarm_ctor(&me->alarm); /* orthogonal component ctor */

    /* private time event ctor */
    QTimeEvt_ctorX(&me->timeEvt, &me->super, TICK_SIG, 0U);
}

/*..........................................................................*/
/*${Components::AlarmClock} ................................................*/
/*${Components::AlarmClock::SM} ............................................*/
static QState AlarmClock_initial(AlarmClock * const me, QEvt const * const e) {
    static struct {
        QMState const *target;
        QActionHandler act[3];
    } const tatbl_ = { /* transition-action table */
        &AlarmClock_timekeeping_s, /* target state */
        {
            Q_ACTION_CAST(&AlarmClock_timekeeping_e), /* entry */
            Q_ACTION_CAST(&AlarmClock_timekeeping_i), /* init.tran. */
            Q_ACTION_CAST(0) /* zero terminator */
        }
    };
    /* ${Components::AlarmClock::SM::initial} */
    (void)e; /* avoid compiler warning about unused parameter */
    me->current_time = 0U;

    /* (!) trigger the initial transition in the component */
    QMSM_INIT((QMsm *)&me->alarm, (QEvt *)0);
    return QM_TRAN_INIT(&tatbl_);
}
/*${Components::AlarmClock::SM::timekeeping} ...............................*/
/* ${Components::AlarmClock::SM::timekeeping} */
static QState AlarmClock_timekeeping_e(AlarmClock * const me) {
    /* periodic timeout every second */
    QTimeEvt_armX(&me->timeEvt, BSP_TICKS_PER_SEC,
                                BSP_TICKS_PER_SEC);
    return QM_ENTRY(&AlarmClock_timekeeping_s);
}
/* ${Components::AlarmClock::SM::timekeeping} */
static QState AlarmClock_timekeeping_x(AlarmClock * const me) {
    QTimeEvt_disarm(&me->timeEvt);
    return QM_EXIT(&AlarmClock_timekeeping_s);
}
/* ${Components::AlarmClock::SM::timekeeping::initial} */
static QState AlarmClock_timekeeping_i(AlarmClock * const me) {
    static struct {
        QMState const *target;
        QActionHandler act[2];
    } const tatbl_ = { /* transition-action table */
        &AlarmClock_mode24h_s, /* target state */
        {
            Q_ACTION_CAST(&AlarmClock_mode24h_e), /* entry */
            Q_ACTION_CAST(0) /* zero terminator */
        }
    };
    /* ${Components::AlarmClock::SM::timekeeping::initial} */
    return QM_TRAN_INIT(&tatbl_);
}
/* ${Components::AlarmClock::SM::timekeeping} */
static QState AlarmClock_timekeeping(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${Components::AlarmClock::SM::timekeeping::CLOCK_24H} */
        case CLOCK_24H_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[2];
            } const tatbl_ = { /* transition-action table */
                &AlarmClock_mode24h_s, /* target state */
                {
                    Q_ACTION_CAST(&AlarmClock_mode24h_e), /* entry */
                    Q_ACTION_CAST(0) /* zero terminator */
                }
            };
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /* ${Components::AlarmClock::SM::timekeeping::CLOCK_12H} */
        case CLOCK_12H_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[2];
            } const tatbl_ = { /* transition-action table */
                &AlarmClock_mode12h_s, /* target state */
                {
                    Q_ACTION_CAST(&AlarmClock_mode12h_e), /* entry */
                    Q_ACTION_CAST(0) /* zero terminator */
                }
            };
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        /* ${Components::AlarmClock::SM::timekeeping::ALARM} */
        case ALARM_SIG: {
            BSP_showMsg("Wake up!!!");
            status_ = QM_HANDLED();
            break;
        }
        /* ${Components::AlarmClock::SM::timekeeping::ALARM_SET, ALARM_ON, ALARM_OFF} */
        case ALARM_SET_SIG: /* intentionally fall through */
        case ALARM_ON_SIG: /* intentionally fall through */
        case ALARM_OFF_SIG: {
            /* (!) synchronously dispatch to the orthogonal component */
            QMSM_DISPATCH((QMsm *)&me->alarm, e);
            status_ = QM_HANDLED();
            break;
        }
        /* ${Components::AlarmClock::SM::timekeeping::TERMINATE} */
        case TERMINATE_SIG: {
            static struct {
                QMState const *target;
                QActionHandler act[3];
            } const tatbl_ = { /* transition-action table */
                &AlarmClock_final_s, /* target state */
                {
                    Q_ACTION_CAST(&AlarmClock_timekeeping_x), /* exit */
                    Q_ACTION_CAST(&AlarmClock_final_e), /* entry */
                    Q_ACTION_CAST(0) /* zero terminator */
                }
            };
            BSP_showMsg("--> final");
            status_ = QM_TRAN(&tatbl_);
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::timekeeping::mode24h} ......................*/
/* ${Components::AlarmClock::SM::timekeeping::mode24h} */
static QState AlarmClock_mode24h_e(AlarmClock * const me) {
    BSP_showMsg("*** 24-hour mode");
    (void)me; /* avoid compiler warning in case 'me' is not used */
    return QM_ENTRY(&AlarmClock_mode24h_s);
}
/* ${Components::AlarmClock::SM::timekeeping::mode24h} */
static QState AlarmClock_mode24h(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${Components::AlarmClock::SM::timekeeping::mode24h::TICK} */
        case TICK_SIG: {
            TimeEvt pe; /* temporary synchronous event for the component */

            /* roll over in 24-hr mode? */
            if (++me->current_time == 24U*60U) {
                me->current_time = 0U;
            }
            BSP_showTime24H("", me->current_time, 60U);
            pe.super.sig = TIME_SIG;
            pe.current_time = me->current_time;

            /* (!) synchronously dispatch to the orthogonal component */
            QMSM_DISPATCH(&me->alarm.super, &pe.super);
            status_ = QM_HANDLED();
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::timekeeping::mode12h} ......................*/
/* ${Components::AlarmClock::SM::timekeeping::mode12h} */
static QState AlarmClock_mode12h_e(AlarmClock * const me) {
    BSP_showMsg("*** 12-hour mode");
    (void)me; /* avoid compiler warning in case 'me' is not used */
    return QM_ENTRY(&AlarmClock_mode12h_s);
}
/* ${Components::AlarmClock::SM::timekeeping::mode12h} */
static QState AlarmClock_mode12h(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /* ${Components::AlarmClock::SM::timekeeping::mode12h::TICK} */
        case TICK_SIG: {
            TimeEvt pe; /* temporary synchronous event for the component */

            /* roll over in 12-hr mode? */
            if (++me->current_time == 12U*60U) {
                me->current_time = 0U;
            }
            BSP_showTime12H("", me->current_time, 60U);
            pe.super.sig = TIME_SIG;
            pe.current_time = me->current_time;

            /* (!) synchronously dispatch to the orthogonal component */
            QMSM_DISPATCH(&me->alarm.super, &pe.super);
            status_ = QM_HANDLED();
            break;
        }
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    return status_;
}
/*${Components::AlarmClock::SM::final} .....................................*/
/* ${Components::AlarmClock::SM::final} */
static QState AlarmClock_final_e(AlarmClock * const me) {
    QF_stop(); /* terminate the application */
    (void)me; /* avoid compiler warning in case 'me' is not used */
    return QM_ENTRY(&AlarmClock_final_s);
}
/* ${Components::AlarmClock::SM::final} */
static QState AlarmClock_final(AlarmClock * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        default: {
            status_ = QM_SUPER();
            break;
        }
    }
    (void)me; /* avoid compiler warning in case 'me' is not used */
    return status_;
}

