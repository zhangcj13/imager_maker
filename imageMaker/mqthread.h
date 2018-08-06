#ifndef MQTHREAD_H
#define MQTHREAD_H

#include <QThread>

class mQThread : public QThread
{
	Q_OBJECT

public:
	mQThread(QObject *parent=0);
	~mQThread();
protected:
	virtual void run() Q_DECL_OVERRIDE
	{
		//qDebug() << "mQThread Run Thread : " << QThread::currentThreadId();
		int nValue = 0;
		while (nValue < 100)
		{
			// ����50����
			msleep(50);
			++nValue;
			// ׼������
			emit resultReady(nValue);
		}
	}


private:
signals:
	void resultReady(int value);	
};

#endif // MQTHREAD_H
