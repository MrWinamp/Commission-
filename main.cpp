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
    ProcessImage(ImageFormat format = ImageFormat::JPG): m_format(format){
        switch (format) {
        case JPG:
            m_suffix = ".jpg";
            break;
        case PNG:
            m_suffix = ".png";
            break;
        }
    };

    void process(QString inputFileName, QString outputFileName)
    {
        QByteArray imageData = loadImage(inputFileName + m_suffix);
        QImage image = imageFromData(imageData, m_format);
        removeAlphaChannel(image, m_format);
        if(needRemoveAlfaChannel())
            image = processImage(image);
        imageData = imageData(image, m_format);
        saveImage(outputFileName + m_suffix);
    }

protected:
    QByteArray loadImage(QString &inputFileName);
    QImage imageFromData(QByteArray &imageData, ImageFormat format);
    virtual QImage processImage(QImage &image) = 0;
    virtual void removeAlphaChannel(QImage &image, ImageFormat format) = 0;
    QByteArray imageData(QImage &image, ImageFormat format);
    void saveImage(QString);
    bool needRemoveAlfaChannel(){
        return true;
    }
private:
    ImageFormat m_format;
    QString m_suffix;
};

class ProcessJpgImage: public ProcessImage
{
public:
    ProcessJpgImage(): ProcessImage(ImageFormat::JPG){}
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
public:
    ProcessPngImage(): ProcessImage(ImageFormat::PNG){}
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
