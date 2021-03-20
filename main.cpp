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
public:
    void process(QString inputFileName, QString outputFileName)
    {
        QByteArray imageData = loadImage(inputFileName + ".jpg");
        QImage image = imageFromData(imageData, ImageFormat::JPG);
        removeAlphaChannel(image, ImageFormat::PNG);
        if(needRemoveAlfaChannel())
            image = processImage(image);
        imageData = imageData(image, ImageFormat::JPG);
        saveImage(outputFileName + ".jpg");
    }

protected:
    QByteArray loadImage(QString &inputFileName);
    QImage imageFromData();
    virtual QImage processImage(QImage &image) = 0;
    virtual void removeAlphaChannel(QImage &image, ImageFormat format) = 0;
    QByteArray imageData(QImage &image, ImageFormat format);
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
    QImage processImage(QImage &image);
    void removeAlphaChannel(QImage &image, ImageFormat format);
};

class ProcessPngImage: public ProcessImage
{
protected:
    QImage processImage(QImage &image);
    void removeAlphaChannel(QImage &image, ImageFormat format);
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
