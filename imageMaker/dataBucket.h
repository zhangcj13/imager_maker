#pragma once
#include <memory>

namespace imgmaker
{
	struct DataSize
	{
	public:
		//unsigned int =size_t,为正数，增加所能存储的数据大小
		size_t number = 0;  //Batch_size
		size_t channels = 0; 
		size_t width = 0;
		size_t height = 0;
	public:
		//初始化
		DataSize() = default;
		DataSize(const size_t _number, const size_t _channels, const size_t _width, const size_t _height)
			:number(_number), channels(_channels), width(_width), height(_height){}
		//输入数据数量
		inline size_t totalSize() const { return _4DSize(); }
		inline size_t _4DSize() const { return number*channels*width*height; }
		inline size_t _3DSize() const { return channels*width*height; }
		inline size_t _2DSize() const { return width*height; }
		//重载操作符
		inline bool operator==(const DataSize& other) const
		{
			return other.number == number && other.channels == channels && other.width == width && other.height == height;
		}
		inline bool operator!=(const DataSize& other) const
		{
			return !(*this == (other));
		}
		//
		inline size_t getIndex(const size_t in, const size_t ic, const size_t ih, const size_t iw) const{
			return in*channels*height*width + ic*height*width + ih*width + iw;
		}
		inline size_t getIndex(const size_t ic, const size_t ih, const size_t iw) const{
			return ic*height*width + ih*width + iw;
		}
		
	};

	class DataBucket
	{
	private:
		DataSize size;
		std::shared_ptr<float> data;//矩阵数据
	public:
		DataBucket(const DataSize _size);
		virtual ~DataBucket();
	public:
		void fillData(const float item);
		void cloneTo(DataBucket& target);

		DataSize getSize() const;
		std::shared_ptr<float> getData() const;
	};
}