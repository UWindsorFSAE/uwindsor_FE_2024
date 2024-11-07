#include <QApplication>
#include <QDebug>
#include <QFontDatabase>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load the custom font from the resources
    int fontId = QFontDatabase::addApplicationFont(":/fonts/resources/Roboto-Medium.ttf");
    if (fontId == -1) {
        qDebug() << "Font loading failed!";
    } else {
        qDebug() << "Font loaded successfully!";
    }

    // Load the custom font from the resources
    int font2Id = QFontDatabase::addApplicationFont(":/fonts/resources/Roboto-Light.ttf");
    if (font2Id == -1) {
        qDebug() << "Font loading failed!";
    } else {
        qDebug() << "Font loaded successfully!";
    }

    // Create the main window widget
    QWidget window;
    window.setWindowTitle("Dash");
    window.setStyleSheet("background-color: #080808;");

    QFontDatabase fontDatabase;
    QStringList fontFamilies = fontDatabase.families();  // List of font families

    // Print the font families
    for (const QString &font : fontFamilies) {
        qDebug() << font;
    }

    // Create the grid layout and set it as the layout for the window
    QGridLayout *gridLayout = new QGridLayout(&window);

    int rows = 2;
    int cols = 3;

    std::vector<Qt::Alignment> allignments = {Qt::AlignLeft, Qt::AlignHCenter, Qt::AlignRight};

    // Populate the grid with components, each containing two labels
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Create a widget to hold the two labels
            QWidget *componentWidget = new QWidget();
            QVBoxLayout *vboxLayout = new QVBoxLayout(componentWidget);

            // Set small spacing between labels
            vboxLayout->setSpacing(0);

            // Create two labels and add them to the vertical layout
            QLabel *label1 = new QLabel(QString("SPEED"));
            QLabel *label2 = new QLabel(QString("331.2"));

            // Create two different fonts for the labels
            QFont font1("Roboto Medium");
            QFont font2("Roboto Medium");

            // Apply the fonts to the labels
            label1->setFont(font1);
            label2->setFont(font2);

            // Set alignment to top-left to reduce extra spacing
            label1->setAlignment(allignments[col]);
            label2->setAlignment(allignments[col]);

            // Set alignment to top-left to reduce extra spacing
            vboxLayout->setAlignment(Qt::AlignCenter);
            vboxLayout->setSpacing(0);

            // Set larger font size via stylesheet
            label1->setStyleSheet("QLabel { font-size: 30px; font-weight: 100; color: #13b80d; margin: 0; padding: 0; }");
            label2->setStyleSheet("QLabel { font-size: 60px; font-weight: 800; color: white; margin: 0; padding: 0; }");

            // Add labels to the vertical layout
            vboxLayout->addWidget(label1);
            vboxLayout->addWidget(label2);

            // Set layout margins to 0 for a compact look
            vboxLayout->setContentsMargins(0, 0, 0, 0);

            // Add the widget containing the two labels to the grid layout
            gridLayout->addWidget(componentWidget, row, col);
        }
    }

    // Enable the grid layout to expand and fill the entire window
    window.setLayout(gridLayout);
    window.setGeometry(100, 100, 800, 480);  // Initial window size

    // Show the window
    window.show();

    return app.exec();
}
