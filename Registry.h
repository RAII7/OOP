#pragma once

#include <unordered_map>
#include "Product.h"
#include "Customer.h"
#include "Deal.h"

template <class Type>
class Registry
{
private:
	std::unordered_map<unsigned int, Type> objects_map;
	std::vector<unsigned int> id_vec;

public:
	unsigned int regist(Type& obj)
	{
		unsigned int id = obj.ID();
		objects_map[id] = obj;
		id_vec.push_back(id);
		return id;
	}

	void deregist(unsigned int id)
	{
		try
		{
			auto iter = std::find(id_vec.begin(), id_vec.end(), id);
			if (iter == id_vec.end())
				throw std::invalid_argument("Cannot deregister a object: ID is not registered.\n");
			objects_map.erase(id);
			id_vec.erase(iter);
		}
		catch (const std::invalid_argument& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	Type& getById(unsigned int id)
	{
		try
		{
			auto iter = std::find(id_vec.begin(), id_vec.end(), id);
			if (iter == id_vec.end())
				throw std::invalid_argument("Cannot deregister a object: ID is not registered.\n");
			return objects_map.at(id);
		}
		catch (const std::invalid_argument& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	int regSize()
	{
		return id_vec.size();
	}

	void regClear()
	{
		objects_map.clear();
		id_vec.clear();
	}

	auto begin() {
		return id_vec.begin();
	}

	auto end() {
		return id_vec.end();
	}
};
 /*int Registry() {
	std::cout << Registry;
}*/
