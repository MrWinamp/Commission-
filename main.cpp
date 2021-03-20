#include <QCoreApplication>
#include <QImage>
// Задание 1
class Employee
{
   int employee_Id;
  std::string employeeName;
public:
// Этот метод вставляет работника в таблицу некоторой БД
  bool InsertIntoEmployeeTable(Employee &em);

};

class ReportGenerator
{
public:
// Этот метод генерирует отчет относительно заданного работника
    void GenerateReport(Employee &em);
};

// Задание 2
enum ImageFormat
{
   JPG,
   PNG
};

class ProcessImage
{
    void process(QString inputFileName, QString outputFileName)
    {
        QByteArray imageData = loadImage(inputFileName);
        QImage image = imageFromData(imageData);
        removeAlphaChannel(image);
        if(needRemoveAlfaChannel())
            image = processImage(image);
        imageData = imageData(image);
        saveImage(outputFileName);
    }

protected:
    virtual QByteArray loadImage(QString &inputFileName) = 0;
    virtual QImage imageFromData(QByteArray &imageData) = 0;
    virtual QImage processImage(QImage &image) = 0;
    virtual void removeAlphaChannel(QImage &image) = 0;
    virtual QByteArray imageData(QImage &image) = 0;
    void saveImage(QString);
    bool needRemoveAlfaChannel(){
        return true;
    }
};

class ProcessJpgImage: public ProcessImage
{
protected:
    bool needRemoveAlfaChannel()
    {
        return false;
    }
    QByteArray loadImage(QString &inputFileName);
    QImage imageFromData(QByteArray &imageData);
    QByteArray imageData(QImage &image);
    QImage processImage(QImage &image);
    void removeAlphaChannel(QImage &image);
};

class ProcessPngImage: public ProcessImage
{
protected:
    QByteArray loadImage(QString &inputFileName);
    QImage imageFromData(QByteArray &imageData);
    QByteArray imageData(QImage &image);
    QImage processImage(QImage &image);
    void removeAlphaChannel(QImage &image);
};

void processJpgImage(QString inputFileName, QString outputFileName)
{
   QByteArray imageData = loadImage(inputFileName + ".jpg");
   QImage image = imageFromData(imageData, ImageFormat::JPG);
   image = processImage(image);
   imageData = imageData(image, ImageFormat::JPG);
   saveImage(outputFileName + ".jpg");
}

void processPngImage(QString inputFileName, QString outputFileName)
{
   QByteArray imageData = loadImage(inputFileName + ".png");
   QImage image = imageFromData(imageData , ImageFormat::PNG);
   removeAlphaChannel(image, ImageFormat::PNG);
   image = processImage(image);
   imageData = imageData(image, ImageFormat::PNG);
   saveImage(outputFileName + ".png");
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
