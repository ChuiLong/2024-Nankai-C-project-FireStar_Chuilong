#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView {//这是一个类的声明，名为 "View"，它是 "QGraphicsView" 类的公有子类。这意味着 "View" 类继承了 "QGraphicsView" 类的属性和方法，并且可以重写或添加自己的属性和方法。
    Q_OBJECT    //这是一个宏，用于在类中声明 Qt 信号和槽机制所需的元对象特性
signals:                                //这是一个信号部分，用于声明类中定义的信号
    void move(int x, int y);
    void events(QString str);
    void fight(int num);
    void change();
    void quit();
//信号函数
public:
    explicit View(QWidget *parent = 0);       //不允许隐式调用
    ~View();
    QString GetStatus() { return status; }
    void SetStatus(QString status) { this->status = status; }
    void keyMain(QKeyEvent *event);
    void keyShop(QKeyEvent *event);
    void keyWelcome(QKeyEvent *event);
    void keySelect(QKeyEvent *event);
    void keyFight();
    void action();
//公共变量和函数
protected:
    void keyPressEvent(QKeyEvent *event);
//这是一个保护函数的声明，重写了基类中的虚函数 keyPressEvent
private:
    int access(int x, int y);
    QString status;
    int next_step;
//私有的
};
#endif
