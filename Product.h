#pragma once

#include <string>
#include "General.h"

class Product : public General {
private:
	std::string m_name;
	double m_optPrice;
	double m_rozPrice;
	std::string m_description;

public:
	std::string name() {
		return m_name;
	}
	double optPrice() {
		return m_optPrice;
	}
	double rozPrice() {
		return m_rozPrice;
	}
	std::string description() {
		return m_description;
	}

	void setName(std::string name) {
		this->m_name = std::move(name);
	}
	void setOptPrice(double optPrice) {
		this->m_optPrice = std::move(optPrice);
	}
	void setRozPrice(double rozPrice) {
		this->m_rozPrice = std::move(rozPrice);
	}
	void setDescription(std::string description) {
		this->m_description = std::move(description);
	}
};
int main() {
	int name;
	int price;
	std::cin >> name;
	std::cout << name;
	std::cin >> price;
	std::cout << price;
	return 0;
}