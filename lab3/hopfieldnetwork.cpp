#include "hopfieldnetwork.h"
#include <QImage>
#include <QColor>
#include <ctime>
#include <random>

HopfieldNetwork::HopfieldNetwork(QStringList &fileNames)
{
    srand(time(NULL));
    std::vector<std::vector<int>> x;

    for (size_t i = 0; i < fileNames.size(); i++)
    {
        QImage image(fileNames.at(i));
        x.push_back(imageToData(&image));
    }

    loadWeightMatrix(x);
}

QImage*HopfieldNetwork::recognize(QImage* input)
{
    std::vector<int> x = imageToData(input);
    std::vector<int> y = recognizeData(x);
    QImage* output = dataToImage(y);
    return output;
}

void HopfieldNetwork::loadWeightMatrix(std::vector<std::vector<int>>& x)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                w[i][j] = 0;
                for (int k = 0; k < x.size(); k++)
                {
                    w[i][j] += (x[k][i]) * (x[k][j]);
                }
            }
            else
            {
                w[i][j] = 0;
            }
        }
    }
}

std::vector<int> HopfieldNetwork::recognizeData(std::vector<int> x)
{
    std::vector<int> y;
    y = x;
    std::vector<int> prevY;
    prevY.resize(N, 0);
    int maxIter = 10000;

    for(int j = 0; j < N; j++)
    {
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += w[i][j] * y[i];
        }

        if (sum >= 0)
        {
            y[j] = 1;
        }
        else
        {
            y[j] = -1;
        }
    }

    while ((maxIter-- > 0) && (y != prevY))
    {
        //y(j) = T(sum(w(i, j) * x(i)))
        //where T(a) = -1 if a > 0,
        //and T(a) = 1 otherwise

        prevY = y;

        int j = rand() % N;
        int sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += w[i][j] * y[i];
        }

        if (sum >= 0)
        {
            y[j] = 1;
        }
        else
        {
            y[j] = -1;
        }

    }

    return y;
}

std::vector<int> HopfieldNetwork::imageToData(QImage* input)
{
    std::vector<int> x;
    x.resize(N, 0);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            QColor color = QColor(input->pixel(j, i));
            int index = i * WIDTH + j;
            if (color == QColor(0, 0, 0))
            {
                x[index] = 1;
            }
            else
                x[index] = -1;
        }
    }
    return x;
}

QImage*HopfieldNetwork::dataToImage(std::vector<int>& x)
{
    QImage* image = new QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
    image->fill(Qt::white);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            int index = i * WIDTH + j;
            int color = x[index];
            if (color == 1)
            {
                image->setPixel(j, i, 0x000000);
            }
            else
            {
                image->setPixel(j, i, 0xffffff);
            }
        }
    }
    return image;
}
