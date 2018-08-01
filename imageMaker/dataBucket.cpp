#include <algorithm>
#include "dataBucket.h"

namespace imgmaker
{
	DataBucket::DataBucket(const DataSize _size)
		:size(_size),data(new float[size.totalSize()])//���ݳߴ��ȡ�洢�ռ�
	{

	}
	DataBucket::~DataBucket()
	{

	}
	//�洢�ռ丳ֵ
	void DataBucket::fillData(const float item)
	{
		std::fill(data.get(), data.get() + getSize().totalSize(), item);
	}
	//���ݿ���
	void DataBucket::cloneTo(DataBucket& target)
	{
		target.size = this->size;
		const size_t dataSize = sizeof(float)*this->size.totalSize();
		memcpy(target.data.get(), this->data.get(), dataSize);
	}

	std::shared_ptr<float> DataBucket::getData() const
	{
		return data;
	}
	DataSize DataBucket::getSize() const
	{
		return size;
	}
}//namespace