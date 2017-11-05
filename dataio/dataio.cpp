#include "dataio.h"

/*function that reading data from file*/
bool readFromFile(QVector <QVector <double>> &vector_container, QVector <int> usedChannels, QString &answer)
{
    TADC_Data_file ADC_Data_File;
    FILE *adc_data_file;
    QVector <double> vectorOfData;

    QString datadir = "Data";
    if(!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    for (auto itv = usedChannels.begin(); itv != usedChannels.end(); ++itv){
        adc_data_file = fopen((datadir.toStdString()+ "\\Channel_" + std::to_string(*itv) + ".dat").c_str(), "rb");
        if (adc_data_file == NULL) {
            answer = "<font color='red'>Данные не загружены</font>";
            return false;
        }
        fread(&ADC_Data_File, sizeof(ADC_Data_File), 1, adc_data_file);
        fclose(adc_data_file);
        for (unsigned int j=0;j < ADC_Data_File.adc_count;j++){
            double temp;
            temp = ADC_Data_File.adc_buff[j];
            temp -= 8192;
            temp = ( (temp * 10) / 8192);
            vectorOfData.append(temp);
            }
        vector_container.append(vectorOfData);
        vectorOfData.clear();
        }
    answer = "<font color='green'>Данные загружены</font>";
    return true;
}

bool readFromFile(QMap <QString, QVector<double>> &map_container, QVector <int> usedChannels, QString &answer)
{
    TADC_Data_file ADC_Data_File;
    FILE *adc_data_file;
    QVector <double> vectorOfData;

    QString datadir = "Data";
    if (!QDir(datadir).exists()){
        QDir().mkdir(datadir);
    }
    for (auto itv = usedChannels.begin(); itv != usedChannels.end(); ++itv){
        adc_data_file = fopen((datadir.toStdString()+ "\\Channel_" + std::to_string(*itv) + ".dat").c_str(), "rb");
        if (adc_data_file == NULL) {
            answer = "<font color='red'>Данные не загружены</font>";
            return false;
        }
        fread(&ADC_Data_File, sizeof(ADC_Data_File), 1, adc_data_file);

        fclose(adc_data_file);
        for (unsigned int j=0;j < ADC_Data_File.adc_count;j++){
            double temp;
            temp = ADC_Data_File.adc_buff[j];
            temp -= 8192;
            temp = ( (temp * 10) / 8192);
            vectorOfData.append(temp);
            }
        map_container.insert(QString::fromUtf8(("Channel_" + std::to_string(*itv)).c_str()), vectorOfData);
        vectorOfData.clear();
        }
    adc_data_file = fopen((datadir.toStdString()+ "\\Channel_DUP.dat").c_str(), "rb");
    if (adc_data_file == NULL) {
        answer = "<font color='red'>Данные не загружены</font>";
        return false;
    }
    fread(&ADC_Data_File, sizeof(ADC_Data_File), 1, adc_data_file);
    fclose(adc_data_file);
    for (unsigned int j=0;j < ADC_Data_File.adc_count;j++){
        double temp;
        temp = ADC_Data_File.adc_buff[j];
        temp -= 8192;
        temp = ( (temp * 10) / 8192);
        vectorOfData.append(temp);
        }
    map_container.insert("Channel_DUP", vectorOfData);
    vectorOfData.clear();

    answer = "<font color='green'>Данные загружены</font>";
    return true;
}

bool readFromADC(QVector <QVector <double>> &vector_container, QVector <int> usedChannels, QString &answer)
{
    TConfigUSBPort ConfigUSBPort;
    TADC_Data ADC_Data;
    Settings settings;
    settings.getUsbSettings(ConfigUSBPort);
    //getUsbSettings(ConfigUSBPort);

    ADC_Data.adc_count = ConfigUSBPort.adc_count;
    //ADC_Data.adc_freq = ConfigUSBPort.adc_freq;

    if (!OpenPort(&ConfigUSBPort)){
        answer = "<font color='red'>Ошибка при открытии порта</font>";
        return false;
    }

    double timer_sleep;
    timer_sleep = ConfigUSBPort.adc_count;
    timer_sleep = timer_sleep / ConfigUSBPort.adc_freq; //timer for ADC

    int32_t temp;

    if ( (temp = SetEnableChannelADC(ConfigUSBPort.adc_channels)) < 0 ){
        answer = "<font color='red'>Ошибка при установке подключении каналов</font>";
        return false;
    }

    if ( (temp = SetFreqSampleADC(ConfigUSBPort.adc_freq)) < 0 ){
        answer = "<font color='red'>Ошибка при установке частоты АЦП</font>";
        return false;
    }

    if ( (temp = SetCountSampleADC(ConfigUSBPort.adc_count)) < 0 ){
        answer = "<font color='red'>Ошибка при установке количества точек</font>";
        return false;
    }

    if (StartSampleADC(timer_sleep + 2000) < 0){
        answer = "<font color='red'>Ошибка при установке времени работы АЦП</font>";
        return false;
    }
    QVector <double> vectorOfData;

    for (auto itv = usedChannels.begin(); itv != usedChannels.end(); ++itv){
        temp = ReadDataADC(ConfigUSBPort.adc_count, *itv, ADC_Data.adc_buff);
        for (unsigned int j=0;j < ADC_Data.adc_count;j++){
            double temp;
            temp = ADC_Data.adc_buff[j];
            temp -= 8192;
            temp = ( (temp * 10) / 8192);
            vectorOfData.append(temp);
            }
        vector_container.append(vectorOfData);
        vectorOfData.clear();
    }
    ClosePort();
    answer = "<font color='green'>Данные загружены</font>";
    return true;
}

bool readFromADC(QMap <QString, QVector<double>> &map_container, QVector <int> usedChannels, QString &answer)
{
    TConfigUSBPort ConfigUSBPort;
    TADC_Data ADC_Data;
    FILE *adc_data_file;
    Settings settings;
    settings.getUsbSettings(ConfigUSBPort);

    // уменьшаем значения на -1, потому что у ReadADC() 0 - это 1 канал и тп и тд.
    std::for_each(usedChannels.begin(), usedChannels.end(), [](int &a){a--;});

    ADC_Data.adc_count = ConfigUSBPort.adc_count;
    ADC_Data.adc_freq = ConfigUSBPort.adc_freq;

    if (!OpenPort(&ConfigUSBPort)){
        answer = "<font color='red'>Ошибка при открытии порта</font>";
        return false;
    }

    double timer_sleep;
    timer_sleep = ConfigUSBPort.adc_count;
    timer_sleep = timer_sleep / ConfigUSBPort.adc_freq; //timer for ADC

    int32_t temp;

    if ( (temp = SetEnableChannelADC(ConfigUSBPort.adc_channels)) < 0 ){
        answer = "<font color='red'>Ошибка при установке подключении каналов</font>";
        return false;
    }

    if ( (temp = SetFreqSampleADC(ConfigUSBPort.adc_freq)) < 0 ){
        answer = "<font color='red'>Ошибка при установке частоты АЦП</font>";
        return false;
    }

    if ( (temp = SetCountSampleADC(ConfigUSBPort.adc_count)) < 0 ){
        answer = "<font color='red'>Ошибка при установке количества точек</font>";
        return false;
    }

    if (StartSampleADC(timer_sleep + 2000) < 0){
        answer = "<font color='red'>Ошибка при установке времени работы АЦП</font>";
        return false;
    }
    QVector <double> vectorOfData;

    for (auto itv = usedChannels.begin(); itv != usedChannels.end(); ++itv){
        temp = ReadDataADC(ConfigUSBPort.adc_count, *itv, ADC_Data.adc_buff);
        for (unsigned int j=0;j < ADC_Data.adc_count;j++){
            double temp;
            temp = ADC_Data.adc_buff[j];
            temp -= 8192;
            temp = ( (temp * 10) / 8192);
            vectorOfData.append(temp);
            }

        adc_data_file = fopen(("Channel_" + std::to_string(*itv) + ".dat").c_str(), "wb");
        fwrite(&ADC_Data, sizeof(ADC_Data), 1, adc_data_file);
        fclose(adc_data_file);

        map_container.insert(QString::fromUtf8(("Channel_" + std::to_string(*itv + 1)).c_str()), vectorOfData);
        vectorOfData.clear();
    }
    //ДУП канал считывается отдельно (номер канала берется из настроек программы)
    temp = ReadDataADC(ConfigUSBPort.adc_count, settings.getDupChannel() - 1, ADC_Data.adc_buff);
    for (unsigned int j=0;j < ADC_Data.adc_count;j++){
        double temp;
        temp = ADC_Data.adc_buff[j];
        temp -= 8192;
        temp = ( (temp * 10) / 8192);
        vectorOfData.append(temp);
        }

    adc_data_file = fopen("Channel_DUP.dat", "wb");
    fwrite(&ADC_Data, sizeof(ADC_Data), 1, adc_data_file);
    fclose(adc_data_file);

    map_container.insert("Channel_DUP", vectorOfData);
    vectorOfData.clear();
    ClosePort();
    answer = "<font color='green'>Данные загружены</font>";
    return true;
}
/* function that getting indexes of values where dup is works*/
void getIndicesVector(QVector <double> &dataVector, QVector <int> &indicesVector)
{
    Settings settings;
    bool indexGeted = false;
    double porogValue = settings.getTreshold();

    for (auto itv = dataVector.begin(); itv != dataVector.end(); ++itv){
        if (*itv > porogValue && !indexGeted){
            indicesVector.push_back(itv - dataVector.begin());
            indexGeted = true;
        }
        if (*itv < 0 && indexGeted){
            indexGeted = false;
        }
    }
}

/* function that count VMT angle (average) from all getted data by indicesVector*/
int getVMTAngle(QVector <int> &indicesVector, QVector <double> &dataVector)
{
    int N = 1;
    double fiAngle = 360/N;
    int tacticity = 1;
    double fiVmt;
    int averageFiVmt;
    QVector<double> fiVmtVector;
    QVector<int>::const_iterator itv;

    for (itv = indicesVector.begin() + 1*tacticity;itv < std::prev(indicesVector.end(), 1*tacticity);itv += tacticity){
        double max = dataVector[0];
        int index;           /*if tacticity 1 iterator will upgrade by 1*/
        QVector <int> indexes;

        for (int i = *itv;i <= *(itv+tacticity);++i){
            if (dataVector[i] > max){
                max = dataVector[i];               
            }
        }
        for (int i = *itv;i <= *(itv+tacticity);++i){
            if (dataVector[i] == max){
                indexes.push_back(i);
            }
        }
        index = getAverageIndex(indexes);
        auto angleSegment = fiAngle/(*(std::next(itv, tacticity)) - *itv);
        fiVmt = (index - *itv) * angleSegment ;
        fiVmtVector.push_back(fiVmt);

    }
    return averageFiVmt = round(std::accumulate(fiVmtVector.begin(), fiVmtVector.end(), 0.0)/fiVmtVector.size());
}

/*function that get's average index from indexes of max values (for counting VMT)*/
int getAverageIndex(QVector <int> indexes)
{
    int averageIndex = int(std::accumulate(indexes.begin(), indexes.end(), 0)/indexes.size());
    int indexDiff = averageIndex - *(indexes.begin());
    int index = *(indexes.begin());
    for (auto itv = indexes.begin(); itv != indexes.end(); ++itv){
        if (abs(averageIndex - *itv) < indexDiff){
            indexDiff = abs(averageIndex - *itv);
            index = *itv;
        }
    }
    return index;
}

/*function that getting VMT data vector(vector that contains data from -180 to VMT point to +180 degree)*/
void getVMTDataVector(int VMT, QVector <int> &indicesVector, QVector <double> &dataVector, QVector<double> &vmtDataVector)
{
    int tacticity = 1;
    QVector <QVector <double>> vector;

    for (auto itv = std::next(indicesVector.begin(), 1*tacticity); itv < std::prev(indicesVector.end(), 1*tacticity); itv+=1*tacticity){
        auto angleSegment = (*(std::next(itv, tacticity)) - *itv)/360.0;
        int delta = angleSegment*180;

        for (int i = *itv + int(angleSegment*VMT) - delta; i <= (*itv + int(angleSegment*VMT) + delta);++i){
            vmtDataVector.push_back(dataVector.at(i));
        }
        getAproxVMTVector(vmtDataVector);
        vector.push_back(vmtDataVector);
        vmtDataVector.clear();
    }
    getOneVectorFromSeveral(vector, vmtDataVector);
}

/*function that counting average vector from few vectors*/
void getOneVectorFromSeveral(QVector<QVector<double>> &bigVector, QVector<double> &newVector)
{
    for (int i = 0; i < bigVector.begin()->size();++i){
        double summ = 0;
        for (auto itv = bigVector.begin(); itv != bigVector.end(); ++itv){
            summ += (*itv).at(i);
        }
        newVector.push_back((summ/bigVector.size()));
    }

}

/*function that scaling VMTDataVector from big size to small (point every 0.5 degree = 721 elements)*/
void getAproxVMTVector(QVector <double> &oldVector, double angleSegementNew)
{
    QVector<double> vect;
    QVector<double> newVector;
    tk::spline s;
    double angleSegmentOfBigVector = 360.0/oldVector.size();

    for (double i = 0; i <= 360; i += angleSegmentOfBigVector){

        if (vect.size() < oldVector.size()){
            vect.push_back(i);
        }
    }
    /*устанавливаем данные, для получения новых после интерполяции*/
    s.set_points(vect.toStdVector(),oldVector.toStdVector());

    for (double i = 0; i <= 360; i += angleSegementNew){
        newVector.push_back(s(i));
    }

    //shiftCorrecting(newVector);
    oldVector.clear();
    oldVector = newVector;

}

/*function that correcting finded VMT point*/
void shiftCorrecting(QVector <double> &oldVector)
{
    int distance = std::distance(oldVector.begin(), std::max_element(oldVector.begin(), oldVector.end())) - 360;
    if (distance < 0){
        int distanc = abs(distance);
        for (auto itv = oldVector.end() - 1; distanc > 0;){
            oldVector.push_front(*itv);
            distanc--;
        }
        oldVector.erase(oldVector.end() - abs(distance), oldVector.end());
    }
    else if (distance > 0) {
        int distanc = distance;
        for (auto itv = oldVector.begin(); distanc > 0; ++itv){
            oldVector.push_back(*itv);
            distanc--;
        }
        oldVector.erase(oldVector.begin(), oldVector.begin() + distance);
    }
}

bool addNewDiesel(const QVariantMap &newDiesel)
{
    QString dieselsDir = "DieselsTypes";
    if (!QDir(dieselsDir).exists()){
        QDir().mkdir(dieselsDir);
    }
    QString dieselFile = newDiesel.value("dieseltype").toString();

    QJsonObject object = QJsonObject::fromVariantMap(newDiesel);

    QFile file(dieselsDir + "/" + dieselFile + QString(".json"));
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }
    QJsonDocument document(object);
    file.write(document.toJson());
    return true;
}
/*returns list of diesels from DieselsTypes folder*/
QStringList getDieselsList()
{
    QDir dir("DieselsTypes");
    QStringList list;
    return list = dir.entryList(QStringList() << "*.json", QDir::Files);
}

QVector <QVariantMap> getDieselsMap(bool &ok)
{
    QStringList list = getDieselsList();
    QString dieselsDir = "DieselsTypes";
    QVector <QVariantMap> diesels;
    ok = true;

    for (auto item : list) {
       QFile file(dieselsDir + "/" + item);
       if (!file.open(QIODevice::ReadOnly)){
           ok = false;
       }
       QByteArray data = file.readAll();
       QJsonDocument doc(QJsonDocument::fromJson(data));
       QJsonObject obj(doc.object());
       auto diesel = obj.toVariantMap();
       diesels.append(diesel);
       file.close();
    }
    return diesels;
}

QVector<QPen> getColors()
{
    QStringList list;
    QVector<QPen> graphPenVector;

    list << "red" << "green" << "blue" << "red" << "darkRed" << "magenta" << "darkMagenta" << "cyan" << "darkGreen";
    list << "yellow" << "darkYellow" << "darkCyan" << "darkBlue" << "darkGray" << "brown" << "orange" << "darkOrange";
    list << "deeppinpl" << "deepskyblue" << "black";

    for (int i = 0; i < list.size(); ++i){
        QPen graphPen;
        graphPen.setColor(list[i]);
        graphPenVector.push_back(graphPen);
    }
    return graphPenVector;
}

void getChannelsDataMap(QMap<QString, QVector<double>> &mapContainer, int VMT, QVector <int> indicesVector, int channel)
{
    mapContainer.remove("Channel_DUP"); //удаляем ДУП канал, чтобы не мешал

    QVector <int> workOrder = DieselType::getInstance().getWorkOrder();
    int order = workOrder.indexOf(channel) + 1;
    if (order == 1){
        QVector <double> vmtDataVector;
        QString key = QString::fromUtf8(("Channel_" + std::to_string(order)).c_str());
        getVMTDataVector(VMT, indicesVector, mapContainer[key], vmtDataVector);
        mapContainer.insert(key, vmtDataVector);
    } else {
        QVector <double> vmtDataVector;
        QString key = QString::fromUtf8(("Channel_" + std::to_string(order)).c_str());
        VMT += DieselType::getInstance().getAngleWedge() * (order - 1);
        slimimngIndicesVector(indicesVector, VMT);
        getVMTDataVector(VMT, indicesVector, mapContainer[key], vmtDataVector);
        mapContainer.insert(key, vmtDataVector);
    }
}

void slimimngIndicesVector(QVector <int> &indicesVector, int &enterAngle)
{
    int count = enterAngle/360; // на самом деле 360*тактность
    for (int i = 0; i < count; ++i){
        indicesVector.pop_front();
    }
    enterAngle = enterAngle%360;
}

void deleteDiesel(const QString &dieselname)
{
    QString dieselsDir = "DieselsTypes";
    QFile::remove(dieselsDir + "/" + dieselname + ".json");
}

QVector <double> getAnglesVector()
{
    QVector <double> anglesVector;
    for (double i = -180; i <= 180; i += 0.5){
        anglesVector.push_back(i);
    }
    return anglesVector;
}

bool saveVMT(int VMT)
{
    QVariantMap vmt;
    vmt.insert("VMT", VMT);
    QJsonObject object = QJsonObject::fromVariantMap(vmt);

    QFile file("VMT" + QString(".json"));
    if (!file.open(QIODevice::WriteOnly)){
        return false;
    }
    QJsonDocument document(object);
    file.write(document.toJson());
    return true;
}

int getVMTAngle()
{
    QFile file("VMT.json");
    if (!file.open(QIODevice::ReadOnly)){
    }
    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    auto vmtMap = doc.object().toVariantMap();
    file.close();
    return vmtMap.value("VMT").toInt();
}
