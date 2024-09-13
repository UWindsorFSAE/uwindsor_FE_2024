#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

class MainWindow : public QWidget
{
public:
    MainWindow()
    {
        //test
        resize(1280, 720);
        setStyleSheet("background-color: black;");
        // Create the main layout for the widget
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // Create a header layout for the text and button
        QHBoxLayout *headerLayout = new QHBoxLayout();

        // Create a label and a button for the header
        QLabel *headerLabel = new QLabel("Header Text");
        QPushButton *headerButton = new QPushButton("Header Button");
        headerButton->setStyleSheet("background-color: white; color: black;");

        // Add the label and button to the header layout
        headerLayout->addWidget(headerLabel);
        headerLayout->addWidget(headerButton);

        // Create the grid layout for the buttons
        QGridLayout *gridLayout = new QGridLayout();

        // Number of rows and columns for the grid
        int numRows = 5; // For example, 5 rows
        int numCols = 4; // 4 columns

        // Add buttons to the grid layout
        for (int i = 0; i < numRows * numCols; ++i)
        {
            QPushButton *button = new QPushButton(QString("Button %1").arg(i + 1));

            // Set the button background color to white
            button->setStyleSheet("background-color: white; color: black;");

            gridLayout->addWidget(button, i / numCols, i % numCols);
        }

        // Add the header layout and grid layout to the main layout
        mainLayout->addLayout(headerLayout);
        mainLayout->addLayout(gridLayout);

        // Set the main layout to the widget
        setLayout(mainLayout);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
