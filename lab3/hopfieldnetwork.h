#ifndef HOPFIELDNETWORK_H
#define HOPFIELDNETWORK_H

#include <QStringList>

class HopfieldNetwork
{
public:
    HopfieldNetwork(QStringList& fileNames);

    //for images 10 * 10
    //Hopfield network  can recognize 0.15 * N images
    static const int HEIGHT = 20;
    static const int WIDTH = 20;
    //number of neurons
    static const int N = HEIGHT * WIDTH;

    QImage* recognize(QImage* input);

private:
    //weight matrix
    int w[N][N];

    void loadWeightMatrix(std::vector<std::vector<int>>& x);
    std::vector<int> recognizeData(std::vector<int> x);
    std::vector<int> imageToData(QImage* input);
    QImage* dataToImage(std::vector<int>& x);
};

#endif // HOPFIELDNETWORK_H
