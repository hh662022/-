#include "game.h"
#include <QMediaPlayer>
#include <QDebug>
#include <QAudioOutput>
#include <QTimer>
#include <QFileInfo>
#include <cstring>
#include "judge.h"
#include "ui_form.h"

Game::Game() : ui(new Ui::Form()) {

    musicSpeed = 1.00;
    visualScrollSpeed = 600;
    musicVolume = 50;
    osuURL = ":/Songs/1/1.osu";
    musicURL = "qrc:/Songs/1/song.mp3";

    ui->setupUi(this);
    show();

    // -------------

    // set up graphics
    scene = new QGraphicsScene();
    int w = marginLeft + playFieldWidth + marginRight,
        h = marginUp + playFieldHeight + marginDown;
    scene->setSceneRect(0, 0, w, h);
    qDebug() << w << h;

    view = ui->graphicsView; // view = new QGraphicsView();
    view->setScene(scene);
    // view->resize(20+w, 20+h);
    view->show();

    // add score
    score = new Score();
    scene->addItem(score);

    // add accuracy
    accuracy = new Accuracy();
    scene->addItem(accuracy);

    // add judgement
    judgement = new Judge(scene, score, accuracy);

    // add example rectangles
    QGraphicsRectItem * marginRightRect = new QGraphicsRectItem();
    marginRightRect->setRect(marginLeft + playFieldWidth, 0, marginRight, h);
    scene->addItem(marginRightRect);

    QGraphicsRectItem * marginLeftRect = new QGraphicsRectItem();
    marginLeftRect->setRect(0, 0, marginLeft, h);
    scene->addItem(marginLeftRect);

    QGraphicsRectItem * marginUpRect = new QGraphicsRectItem();
    marginUpRect->setRect(0, 0, w, marginUp);
    scene->addItem(marginUpRect);

    QGraphicsRectItem * marginDownRect = new QGraphicsRectItem();
    marginDownRect->setRect(0, marginUp + playFieldHeight, w, marginDown);
    scene->addItem(marginDownRect);

    for (int i = 0; i < columnCount; ++i) {
        QGraphicsRectItem * columniRect = new QGraphicsRectItem();
        columniRect->setRect(marginLeft + i*noteWidth, marginUp, noteWidth, playFieldHeight);
        scene->addItem(columniRect);
    }
}

void Game::start() {
    scrollSpeed = visualScrollSpeed * musicSpeed;

    // load .osu file
    QFile osuFile(osuURL);
    file = &osuFile;
    if (!osuFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!osuFile.atEnd()) {
        QByteArray line = osuFile.readLine();
        QString sline = line;
        QStringList slist = sline.split(QLatin1Char(',')), slist2 = slist[5].split(QLatin1Char(':'));
        /* Hold syntax: x,y,time,type,hitSound,endTime:hitSample
         * endTime (Integer): End time of the hold, in milliseconds from the beginning of the beatmap's audio.
         * x determines the index of the column that the hold will be in. It is computed by floor(x * columnCount / 512) and clamped between 0 and columnCount - 1.
         * y does not affect holds. It defaults to the centre of the playfield, 192.
         */
        Note *note = new Note(slist[0].toInt(), slist[1].toInt(), slist[2].toInt(), slist[3].toInt(), slist[4].toInt(), slist2[0].toInt());
        int lane = note->x * columnCount / 512;
        notes[lane].append(note);
    }
    memset(st, 0, sizeof(st));
    memset(ed, 0, sizeof(ed));

    // set playField to receive input
    playField = new PlayField();
    scene->addItem(playField);
    playField->setFlag(QGraphicsItem::ItemIsFocusable);
    playField->setFocus();
    playField->game = this;

    // set up audio, start game
    audio = new QAudioOutput();
    player = new QMediaPlayer();
    player->setAudioOutput(audio);
    player->setSource(QUrl(musicURL));
    audio->setVolume(musicVolume);
    player->setPlaybackRate(musicSpeed);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Game::timerAlert);
    timer->start(5);

    view->show();
    player->play();
}

void Game::keyPress(int i)
{
    if (player->playbackState() != QMediaPlayer::PlayingState) return;
    int cur = player->position();
    redraw(cur);
    if (st[i] == ed[i]) return;
    int st1 = st[i];
    Note * note = notes[i][st[i]];
    if (judgement->hasMissed(cur, note, musicSpeed)) return;
    if (judgement->canHit(cur, note, musicSpeed)) {
        judgement->judge(cur, note, musicSpeed);
        assert(st1 == st[i]);
        note->isHit = true;
        scene->removeItem(note);
        st[i]++;
    }
}

void Game::positionChanged(qint64 position)
{
}

void Game::timerAlert() {
    redraw();
}

/* Hit object types are stored in an 8-bit integer where each bit is a flag with special meaning. The base hit object type is given by bits 0, 1, 3, and 7 (from least to most significant):
 * 0: Hit circle
 * 1: Slider
 * 3: Spinner
 * 7: osu!mania hold
 */

void Game::redraw(int cur)
{
    playField->setFocus();
    if (cur == -1) cur = player->position();
    // update current notes on screen.
    for (int i = 0; i < columnCount; ++i) {
        // check if new notes should appear on screen
        while (ed[i] < notes[i].size() && cur >= notes[i][ed[i]]->time - scrollSpeed) {
            Note * note = notes[i][ed[i]];
            scene->addItem(note);
            ed[i]++;
        }
        // check if old notes should be removed
        while (st[i] < ed[i] && st[i] < notes[i].size() && judgement->hasMissed(cur, notes[i][st[i]], musicSpeed)) {
            judgement->showJudgement(Miss);
            accuracy->addPercent(0);
            scene->removeItem(notes[i][st[i]]);
            st[i]++;
        }
        // redraw notes
        for (int j = st[i]; j < ed[i]; ++j) {
            Note * note = notes[i][j];
            int newx = marginLeft + i * noteWidth,
                newy = - noteHeight + (marginUp + playFieldHeight) * (cur - (note->time - scrollSpeed)) / scrollSpeed;
            note->setPos(newx, newy);
        }
    }
    bool hasEnded = true;
    for (int i = 0; i < columnCount; ++i) {
        hasEnded &= (st[i] == notes[i].size());
    }
    if (hasEnded) endGame();
}

int Game::endGame() {
    view->hide();
    int ret = score->score;
    view->hide();

    delete judgement;
    delete playField;
    delete score;
    delete accuracy;

    delete scene;
    delete view;

    delete audio;
    delete player;
    delete timer;
    return ret;
}

void Game::pauseGame() {
    timer->stop();
    player->pause();
}

void Game::continueGame() {
    timer->start();
    player->play();
}

Game::~Game()
{
}

void Game::on_pushButton_clicked()
{
    start();
}


void Game::on_pushButton_3_clicked()
{
    pauseGame();
}


void Game::on_pushButton_4_clicked()
{
    continueGame();
}


void Game::on_pushButton_2_clicked()
{
    endGame();
    hide();
    emit this->gameEnded();
    delete this;
}

