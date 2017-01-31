/****************************************************************
 * options.cpp
 * GrblHoming - zapmaker fork on github
 *
 * 15 Nov 2012
 * GPL License (see LICENSE file)
 * Software is provided AS-IS
 ****************************************************************/

#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::~Options()
{

}
/// T4
void Options::init()
{
    connect(ui->checkBoxUseMmManualCmds,SIGNAL(toggled(bool)),this,SLOT(toggleUseMm(bool)));
    connect(ui->chkLimitZRate,SIGNAL(toggled(bool)),this,SLOT(toggleLimitZRate(bool)));
    connect(ui->checkBoxFourAxis,SIGNAL(toggled(bool)),this,SLOT(toggleFourAxis(bool)));
    connect(ui->checkBoxPositionReportEnabled,SIGNAL(toggled(bool)),this,SLOT(togglePosReporting(bool)));
    connect(this, SIGNAL(setSettingsOptionsUseMm()), parentWidget(), SLOT(setSettingsOptionsUseMm()));

    QSettings settings;

    QString invX = settings.value(SETTINGS_INVERSE_X, "false").value<QString>();
    QString invY = settings.value(SETTINGS_INVERSE_Y, "false").value<QString>();
    QString invZ = settings.value(SETTINGS_INVERSE_Z, "false").value<QString>();
    QString invFourth = settings.value(SETTINGS_INVERSE_FOURTH, "false").value<QString>();
    ui->chkInvFourth->setChecked(invFourth == "true");
    ui->chkInvX->setChecked(invX == "true");
    ui->chkInvY->setChecked(invY == "true");
    ui->chkInvZ->setChecked(invZ == "true");

    // enable logging by default
    QString enDebugLog = settings.value(SETTINGS_ENABLE_DEBUG_LOG, "true").value<QString>();
    // default aggressive preload behavior to 'true'!
    QString enAggressivePreload = settings.value(SETTINGS_USE_AGGRESSIVE_PRELOAD, "true").value<QString>();
    QString waitForJogToComplete = settings.value(SETTINGS_WAIT_FOR_JOG_TO_COMPLETE, "true").value<QString>();
    QString useMmManualCmds = settings.value(SETTINGS_USE_MM_FOR_MANUAL_CMDS, "true").value<QString>();
    QString enFourAxis = settings.value(SETTINGS_FOUR_AXIS_USE, "false").value<QString>();
    char fourthAxisType = settings.value(SETTINGS_FOUR_AXIS_NAME, FOURTH_AXIS_A).value<char>();

    if (enFourAxis == "false")
    {
        ui->chkInvFourth->hide();
        ui->chkInvFourth->setAttribute(Qt::WA_DontShowOnScreen, true);

        ui->groupBoxFourthAxis->setEnabled(false);
    }
    else
    {
        ui->chkInvFourth->show();
        ui->chkInvFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->groupBoxFourthAxis->setEnabled(true);

        switch (fourthAxisType)
        {
            case FOURTH_AXIS_A:
            default:
                ui->radioButtonFourthAxisA->setChecked(true);
                break;
            case FOURTH_AXIS_B:
                ui->radioButtonFourthAxisB->setChecked(true);
                break;
            case FOURTH_AXIS_C:
                ui->radioButtonFourthAxisC->setChecked(true);
                break;
			case FOURTH_AXIS_U:
				ui->radioButtonFourthAxisU->setChecked(true);
                break;
            case FOURTH_AXIS_V:
                ui->radioButtonFourthAxisV->setChecked(true);
                break;
            case FOURTH_AXIS_W:
                ui->radioButtonFourthAxisW->setChecked(true);
                break;
        }
    }

    ui->checkBoxEnableDebugLog->setChecked(enDebugLog == "true");
    ui->chkAggressivePreload->setChecked(enAggressivePreload == "true");
    //ui->checkBoxWaitForJogToComplete->setChecked(waitForJogToComplete == "true");
    ui->checkBoxWaitForJogToComplete->hide();
    ui->checkBoxUseMmManualCmds->setChecked(useMmManualCmds == "true");
    ui->checkBoxFourAxis->setChecked(enFourAxis == "true");

    int waitTime = settings.value(SETTINGS_RESPONSE_WAIT_TIME, DEFAULT_WAIT_TIME_SEC).value<int>();
    ui->spinResponseWaitSec->setValue(waitTime);

    double zJogRate = settings.value(SETTINGS_Z_JOG_RATE, DEFAULT_Z_JOG_RATE).value<double>();
    ui->doubleSpinZJogRate->setValue(zJogRate);

/// T4
    ui->spinMaxStatusLines->setValue( settings.value( SETTINGS_MAX_STATUS_LINES, 0 ).value<int>() );

    QString zRateLimit = settings.value(SETTINGS_Z_RATE_LIMIT, "false").value<QString>();
    ui->chkLimitZRate->setChecked(zRateLimit == "true");

    double zRateLimitAmount = settings.value(SETTINGS_Z_RATE_LIMIT_AMOUNT, DEFAULT_Z_LIMIT_RATE).value<double>();
    ui->doubleSpinZRateLimit->setValue(zRateLimitAmount);
    double xyRateAmount = settings.value(SETTINGS_XY_RATE_AMOUNT, DEFAULT_XY_RATE).value<double>();
    ui->doubleSpinXYRate->setValue(xyRateAmount);

    if (!ui->chkLimitZRate->isChecked())
    {
        ui->doubleSpinZRateLimit->setEnabled(false);
        ui->doubleSpinXYRate->setEnabled(false);
    }

    QString ffCmd = settings.value(SETTINGS_FILTER_FILE_COMMANDS, "false").value<QString>();
    ui->chkFilterFileCommands->setChecked(ffCmd == "true");
    QString rPrecision = settings.value(SETTINGS_REDUCE_PREC_FOR_LONG_LINES, "false").value<QString>();
    ui->checkBoxReducePrecForLongLines->setChecked(rPrecision == "true");
    ui->spinBoxGrblLineBufferSize->setValue(settings.value(SETTINGS_GRBL_LINE_BUFFER_LEN, DEFAULT_GRBL_LINE_BUFFER_LEN).value<int>());
    ui->spinBoxCharSendDelay->setValue(settings.value(SETTINGS_CHAR_SEND_DELAY_MS, DEFAULT_CHAR_SEND_DELAY_MS).value<int>());
/// T4
    int posReqKind = settings.value(SETTINGS_POS_REQ_KIND, POS_REQ).value<int>();
    switch (posReqKind) {
        case POS_REQ:
            ui->checkBoxPositionReportEnabled->setChecked(true);
            break;
        case POS_SYNC:
            ui->checkBoxSynchronousSimulation->setChecked(true);
            break;
        case POS_NO:
            ui->checkBoxNoDisplay->setChecked(true);
            break;
    }
/// <--
    QString enPosReq = settings.value(SETTINGS_ENABLE_POS_REQ, "true").value<QString>();
      //  ui->checkBoxPositionReportEnabled->setChecked(enPosReq == "true");
    QString posReqType = settings.value(SETTINGS_TYPE_POS_REQ, PREQ_NOT_WHEN_MANUAL).value<QString>();
    double posRateFreqSec = settings.value(SETTINGS_POS_REQ_FREQ_SEC, DEFAULT_POS_REQ_FREQ_SEC).value<double>();
    ui->doubleSpinBoxPosRequestFreqSec->setValue(posRateFreqSec);
    if (posReqType == PREQ_NOT_WHEN_MANUAL)
    {
        ui->radioButton_ReqNotDuringManual->setChecked(true);
    }
    else if (posReqType == PREQ_ALWAYS)
    {
        ui->radioButton_ReqAlways->setChecked(true);
    }
    else
    {
        ui->radioButton_ReqAlwaysNoIdleCheck->setChecked(true);
    }

    togglePosReporting(enPosReq == "true");

}

void Options::accept()
{
    QSettings settings;
// tab Axis
    settings.setValue(SETTINGS_INVERSE_X, ui->chkInvX->isChecked());
    settings.setValue(SETTINGS_INVERSE_Y, ui->chkInvY->isChecked());
    settings.setValue(SETTINGS_INVERSE_Z, ui->chkInvZ->isChecked());
    settings.setValue(SETTINGS_INVERSE_FOURTH, ui->chkInvFourth->isChecked());
    settings.setValue(SETTINGS_ENABLE_DEBUG_LOG, ui->checkBoxEnableDebugLog->isChecked());
    settings.setValue(SETTINGS_USE_AGGRESSIVE_PRELOAD, ui->chkAggressivePreload->isChecked());
    settings.setValue(SETTINGS_WAIT_FOR_JOG_TO_COMPLETE, ui->checkBoxWaitForJogToComplete->isChecked());
    settings.setValue(SETTINGS_USE_MM_FOR_MANUAL_CMDS, ui->checkBoxUseMmManualCmds->isChecked());
    settings.setValue(SETTINGS_FOUR_AXIS_USE, ui->checkBoxFourAxis->isChecked());
    settings.setValue(SETTINGS_FOUR_AXIS_NAME, getFourthAxisName());
    settings.setValue(SETTINGS_FOUR_AXIS_ROTATE, getFourthAxisRotate());

// tab General
    settings.setValue(SETTINGS_RESPONSE_WAIT_TIME, ui->spinResponseWaitSec->value());
    settings.setValue(SETTINGS_Z_JOG_RATE, ui->doubleSpinZJogRate->value());

    settings.setValue(SETTINGS_Z_RATE_LIMIT, ui->chkLimitZRate->isChecked());
    settings.setValue(SETTINGS_Z_RATE_LIMIT_AMOUNT, ui->doubleSpinZRateLimit->value());
    settings.setValue(SETTINGS_XY_RATE_AMOUNT, ui->doubleSpinXYRate->value());
/// T4
    settings.setValue(SETTINGS_MAX_STATUS_LINES, ui->spinMaxStatusLines->value());

// tab Filtering
    settings.setValue(SETTINGS_FILTER_FILE_COMMANDS, ui->chkFilterFileCommands->isChecked());
    settings.setValue(SETTINGS_REDUCE_PREC_FOR_LONG_LINES, ui->checkBoxReducePrecForLongLines->isChecked());
    settings.setValue(SETTINGS_GRBL_LINE_BUFFER_LEN, ui->spinBoxGrblLineBufferSize->value());
    settings.setValue(SETTINGS_CHAR_SEND_DELAY_MS, ui->spinBoxCharSendDelay->value());

// tab Display
    settings.setValue(SETTINGS_ENABLE_POS_REQ, ui->checkBoxPositionReportEnabled->isChecked());
    settings.setValue(SETTINGS_TYPE_POS_REQ, getPosReqType());
    settings.setValue(SETTINGS_POS_REQ_FREQ_SEC, ui->doubleSpinBoxPosRequestFreqSec->value());
/// T4
    int posreq = getPosReqKind();
    settings.setValue(SETTINGS_POS_REQ_KIND, posreq);
    connect(this, SIGNAL(setPosReqKind(int)), parentWidget(), SLOT(setPosReqKind(int) ));
    // -> 'Mainwindow::setSettingsOptions()'
    connect(this, SIGNAL(setSettingsOptions()), parentWidget(), SLOT(setSettingsOptions()));

    emit setSettingsOptions();

    this->close();
}

/// T4
void Options::setUseMm(bool mm)
{
//diag("Options::setUseMm = %s", mm==true?"true":"false");
    externUseMm = mm;
// update gcode thread with latest values
   //ui->checkBoxUseMmManualCmds->setEnabled(ui->checkBoxUseMmManualCmds->isChecked() == mm );
    ui->checkBoxUseMmManualCmds->setChecked(mm);
}
bool Options::getUseMm()
{
//diag("Options::checkBoxUseMmManualCmds->isChecked() = %s", ui->checkBoxUseMmManualCmds->isChecked()==true?"true":"false");
    return ui->checkBoxUseMmManualCmds->isChecked();
}
double Options::getZJogRate()
{
    return ui->doubleSpinZJogRate->value();
}
double Options::getzRateLimit()
{
//diag("Options::getzRateLimit() = %0.2f", ui->doubleSpinZRateLimit->value());
    return ui->doubleSpinZRateLimit->value();
}
double Options::getXYRate()
{
    return ui->doubleSpinXYRate->value();
}
/// <--

void Options::toggleUseMm(bool useMm)
{
//diag("Options::toggleUseMm() ...");
    double zJogRate = ui->doubleSpinZJogRate->value();
    double zRateLimit = ui->doubleSpinZRateLimit->value();
    double xyRate = ui->doubleSpinXYRate->value();
/// T4
    QString txt = "Z-Jog Rate ";
    if (useMm)
    {
        txt += "(mm/min)";
        zJogRate *= MM_IN_AN_INCH ;   //  zJogRate = int(zJogRate*100 + 0.5)/100.0 ;
        zRateLimit *= MM_IN_AN_INCH ; //  zRateLimit = int(zRateLimit*100 + 0.5)/100.0 ;
        xyRate *= MM_IN_AN_INCH ;     //  xyRate  = int(xyRate *100 + 0.5)/100.0 ;
    }
    else
    {   txt += "(inches/min)";
        zJogRate /= MM_IN_AN_INCH ;
        zRateLimit /= MM_IN_AN_INCH ;
        xyRate /= MM_IN_AN_INCH ;
    }
    ui->labelZJogRate->setText(txt);
    ui->doubleSpinZJogRate->setValue(zJogRate);
    ui->doubleSpinZRateLimit->setValue(zRateLimit);
    ui->doubleSpinXYRate->setValue(xyRate);
/// <--
    emit setSettingsOptionsUseMm();
}

void Options::toggleLimitZRate(bool limitZ)
{
    ui->doubleSpinZRateLimit->setEnabled(limitZ);
    ui->doubleSpinXYRate->setEnabled(limitZ);
}

void Options::toggleFourAxis(bool four)
{
    if (four)
    {
        ui->chkInvFourth->show();
        ui->chkInvFourth->setAttribute(Qt::WA_DontShowOnScreen, false);
        ui->groupBoxFourthAxis->setEnabled(true);
    }
    else
    {
        ui->chkInvFourth->hide();
        ui->chkInvFourth->setAttribute(Qt::WA_DontShowOnScreen, true);
        ui->groupBoxFourthAxis->setEnabled(false);
    }

}

void Options::togglePosReporting(bool usePosReporting)
{
    if (usePosReporting)
    {
        ui->groupBox_ReqPos->setEnabled(true);
    }
    else
    {
        ui->groupBox_ReqPos->setEnabled(false);
    }
}

/// T4
bool Options::getFourthAxisRotate()
{
    char name = getFourthAxisName();

    return (name == FOURTH_AXIS_A || name == FOURTH_AXIS_B || name == FOURTH_AXIS_C );

}

char Options::getFourthAxisName()
{
// update gcode thread with latest values
    char type = FOURTH_AXIS_A;

    if (ui->radioButtonFourthAxisA->isChecked())
    {
        type = FOURTH_AXIS_A;
    }
    else
	if (ui->radioButtonFourthAxisB->isChecked())
    {
        type = FOURTH_AXIS_B;
    }
    else
    if (ui->radioButtonFourthAxisC->isChecked())
    {
        type = FOURTH_AXIS_C;
    }
    if (ui->radioButtonFourthAxisU->isChecked())
    {
        type = FOURTH_AXIS_U;
    }
    else
	if (ui->radioButtonFourthAxisV->isChecked())
    {
        type = FOURTH_AXIS_V;
    }
    else
    if (ui->radioButtonFourthAxisW->isChecked())
    {
        type = FOURTH_AXIS_W;
    }

    return type;
}

/// T4
int Options::getPosReqKind()
{
    int choice = POS_REQ ;
    if (ui->checkBoxPositionReportEnabled->isChecked() )
        choice = POS_REQ ;
// update gcode thread with latest values
    else
    if (ui->checkBoxSynchronousSimulation->isChecked())
        choice = POS_SYNC;
    else
    if (ui->checkBoxNoDisplay->isChecked() )
        choice = POS_NO ;

    return  choice;
}

QString Options::getPosReqType()
{
    if (ui->radioButton_ReqAlways->isChecked())
    {
        return PREQ_ALWAYS;
    }
    else if (ui->radioButton_ReqNotDuringManual->isChecked())
    {
        return PREQ_NOT_WHEN_MANUAL;
    }
    return PREQ_ALWAYS_NO_IDLE_CHK;
}
