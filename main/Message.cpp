#include "Message.h"
#include "ui_Message.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include "globals/Globals.h"

/**
 * @brief Message::Message
 * @param parent
 */
Message::Message(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Message)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(0);
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(QColor(0, 0, 0, 30));
    effect->setOffset(4);
    effect->setBlurRadius(8);
    setGraphicsEffect(effect);
}

/**
 * @brief Message::~Message
 */
Message::~Message()
{
    delete ui;
}

/**
 * @brief Sets the (unique) id of the message
 * @param id Id
 * @see Message::id
 */
void Message::setId(int id)
{
    m_id = id;
}

/**
 * @property Message::id
 * @brief Holds the (unique) id of the message
 * @return Id of the message
 * @see Message::setId
 */
int Message::id()
{
    return m_id;
}

/**
 * @brief Shows or hides the progress bar
 * @param show Show the progress bar (or not)
 */
void Message::showProgressBar(bool show)
{
    ui->progressBar->setVisible(show);
    m_timer->start(10*60*1000);
}

/**
 * @brief Sets the value of the progress bar
 * @param current Current value
 * @param max Maximum value
 */
void Message::setProgress(int current, int max)
{
    ui->progressBar->setRange(0, max);
    ui->progressBar->setValue(current);
    m_timer->start(10*60*1000);
}

/**
 * @brief Sets the message to be displayed
 * @param message Message
 * @param timeout How long should it be visible
 */
void Message::setMessage(QString message, int timeout)
{
    ui->label->setText(message);
    m_timer->start(timeout);
}

/**
 * @brief Message::timeout
 */
void Message::timeout()
{
    qDebug() << "Entered, m_id=" << m_id;
    emit sigHideMessage(m_id);
}

int Message::maxValue()
{
    return ui->progressBar->maximum();
}

int Message::value()
{
    return ui->progressBar->value();
}
