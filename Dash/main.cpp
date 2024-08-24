#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout> // Header for QVBoxLayout

class MainWindow : public QWidget
{
public:
    MainWindow()
    {
        QPushButton *button = new QPushButton("Click Me", this);
        QLabel *label = new QLabel("Hello, World!", this);

        QVBoxLayout *layout = new QVBoxLayout; // Using QVBoxLayout
        layout->addWidget(button);
        layout->addWidget(label);

        setLayout(layout);
        setWindowTitle("Simple Qt App");

        connect(button, &QPushButton::clicked, [label]()
                { label->setText("Button Clicked!"); });
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
