/****************************************************************
 * definitions.h
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QtGlobal>
#include <QString>
#include <QDateTime>
#include "atomicintbool.h"

#define DEFAULT_WAIT_TIME_SEC   100

#define DEFAULT_Z_JOG_RATE      260.0
#define DEFAULT_Z_LIMIT_RATE    100.0
#define DEFAULT_XY_RATE         2000.0

#define DEFAULT_GRBL_LINE_BUFFER_LEN    50
#define DEFAULT_CHAR_SEND_DELAY_MS      0

#define MM_IN_AN_INCH           25.4
#define PRE_HOME_Z_ADJ_MM       5.0

#define REQUEST_CURRENT_POS             "?"
/// T4
#define PAUSE_COMMAND_V08c              "M1"
//#define SETTINGS_COMMAND_V08a           "$"
#define HELP_COMMAND_V08c               "$"
#define SETTINGS_COMMAND_V08c           "$$"
#define SETTINGS_COMMAND_V$           	"$"
#define SETTINGS_COMMAND_V$$           	"$$"
#define HOMING_CYCLE_COMMAND			"$H"
#define CYCLE_START_COMMAND				"~"
#define FEED_FOLD_COMMAND				"!"

/// T3
#define REQUEST_MODE_CHECK       		"$C"
/// T4
#define REQUEST_PARSER_STATE_V08c       "$G"
#define REQUEST_PARAMETERS_V08c			"$#"
#define REQUEST_INFO_V09g				"$I"
#define REQUEST_STARTUP_BLOCKS			"$N"

#define SET_UNLOCK_STATE_V08c           "$X"
#define REQUEST_PARSER_STATE_V$$       	"$G"
#define SET_UNLOCK_STATE_V$$           	"$X"

#define REGEXP_SETTINGS_LINE    "(\\d+)\\s*=\\s*([\\w\\.]+)\\s*\\(([^\\)]*)\\)"

#define LOG_MSG_TYPE_DIAG       "DIAG"
#define LOG_MSG_TYPE_STATUS     "STATUS"

/// LETARTARE   : one axis choice U or V or W or A or B or C
#define FOURTH_AXIS_U   'U'
#define FOURTH_AXIS_V   'V'
#define FOURTH_AXIS_W   'W'
/// <--
#define FOURTH_AXIS_A   'A'
#define FOURTH_AXIS_B   'B'
#define FOURTH_AXIS_C   'C'
/// T4 : planes G17, G18, G19
#define NO_PLANE	-1
#define PLANE_XY_G17	0   // G17
#define PLANE_YZ_G18	2   // G18
#define PLANE_ZX_G19	1   // G19
/// T4 feedrate
#define SPEED_DEFAULT	0	// mm per mn
#define SPEED_MIN		0
#define SPEED_MAX		24000.0
#define SPEED_FAST		2000.0
/// T4 tolerance
#define TOL_MM			0.01
#define TOL_MM_STEP     0.01
#define TOL_MM_MIN		0.01
#define TOL_MM_MAX		1.0
#define TOL_IN			0.0004
#define TOL_IN_STEP		0.0004
#define TOL_IN_MIN		0.0004
#define TOL_IN_MAX		0.04
/// TA min, max X, Y, Z   mm
#define MIN_X	0.0
#define MIN_Y	0.0
#define MIN_Z	0.0
#define MAX_X	1000.0   // 0.5 m
#define MAX_Y	1000.0
#define MAX_Z	200.0

#define PREQ_ALWAYS           "always"
#define PREQ_ALWAYS_NO_IDLE_CHK     "alwaysWithoutIdleChk"
#define PREQ_NOT_WHEN_MANUAL  "notWhenManual"

#define DEFAULT_POS_REQ_FREQ_SEC    1.0
#define DEFAULT_POS_REQ_FREQ_MSEC   1000

#define POS_REQ 	0
#define POS_SYNC 	1
#define POS_NO		2

extern AtomicIntBool g_enableDebugLog;

void status(const char *str, ...);
void diag(const char *str, ...);
void err(const char *str, ...);
void warn(const char *str, ...);
void info(const char *str, ...);

#endif // DEFINITIONS_H
