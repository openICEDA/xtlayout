#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>

class LBlock;
class MainWindow;
class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
private:
    MainWindow* mMainWindow;
    LBlock* mBlock;
public:
    ~PaintingArea();
    explicit PaintingArea(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    bool saveAs();
    bool saveFile(const QString& pFileName);
    bool loadFile(const QString& pFileName);
    LBlock* getBlock() {return mBlock;};
};
#endif // PAINTINGAREA_H
